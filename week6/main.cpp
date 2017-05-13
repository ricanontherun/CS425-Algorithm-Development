#include <iostream>
#include <cassert>

#include "binary_heap.h"

void tests()
{
	BinaryHeap<int> heap;

	for ( int i = 10; i > 0; --i ) {
		heap.insert(i);
		assert(heap.findMin() == i);
	}

	for ( int i = 1; i <= 10; ++i  ) {
		assert(heap.findMin() == i);
		heap.deleteMin();
	}
}

int main()
{
	tests();

	return EXIT_SUCCESS;
}
