#include <iostream>
#include <cassert>

#include "double_list.h"
#include "single_list.h"

/**
 * Validate a list (single or double) of a given type.
 */
template <typename T>
void validateSwap()
{
  T list;

  // Populate.
  for ( int i = 0; i < 20; ++i ) {
    list.push_back(i);
  }

  assert(*(list.begin()) == 0);
  assert(*(++list.begin()) == 1);

  list.swap(list.begin());

  assert(*(list.begin()) == 1);
  assert(*(++list.begin()) == 0);
}

int main()
{
  validateSwap<List<int>>();
  validateSwap<SingleList<int>>();

  return EXIT_SUCCESS;
}
