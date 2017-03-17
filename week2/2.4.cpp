#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>
#include <vector>
#include <cassert>

/**
 * Solve a summation, going i = from to N = to using the provided callback in the form R fn(N) {}
 */
template <typename R, typename N>
R Summation(std::uint32_t from, std::uint32_t to, std::function<R(N)> fn)
{
  auto sum = static_cast<R>(0);

  for ( auto i = static_cast<N>(from); i <= to; ++i ) {
    sum += fn(i);
  }

  return sum;
}

struct LargeObject
{
  int x;

  LargeObject(int x) : x(x) {
  }
};

// The caller must specify a const & LargeObject variable for a reference to be returned, else a copy will occur.
LargeObject & getReference(std::vector<LargeObject> & arr)
{
  return arr[arr.size() - 1];
}

/**
 * Find the gcd of two integers using euclid's algorithm.
 *
 */
std::int64_t gcd(std::int64_t m, std::int64_t n) {
  // Technicallly the first iteration will reverse the numbers
  // in this case. But I'd rather be verbose about it and handle it.
  if ( m < n ) {
    std::swap(m,n);
  }

  while (n != 0) {
    std::int64_t remainder = m % n;
    m = n;
    n = remainder;
  }

  return m;
}

int main()
{
  // Solve the summation of x^3 from i=1 to 10
  int sum = Summation<int,int>(1, 10, [](int x) {
    return pow(x, 3);
  });

  assert(sum == 3025);

  std::vector<LargeObject> large_objects = {
    LargeObject(1),
    LargeObject(2),
    LargeObject(3)
  };

  LargeObject obj = getReference(large_objects);

  obj.x = 1234;

  assert(large_objects[large_objects.size() - 1].x != 1234);

  assert(gcd(10,5) == 5);
}
