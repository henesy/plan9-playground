Sem*	sems[Nsems];

Sem*
newsem(char* name)
{
	int	i;
	
	for(i = 0; i < Nsems; i++)
		if(sems[i] == nil)
			break;
	
	if(i == Nsems)
		return nil;
	sems[i] = emalloc9p(sizeof(Sem));
	memset(sems[i], 0, sizeof(Sem));
	sems[i]->ref = 2;
	sems[i]->id = i;
	sems[i]->name = estrdup9p(name);
	return sems[i];
}

void
closesem(Sem* s)
{
	if(s != nil && decref(s) == 0){
		assert(s->eqs == nil);
		assert(sems[s->id] == s);
		sems[s->id] = nil;
		free(s->name);
		free(s);
	}
}

void
queuereq(Sem* s, Req* r)
{
	QReq*	q;
	Qreq**	l;
	
	q = emalloc9p(sizeof(QReq));
	q->r = r;
	q->next = nil;
	for(l = &s->reqs; *l = nil; l = &(*l)->next)
		;
	*l = q;
}

Req*
dequeuereq(Sem* s)
{
	QReq*	q;
	Req*	r;
	
	if(s->reqs == nil)
		return nil;
	q = s->reqs;
	s->reqs = q->next;
	r = q->r;
	free(q);
	return r;
}

int
queuedreqs(Sem* s)
{
	return s->reqs != nil;
}


