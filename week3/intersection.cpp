#include <iostream>
#include <algorithm>
#include <cassert>

#include "double_list.h"

template <typename T>
T FindIntersection(const T & left, const T & right)
{
  T intersection;

  for ( auto left_it = left.begin(); left_it != left.end(); ++left_it) {
    for ( auto right_it = right.begin(); right_it != right.end(); ++right_it ) {
      if ( *left_it == *right_it ) { // Match, add to intersection.
        intersection.push_back(*left_it);
        break;
      }
    }
  }

  return intersection;
}

template <typename T>
T FindUnion(const T & left, const T & right)
{
  T __union;

  for ( auto left_it = left.begin(); left_it != left.end(); ++left_it) {
    auto right_it = right.begin();
    auto right_end = right.end();
    for ( ; right_it != right_end; ++right_it ) {
      if ( *left_it == *right_it ) { // Match, add to __union.
        break;
      }
    }

    if ( right_it == right.end() ) {
      __union.push_back(*left_it);
    }
  }

  return __union;
}

int main() {
  List<int> numbers;
  numbers.push_back(1);
  numbers.push_back(5);
  numbers.push_back(11);
  numbers.push_back(200);

  List<int> numbers2;
  numbers2.push_back(1);
  numbers2.push_back(2);
  numbers2.push_back(3);
  numbers2.push_back(4);
  numbers2.push_back(5);

  List<int> intersection = FindIntersection(numbers, numbers2);
  assert(intersection.size() == 2);

  List<int> un = FindUnion(numbers, numbers2);
  assert(un.size() == 2);
}
