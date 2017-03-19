#include <iostream>
#include <cassert>

#include "double_list.h"
#include "single_list.h"

using IntList = SingleList<int>;

void listAssertions(IntList & list)
{
  // Size
  assert(!list.empty());
  assert(list.size() == 20);

  // test front and back peek
  assert(list.front() == 0);
  assert(list.back() == 19);

  // const_iterator tests.
  SingleList<int>::const_iterator it = list.begin();

  assert(it != list.end());
  int number = 0;
  while ( it != list.end() )
  {
    assert(*it == number);

    ++it;
    ++number;
  }

}

void destructiveAssertions(IntList & list)
{
  IntList local1 = list;
  IntList local2 = local1;

  // Pop back
  for ( int i = 19; i >= 0; --i )
  {
    assert(list.back() == i);
    list.pop_back();
  }

  // The list should be empty now.
  assert(list.empty());
  assert(list.size() == 0);

  // Pop front
  for ( int i = 0; i < 20; ++i )
  {
    assert(local1.front() == i);
    local1.pop_front();
  }

  assert(local1.empty());
  assert(local1.size() == 0);

  // test clear.
  local2.clear();
  assert(local2.empty());
  assert(local2.size() == 0);
}

int main()
{
  SingleList<int> list;

  assert(list.empty());

  for ( int i = 0; i < 20; ++i ) {
    list.push_back(i);
  }

  listAssertions(list);

  // Test the copy constructor/operator
  SingleList<int> copy_constructed = list;

  listAssertions(copy_constructed);

  destructiveAssertions(list);
  destructiveAssertions(copy_constructed);
}
