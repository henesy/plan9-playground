#include <u.h>
#include <libc.h>
#include "sll.h"

// Create a new list
Sll
mksll()
{
	return (Sll){nil, 0};
}

// Append to a list
void
ladd(Sll* l, void* p)
{
	int i;
	Sllnode* new = malloc(sizeof(Sllnode));
	new->dat = p;
	new->next = nil;
	Sllnode* n = l->root;
	
	if(l->size == 0){
		l->root = new;
		new->next = nil;
		l->size++;
		return;
	}

	for(i = 0; i < l->size; i++){
		if(i != l->size-1)
			n = n->next;
	}
	
	n->next = new;
	new->next = nil;
	l->size++;
	return;
	
}

// Search → delete from a list
void*
ldel(Sll* l, void* tofind, int(*comp)(void *, void *))
{
	int i;
	void* dat = nil;
	Sllnode* n = l->root;
	Sllnode* prev = nil;
	
	if(l->size == 0){
		return dat;
	}

	for(i = 0; i < l->size; i++){
		if((*comp)(n->dat, tofind)){
			if(l->size == 1){
				// 1 node
				dat = n->dat;
				free(n);
				l->root = nil;
			}else if(i == 0){
				// 0 nodes
				l->root = n->next;
				dat = n->dat;
				free(n);
			}else if(i == l->size-1){
				// We are the last node
				prev->next = nil;
				dat = n->dat;
				free(n);
			}else{
				// this is probably unsafe
				prev->next = n->next;
				dat = n->dat;
				free(n);
			}
			l->size--;
			return dat;
		}
		
		prev = n;
		if(i != l->size-1)
			n = n->next;
			
	}
	return dat;
}

// Gets a list element by "index" -- ArraySll style
void*
lget(Sll *l, int index)
{
	// Out of bounds check
	if(index < 0 || index >= l->size)
		return nil;

	int i;
	Sllnode* n = l->root;
	for(i = 0; i < l->size; i++, n = n->next)
		if(i == index)
			return n->dat;

	// Should never happen
	return nil;
}
