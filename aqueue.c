#include "aqueue.h"



void aqueue_init(ArrayQueue* queue, int capacity, size_t elem_size, FreeFunction free_func) {
	queue->ptr_array = malloc(capacity * sizeof(void*));
	queue->capacity = capacity;
	queue->elem_size = elem_size;
	queue->free_func = free_func;
	queue->length = 0;
	queue->head =queue->tail = queue->ptr_array;
}

void aqueue_destroy(ArrayQueue* queue) {
	

void aqueue_enqueue(ArrayQueue* queue, void* data);

void* aqueue_dequeue(ArrayQueue* queue);

void* aqueue_peek(ArrayQueue* queue);

