
#include <stdlib.h>

#include "BSTree.h"

int num_node(BSTree t) {
	if(t == NULL) return 0;
	return 1 + num_node(t->left) + num_node(t->right);
}



int BSTreeGetKth(BSTree t, int k) {
	// TODO
	int size = num_node(t->left);
	if(k == size) return t->value;
	else if(k < size) return BSTreeGetKth(t->left,k);
	else return BSTreeGetKth(t->right,k -size -1);
}

