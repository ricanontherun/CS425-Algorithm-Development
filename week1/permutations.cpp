#include <iostream>
#include <string.h>

void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char * a, int l, int r)
{
  if ( l == r ) {
    std::cout << a << "\n";
  } else {
    for ( int i = l; i <= r; ++i ) {
      swap(a + l, a + i);
      permute(a, l + 1, r);
      swap(a + l, a + i);
    }
  }
}

int main()
{
  char str[] = "ABC";
  int n = strlen(str);

  // Permute() prints the permutations of a string from 0 to it's end.
  permute(str, 0, n - 1);

  return 0;
}
