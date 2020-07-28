
#include "list.h"

int numDupesInOrderedList(List l) {
	// TODO
	Node tmp = l->head;
	int count = 0;
	while(tmp->next != NULL) {
		if(tmp->value == tmp->next->value) {
			count++;
		}
		tmp = tmp->next;
	}
	return count;
}

