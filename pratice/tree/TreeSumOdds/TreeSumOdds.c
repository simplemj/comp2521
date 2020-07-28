
#include <stdlib.h>

#include "tree.h"

int TreeSumOdds(Tree t) {
	if(t == NULL) return 0;
	int count = TreeSumOdds(t->left) + TreeSumOdds(t->right);
	if(t->value % 2 != 0) {
		count = count + t->value;
	}
	
	return count;

}
