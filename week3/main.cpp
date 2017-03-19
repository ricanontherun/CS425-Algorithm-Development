#include <iostream>

#include "double_list.h"
#include "single_list.h"

int main()
{
  SingleList<int> list;

  for ( int i = 0; i < 20; ++i ) {
    list.push_back(i);
  }
  return 0;
}
