
#include <stdlib.h>

#include "BSTree.h"

int BSTreeNodeDepth(BSTree t, int key) {
	if(t == NULL) return -1;
	if(t->value == key) return 0;
	else if(key < t->value) {
		int l = BSTreeNodeDepth(t->left,key);
		if(l == -1) return -1;
		return l + 1;
	}
	else {
		int r = BSTreeNodeDepth(t->right,key);
		if(r == -1) return -1;
		return r + 1;
	}
}

