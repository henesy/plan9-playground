/* prolog.c: a simple Prolog interpreter written in C++,				*/
/*			including an example test run as main().					*/
/* Copyright (c) Alan Mycroft, University of Cambridge, 2000.			*/

/* Ported to Plan 9 by Sean Hinchee, 2018								*/

#include <u.h>
#include <libc.h>
#define bool int
#define true 1
#define false 0

void
indent(int n)
{
	for(int i = 0; i<n; i++)
		print("	");
}

/*
	Atom functions
*/
typedef struct Atom Atom;
struct Atom {
	char *atomname;
	bool (*eqatom)(Atom*, Atom*);
};

bool
eqatom(Atom* t0, Atom* t1)
{
	return strcmp(t0->atomname, t1->atomname) == 0;
}

// Atom.print() calls should be: print("%s", Atom->atomname);

// Initialize an Atom
Atom*
MkAtom(Atom* a, char* s)
{
	a->atomname = s;
	a->eqatom = eqatom;
	return a;
}

/*
	TermsCons functions
*/
typedef struct TermsCons TermsCons;
struct TermsCons {
	int arity;
	Atom* fsym;
	void** args;

	//TermsCons* (*MkTermsCons)(Atom *f, void* a1, void* a2, void* a3);
	void (*print)(TermsCons* t);
	
	bool unify(Term *t) { return t->unify2(this); }
	
	void* 
	copy() { return copy2(); }
	
	TermCons
	*copy2()
	{ return new TermCons(this); }

	TermCons(TermCons *p)
			: fsym(p->fsym), arity(p->arity),
			  args(p->arity==0 ? nil : new Term*[p->arity])
			{ for(int i=0; i<arity; i++) args[i] = p->args[i]->copy(); }
	
	bool unify2(TermCons *t) { 
	  if(!(fsym->eqatom(t->fsym) && arity == t->arity))
		  return false;
	  for(int i = 0; i<arity; i++)
		  if(!args[i]->unify(t->args[i])) return false;
	  return true;
	}
};

void
PrintTermsCons(TermsCons* t)
{
	t->fsym->print();
	if(t->arity > 0){
		print("(");
		for(int i = 0; i < t->arity; ){
			t->args[i]->print();
			if(++i < t->arity)
				print(",");
		}
		print(")");
	}
}

// Initialize a TermsCons
TermsCons*
MkTermsCons(TermsCons* t, Atom *f, void* a1, void* a2, void* a3)
{
	int count = 3;
	if(a1 == nil)
		--i;
	if(a2 == nil)
		--i;
	if(a3 == nil)
		--i;

	t->fsym = f;
	t->arity = count;
	t->args = calloc(count, sizeof(Term*));

	if(a1 != nil)
		args[0] = a1;
	if(a2 != nil)
		args[1] = a2;
	if(a3 != nil)
		args[2] = a3;
	
	t->print = PrintTermsCons;
}

struct TermVar {

	void* instance;
	int varno;
	static int timestamp;
	bool unify(Term *t);

	TermVar() : instance(this), varno(++timestamp) 
	{}
	
	void print()
	{ if(instance!=this) instance->print();
					else cout<<"_"<<varno; };
	
	void* copy();

	void* reset() { instance = this; }
	
	bool unify2(TermCons *t)
	{
		return this->unify(t);
	}
};

int TermVar.timestamp = 0;

typedef struct Program Program;
typedef struct TermVarMapping TermVarMapping;

struct Goal {

	TermCons *car;
	Goal *cdr;

	Goal(TermCons *h, Goal *t) : car(h), cdr(t)
	{
	}

	Goal
	*copy()
	{
		return new Goal(car->copy2(), cdr==nil ? nil : cdr->copy());
	}

	Goal
	*append(Goal *l)
	{
		return new Goal(car, cdr==nil ? nil : cdr->append(l));
	}

	void print()
	{
		car->print();
		if(cdr != nil){
			cout << "; ", cdr->print();
		}
	}

	void solve(Program *p, int level, TermVarMapping *map);
};

struct Clause {

	TermCons *head;
	Goal *body;

	Clause(TermCons *h, Goal *t) : head(h), body(t)
	{
	}
	
	Clause
	*copy()
	{ 
		return new Clause(head->copy2(), body==nil ? nil : body->copy());
	}

	void print()
	{ 
		head->print();
		cout << " :- ";
		if(body==nil) cout << "true";
		else body->print();
	}
};

