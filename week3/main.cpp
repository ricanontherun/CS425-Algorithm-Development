#include <iostream>

#include "list.h"

int main()
{
    List<int> string_list;

    for ( int i = 0; i < 20; ++i ) {
        string_list.push_back(i);
    }

    List<int>::const_iterator iterator = string_list.begin();
    while ( iterator != string_list.end()  ) {
      std::cout << *iterator << "\n";
      iterator++;
    }
}
