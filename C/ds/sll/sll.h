#ifndef SLLIST_H
#define SLLIST_H

/* Sll (Queue) Architecture */
typedef struct Sllnode Sllnode;
typedef struct Sll Sll;

struct Sllnode {
	Sllnode*	next;
	void*	dat;
};

struct Sll {
	Sllnode*	root;
	uint	size;
};

// Create a new list
Sll mklist(void);

// Append to a list
void ladd(Sll*, void*);

// Search → delete from a list
void* ldel(Sll*, void*, int(*comp)(void *, void *));

// Access elements of a list by 'index'
void* lget(Sll*, int);

#endif
