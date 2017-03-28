#include "bst.h"

#include <cassert>

int main() {
	BinarySearchTree<int> tree;

	tree.insert(2);
	tree.insert(7);
	tree.insert(1);
	tree.insert(3);
	tree.insert(10);

	assert(!tree.empty());

	assert(tree.contains(7));
	assert(tree.contains(1));
	assert(tree.contains(3));
	assert(tree.contains(2));

	assert(!tree.contains(30));

	tree.clear();
	assert(tree.empty());

	tree.insert(2);
	tree.insert(7);
	tree.insert(1);
	tree.insert(3);
	tree.insert(10);

	assert(!tree.empty());

	tree.remove(7);
	assert(!tree.contains(7));
}
