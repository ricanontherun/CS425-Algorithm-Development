#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

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

int main()
{
  std::cout << std::setprecision(2) << std::fixed <<  Summation<double ,int>(1,10, [](int x) {
    return x;
  }) << "\n";
}
