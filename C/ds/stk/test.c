#include <u.h>
#include <libc.h>
#include "stk.h"

void
main(int, char*[])
{
	print("Beginning testing…\n");


	print("Testing creation…\n");
	Stack s = mkstack();
	
	assert(s.size == 0 && s.root == nil);
	

	print("Testing addition…\n");
	int a = 4, b = 7, c = 9;
	sadd(&s, &a);
	sadd(&s, &b);
	sadd(&s, &c);

	// Stack is: [9, 7,4]
	assert(s.size == 3);
	

	print("Testing peek…\n");
	int *t = speek(&s);
	assert(*t == 9);


	print("Testing pop…\n");
	spop(&s);

	t = spop(&s);
	assert(*t == 7);
	assert(s.size == 1);
	spop(&s);
	
	assert(s.size == 0 && s.root == nil);
	
	print("All tests passed.\n");
}
