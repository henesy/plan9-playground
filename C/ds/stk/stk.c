#include <u.h>
#include <libc.h>
#include "stk.h"

// Create a new stack
Stack
mkstack(void)
{
	return (Stack){nil, 0};
}

// Push onto the stack
void
sadd(Stack* s, void* dat)
{
	Node* n = malloc(1 * sizeof(Node));
	n->dat = dat;

	n->next = s->root;
	s->root = n;
	s->size++;
}

// Pop from the stack
void*
spop(Stack* s)
{
	if(s == nil)
		return nil;

	if(s->size <= 0)
		return nil;

	Node* n = s->root;
	void* dat = n->dat;	

	if(s->size == 1)
		// Last element, nothing to connect root to
		s->root = nil;
	else
		s->root = n->next;

	s->size--;

	free(n);
	return dat;
}

// Peek at the top element on the stack
void*
speek(Stack* s)
{
	return s->root->dat;
}
