
#include <stdlib.h>

#include "tree.h"

int size(Tree t) {
	if(t == NULL) return 0;
	else {
		int left = size(t->left);
		int right = size(t->right);
		return right + left + 1;
	}
}



bool TreeIsPerfectlyBalanced(Tree t) {
	// TODO
	if(t == NULL) return true;
	int l = size(t->left);
	int r = size(t->right);
	if(abs(l-r) > 1) return false;
	else return TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right);
}


