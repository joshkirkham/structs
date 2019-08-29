/* A non-intrusive circular doubly linked list with a single sentinel node.
 * 
 * TODO: 
 * 		The current implementation has everything you "need". Add some QoL 
 		stuff like a reverse for_each and a for_each which is safe for
 		removing nodes (cache next pointer). kernek/list.h has some cool shit
 		to try and implement.

 		ADD A SORT

 		Make this threadsafe.
*/

#include "common.h"


struct ListNode {
	struct ListNode *prev, *next;
};

typedef struct ListNode ListNode;


#define BLANK_LIST_NODE(name) { &(name), &(name)}

#define LIST_NODE(prev, next) {(prev), (next)}

#define CREATE_LIST_NODE(name) ListNode name = BLANK_LIST_NODE(name)

static inline void list_node_init(ListNode *l) {
	l->prev = l;
	l->next = l;
}



static inline void list_insert_after(ListNode *after, ListNode *new) {
	_list_insert(after, new, after->next);
}

static inline void list_insert_before(ListNode *before, ListNode *new) {
	_list_insert(before->prev, new, before);
}

/* Inserts a node between two consecutive nodes. 
 * INVALID FOR ARBITRARY NODES - ONLY USE WHEN prev AND next ARE KNOWN.
 * Preferrably, only use it inside this file.
 */
static inline void _list_insert(ListNode *prev, ListNode *new, ListNode *next) {
	prev->next = new;
	new->prev = prev;
	next->prev = new;
	new->next = next;
}


static inline ListNode* list_remove(ListNode *node) {
	node->next->prev = node->prev;
	node->prev->next = node->next;
	return node;
}

static inline bool list_is_empty(ListNode *head) {
	return head->next == head && head->prev == head;
}


/* Given a list node contained in a struct and some type info
 * evaluates to a pointer to the containing struct.
 * 
 * list_node: A pointer to a ListNode struct
 * type: The type name of the outer structure
 * memberName: The member name of the ListNode in the exterior struct
 */
#define LIST_ENTRY(list_node, type, member_name) \
	CONTAINER_OF(list_node, type, member_name)


/* Iterate over a chain of ListNodes
 * 
 * head: The head (sentinel node) of the list. Behavior of the body is \
 *			undefined if it is another node
 * pos: A ListNode to be used as a position counter
 *
 * WARNING: NOT ADVISABLE TO CHANGE LIST STRUCTURE INSIDE BODY OF STATEMENT
 */
#define LIST_FOR_EACH(head, pos) \
	for(pos = (head)->next; pos != (head); pos = pos->next)
