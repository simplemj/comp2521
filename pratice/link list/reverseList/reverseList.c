
#include "list.h"

void listReverse(List l) {
	// TODO
	Node cur = l->head;
	Node head = NULL;
	while (cur != NULL) {
		Node tmp = cur->next;
		cur->next = head;
		head = cur;
		cur = tmp;
	} 
	l->head = head;
}