struct Program {

	Clause *pcar;
	Program *pcdr;
	Program(Clause *h, Program *t) : pcar(h), pcdr(t) {}
};

struct Trail {
	TermVar *tcar;
	Trail *tcdr;
	static Trail *sofar;
	Trail(TermVar *h, Trail *t) : tcar(h), tcdr(t) {}

	static Trail *Note() { return sofar; }
	static void Push(TermVar *x) { sofar = new Trail(x, sofar); }
	static void Undo(Trail *whereto)
	{	for(; sofar != whereto; sofar = sofar->tcdr)
			sofar->tcar->reset();
	}
};

Trail* Trail.sofar = nil;

bool
TermVar.unify(void* t)
{ 
	if(instance!=this)
		return instance->unify(t);
	Trail::Push(this);
	instance = t;
	return true;
}

void*
TermVar.copy()
{
	if(instance==this){
		Trail::Push(this); instance = new TermVar();
	}
	return instance;
}




struct TermVarMapping {
	TermVar **varvar;
	char **vartext;
	int size;

	TermVarMapping(TermVar *vv[], char *vt[], int vs)
		:varvar(vv), vartext(vt), size(vs) {}
	
	void
	showanswer()
	{
		if(size == 0)
			cout << "yes\n";
		else{
			for(int i = 0; i < size; i++){
				cout << vartext[i] << " = "; varvar[i]->print(); cout << "\n";
			}
		}
	}
};

void
Goal::solve(Program *p, int level, TermVarMapping *map)
{
	indent(level); cout << "solve@"  << level << ": ";
	this->print(); cout << "\n";
	for(Program *q = p; q != nil; q = q->pcdr){
		Trail *t = Trail::Note();
		Clause *c = q->pcar->copy();
		Trail::Undo(t);
		indent(level); cout << "  try:"; c->print(); cout << "\n";
		
		if(car->unify(c->head)){
			Goal *gdash = c->body==nil ? cdr : c->body->append(cdr);
			if
				(gdash == nil) map->showanswer();
			else
				gdash->solve(p, level+1, map);
		}else{
			indent(level); cout << "  nomatch.\n";
		}
		Trail::Undo(t);
	}
}

/* A sample test program: append */

Atom *at_app = new Atom("app");
Atom *at_cons = new Atom("cons");
TermCons *f_nil = new TermCons(new Atom("nil"));
TermCons *f_1 = new TermCons(new Atom("1"));
TermCons *f_2 = new TermCons(new Atom("2"));
TermCons *f_3 = new TermCons(new Atom("3"));

void* v_x = new TermVar();
TermCons *lhs1 = new TermCons(at_app, f_nil, v_x, v_x);
Clause *c1 = new Clause(lhs1, nil);

void* v_l = new TermVar();
void* v_m = new TermVar();
void* v_n = new TermVar();

TermCons *rhs2 = new TermCons(at_app, v_l, v_m, v_n);
TermCons *lhs2 = new TermCons(at_app, new TermCons(at_cons, v_x, v_l),
									  v_m,
									  new TermCons(at_cons, v_x, v_n));

Clause *c2 = new Clause(lhs2, new Goal(rhs2,nil));

TermVar *v_i = new TermVar();
TermVar *v_j = new TermVar();
TermCons *rhs3 = new TermCons(at_app, v_i, v_j, 
	new TermCons(at_cons, f_1,
	new TermCons(at_cons, f_2,
	new TermCons(at_cons, f_3, f_nil))));

Goal *g1 = MkGoal(g1, rhs3, nil);

Program* test_p_tmp = MkProgram(test_p_tmp, c2, nil);
Program* test_p = MkProgram(test_p, c1, test_p_tmp);

Program* test_p2_tmp = MkProgram(c1, nil);
Program* test_p2 = MkProgram(test_p2, c2, test_p2_tmp);

TermVar *varvar[] = {v_i, v_j};
char *varname[] =  {"I", "J"};

TermVarMapping *var_name_map;
MkTermVarMapping(var_name_map, varvar, varname, 2);

void
main(int argc, char *argv[])
{
	print("=======Append with normal clause order:\n");
	g1->solve(test_p, 0, var_name_map);
	print("\n=======Append with reversed normal clause order:\n");
	g1->solve(test_p2, 0, var_name_map);

	exits(nil);
}
