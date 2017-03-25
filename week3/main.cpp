#include <iostream>
#include <cassert>

#include "double_list.h"
#include "single_list.h"

/**
 * Validate the correctness of the swap() method, which swaps two adjacent
 * nodes by modifying their links.
 */
template <typename T>
void validateSwapAdjacent()
{
  T list;

  // Populate with 20 integers.
  for ( int i = 0; i < 20; ++i ) {
    list.push_back(i);
  }

  // Verify pre-condition
  assert(*(list.begin()) == 0);
  assert(*(++list.begin()) == 1);

  // Swap the first element with it's right neighbor.
  list.swap(list.begin());

  // Verify the post-condition (elements should be swapped)
  assert(*(list.begin()) == 1);
  assert(*(++list.begin()) == 0);
}

int main()
{
  validateSwapAdjacent<List<int>>();
  validateSwapAdjacent<SingleList<int>>();

  return EXIT_SUCCESS;
}
