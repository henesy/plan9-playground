#ifndef STK_H
#define STK_H

typedef struct Stack Stack;
typedef struct Node Node;

// Represents a Stack
struct Stack {
	Node*	root;
	uint	size;
};

// Represents a Stack Node
struct Node {
	Node*	next;
	void*	dat;
};

// Create a new stack
Stack	mkstack(void);

// Push onto the stack
void	sadd(Stack*, void*);

// Pop from the stack
void*	spop(Stack*);

// Peek at the top element on the stack
void*	speek(Stack*);

#endif
