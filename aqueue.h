/*
 * Header file for a generic fixed capacity queue implemented with an array
 *
 */

#ifndef _ARRAY_QUEUE_H_
#define _ARRAY_QUEUE_H_

typedef void (*FreeFunction)(void*);

/**
 * ptr_array: 	circular array of pointers to the struct's contents
 * elem_size:	the size of the elements in the queue
 * length:		the current number of elements in the queue
 * capacity:	the maximum number of elements the queue holds
 * head:		pointer to the next element to be dequeued
 * tail:		pointer to next element to be enqueued
 * 				head==tail indicates an empty queue
 * free_func	function to free complex data in the queue
 * 				NULL indicates no free_function is supplied
 */
typedef struct {
	void* ptr_array;
	size_t elem_size;
	int capacity;
	int length;
	void* head;
	void* tail;
	FreeFunction free_func;

} ArrayQueue;


/**
 * Initializes an empty queue. 
 */
void aqueue_init(ArrayQueue* queue, int capacity, size_t elem_size, FreeFunction free_func);


/**
 * Deallocates the queue and all currently enqueued elements, along with their data, using 
 * the caller supplied free function if one exists. Data stored on the heap which was previosly
 * enqueued is up to the caller to free.
 */
void aqueue_destroy(ArrayQueue* queue);


/**
 * Enqueues an element on the end of the queue.
 * Return:
 * 		0: enqueued
 * 		1: Not enough space on the queue
 * 		2: general error
 */
void aqueue_enqueue(ArrayQueue* queue, void* data);


/**
 * Dequeues first element from the queue
 * Return:
 * 		NULL: No elements left to dequeue
 * 		void*: pointer to the element to be dequeued
 */
void* aqueue_dequeue(ArrayQueue* queue);


/**
 * Shows the element of the queue which will be dequeued next without removing it
 * Return:
 * 		NULL: No elements left to dequeue
 * 		void*: pointer to the element to be dequeued
 */ 	
void* aqueue_peek(ArrayQueue* queue);






#endif /* _ARRAY_QUEUE_H_ */
