#include <stdio.h>
#include <assert.h>
#include "stack.h"
#include <stdlib.h>
#include <string.h>


/**
 * Initializes the stack. The stack must already be allocated somewhere
 */
void stack_init(Stack* stack, int elemSize, FreeFunction freefunc) {
    stack->size = 0;
    stack->elemSize = elemSize;
    stack->top = NULL;
    stack->freefunc = freefunc;
}

/**
 * Frees the entire stack, including any data inside the nodes using the user defn'd freefunc
 */
void stack_destroy(Stack* stack) {
	while(stack->size > 0) {
		if (stack->freefunc)
			stack->freefunc(stack->top->data);
		StackNode *newTop = stack->top->next;
		free(stack->top);
		stack->top = newTop;
		--stack->size;
	}
}




void stack_push(Stack* stack, void* elem) {

	//Can't copy shit into safe memory locations here, because 
	//I don't know what they are.
	//I suppose this is a downside of this approach. The user needs to allocate space for stuff


	StackNode* newNode = malloc(sizeof(*newNode));
	newNode->data = malloc(stack->elemSize);
	memcpy(newNode->data, elem, stack->elemSize);

	newNode->next = stack->top;
	stack->top = newNode;

	stack->size++;
}




/**
 * Pops an element off the stack. The element is still allocated on the heap! The user is
 * responsible for freeing the space using their self defined freefunction
 */
void* stack_pop(Stack *stack) {
	if (stack->size <= 0) 
		return NULL;

	void* returnPtr = stack->top->data;
	StackNode* newTop = stack->top->next;
	
	//free the StackNode, but not the data it points to
	free(stack->top);

	stack->top = newTop;
	stack->size--;
	return returnPtr;
}
	

void* stack_peek(Stack *stack) {
	if (stack->size <= 0) 
		return NULL;

	return stack->top->data;
}

int stack_size(Stack* stack) {
	return stack->size;
}

int stack_elemSize(Stack* stack) {
	return stack->elemSize;
}

