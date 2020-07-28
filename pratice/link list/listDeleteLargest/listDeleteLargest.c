
#include "list.h"

int listDeleteLargest(List l) {
	
	
	
	
	Node cur= l->head;
	int max = l->head->value;
	if(cur->next == NULL) {
		Node delete = l->head;
		l->head = NULL;
		free(delete);
	}
	else {

	while(cur != NULL) {
		if(max < cur->value) {
			max = cur->value;
		}
		cur = cur->next;
	}
	cur= l->head;
	int flag = 0;
	while(cur->next != NULL) {
		if(cur->next->value == max && flag == 0) {
			Node tmp = cur->next;
			cur->next = cur->next->next;
			free(tmp);
			flag = 1;
		}
		cur = cur->next;
	}
	}
	return max;
}

