#include <iostream>
#include <cassert>
#include <unistd.h>

#include "circular_index.h"
#include "double_list.h"

int main() {
  std::size_t start, players, passes;
  start = players = passes = 0;

  std::cout << "How many people are playing? ";
  std::cin >> players;

  std::cout << "How many passes are performed each round? ";
  std::cin >> passes;

  std::cout << "Playing the Josephus Program...\n";

  CircularIndex index(players);

  List<int> list;

  for ( int i = 0; i < players; ++i )
  {
    list.push_back(i);
  }

  int asd = 0;
  while ( !list.empty() ) {
    List<int>::iterator it = list.at(asd++);

    std::cout << *it << "\n";

    list.erase(it);
  }

  return 0;
  int i = 0;
  while ( list.size() != 1 ) {
    List<int>::iterator it = list.at(i);

    if ( it == list.end() ) {
      std::cout << "We found the end\n";
      break;
    } else {
      std::cout << "Erasing " << *it << " at index " << i << "\n";
      list.erase(it);
    }

    i++;
  }


  return 0;
  while ( list.size() != 1 ) {
    // Simulate M passes.
    index += passes;

    list.erase(list.at(index.index));

    ++index;

    std::cout << "Down to " << list.size() << " players\n";
    sleep(1);
  }
}
