#include <stdio.h>
#include "stack.h"
void main(void) {
	
	Stack stack;
	stack_init(&stack, sizeof(int), NULL);
	for (int i = 0; i < 10; ++i) {
		stack_push(&stack, &i);
	}

	while(stack.size > 0)
		printf("%d\n",  *(int*)stack_pop(&stack));
	
}
