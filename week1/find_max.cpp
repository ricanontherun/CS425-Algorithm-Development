#include <iostream>
#include <vector>
#include <strings.h>

template <typename T, typename Comparator>
const T & find(const std::vector<T> & set, Comparator comparator)
{
  std::size_t size = set.size();

  if ( size == 0 )
  {
    // What do?
  }

  if ( size == 1 ) {
    return set[0];
  }

  std::uint32_t max = 0;

  for ( std::uint32_t i = 1; i < set.size(); ++i ) {
    if ( comparator(set[i], set[max]) ) {
      max = i;
    }
  }

  return set[max];
}

class StringGreaterThanComparator
{
  public:
    bool operator()(const std::string & s1, const std::string & s2)
    {
      return strcasecmp(s1.c_str(), s2.c_str()) > 0;
    }
};

class StringLessThanComparator
{
  public:
    bool operator()(const std::string & s1, const std::string & s2)
    {
      return strcasecmp(s1.c_str(), s2.c_str()) < 0;
    }
};

int main()
{
  std::vector<std::string> strings {
    "Christian",
    "Zaert",
    "acid",
    "Zebra"
  };

  std::cout << "Largest element: " << find(strings, StringGreaterThanComparator{}) << "\n";
  std::cout << "Smallest element: " << find(strings, StringLessThanComparator{}) << "\n";
}

