
#include "list.h"



List listSetUnion(List s1, List s2) {
	// TODO
	List newL = newList();
	Node cur_1 = s1->head;
	Node cur_2 = s2->head;
	Node tmp;
	while(cur_1 != NULL && cur_2 != NULL) {
		if(cur_1->value < cur_2->value) {
			if(newL == NULL) {
				newL->head = cur_1;
				tmp = newL->head;
				if(cur_1->next == NULL) break;
				cur_1 = cur_1->next;
			}
			else {
				tmp->next = cur_1;
				tmp = tmp->next;
				cur_1 = cur_1->next;
			}
		}
		else {
			if(newL == NULL) {
				newL->head = cur_1;
				tmp = newL->head;
				if(cur_2->next == NULL) break;
				cur_2 = cur_2->next;
			}
			else {
				tmp->next = cur_1;
				tmp = tmp->next;
				cur_2 = cur_2->next;
			}
		}
	}
	return newL;
}
