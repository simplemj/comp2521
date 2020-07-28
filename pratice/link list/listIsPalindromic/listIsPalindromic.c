
#include "list.h"

bool listIsPalindromic(List l) {
	// TODO
	if(l == NULL) return true;
	else {
		Node front = l->first;
		Node end = l->last;
		while(front != end && end != front) {
			if (front->value != end->value) {
				return false;
			}
			front = front->next;
			end = end->prev;
		}


	}
	return true;
}

