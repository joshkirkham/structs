#ifndef _STACK_H_
#define _STACK_H_

/**
 * Function to free data in a stack node. It should ONLY free the node's data, not the node
 * itself
 */
typedef void (*FreeFunction)(void*);

typedef struct _stacknode {
	void *data;
	struct _stacknode* next;
} StackNode;


typedef struct {
	int size;
	int elemSize;
	StackNode* top; //Element 1 level lower down the stack
	FreeFunction freefunc;
} Stack;


void stack_init(Stack* stack, int elemSize, FreeFunction freefunc);

void stack_destroy(Stack* stack);

void stack_push(Stack* stack, void* elem);

void* stack_pop(Stack *stack);

void* stack_peek(Stack *stack);

int stack_size(Stack* stack);

int stack_elemSize(Stack* stack);




#endif
