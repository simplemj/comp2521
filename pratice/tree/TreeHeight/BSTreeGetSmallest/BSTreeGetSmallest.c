
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	// TODO
	if(t == NULL) return NULL;
	if(t->left == NULL) return t;
	return BSTreeGetSmallest(t->left);
}
