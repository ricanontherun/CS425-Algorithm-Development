#include <iostream>
#include <cassert>

#include "double_list.h"

using ConstListIterator = List<std::string>::const_iterator;

/**
 * Search for o in start ... end. Returns end if o in not found.
 */
template <typename Iterator, typename Object>
Iterator Find(Iterator start, Iterator end, const Object & o)
{
  for ( ; start != end && *start != o; ++start ) ;

  return start;
}

int main()
{
  List<std::string> strings;

  strings.push_back("Christian");
  strings.push_back("Natalie");
  strings.push_back("Jasmine");
  strings.push_back("Rick");

  std::string search = "Rick";

  const auto it = Find<ConstListIterator, std::string>(
      strings.begin(),
      strings.end(),
      "Rick"
  );

  assert(it != strings.end());

  const auto it2 = Find<ConstListIterator, std::string>(
      strings.begin(),
      strings.end(),
      "NOT IN THE LIST"
  );

  assert(it2 == strings.end());
}
