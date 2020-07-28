
#include "list.h"
int check(List l, int val);

List listSetIntersection(List s1, List s2) {
	// TODO
	Node cur_1 = s1->head;
	Node cur_2 = s2->head;
	List newL = newList();
	while (cur_1 != NULL) {
		cur_2 = s2->head;
		while (cur_2 != NULL) {
			if (cur_1->value == cur_2->value) {
				if (check(newL,cur_1->value) == true) {
					Node new = newNode(cur_1->value);
					new->next = newL->head;
					newL->head = new;
				}
			}
		cur_2 = cur_2->next;
		}
		cur_1 = cur_1->next;
	}
	return newL;
}

int check(List l, int val) {
	Node cur = l->head;
	while (cur != NULL) {
		if (cur->value == val) {
			return false;
		}
		cur = cur->next;
	}
	return true;
}

