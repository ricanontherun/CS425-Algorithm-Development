#include <iostream>
#include <map>
#include <vector>
#include <utility>

#define PUZZLE_ROWS 4
#define PUZZLE_COLS 4

#define TOP_BOUNDARY    0
#define LEFT_BOUNDARY   0
#define BOTTOM_BOUNDARY PUZZLE_ROWS - 1
#define RIGHT_BOUNDARY  PUZZLE_COLS - 1


struct character_position
{
  int x;
  int y;

  character_position(int x, int y) : x(x), y(y) {}
};

char puzzle[PUZZLE_ROWS][PUZZLE_COLS] = {
  {'t', 'h', 'i', 's'},
  {'w', 'a', 't', 's'},
  {'o', 'a', 'h', 'g'},
  {'f', 'g', 'd', 't'}
};

std::string dictionary[] {
  "this",
  "two",
  "fat",
  "that"
};

std::map<char, std::vector<struct character_position>> character_positions;

void GatherMeta()
{
  for ( int row = 0; row < PUZZLE_ROWS; ++row ) {
    for ( int col = 0; col < PUZZLE_COLS; ++col ) {
      char character = puzzle[row][col];
      character_positions[character].emplace_back(col, row);
    }
  }
}

void SearchUp(const std::string & word, struct character_position position)
{
  // If we're at the top of the matrix, we cant look up.
  if ( position.y <= TOP_BOUNDARY ) {
    return;
  }

  std::string context = "";
  for ( int y = position.y; y >= 0; --y ) {
    context += puzzle[y][position.x];
  }

  if ( context.find(word) != std::string::npos ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << position.x << "," << position.y - (word.length() - 1) << ")\n"; }
}

void SearchRight(const std::string & word, struct character_position position)
{
  // Out of bounds check
  if ( position.x >= RIGHT_BOUNDARY ) {
    return;
  }

  std::string context = "";
  for ( int x = position.x; x <= RIGHT_BOUNDARY; ++x ) {
    context += puzzle[position.y][x];
  }

  if ( context.find(word) != std::string::npos ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << position.x + (word.length() - 1) << "," << position.y << ")\n"; }
}

void SearchForWords()
{
  for ( const auto & word : dictionary ) {
    if ( word.length() == 0 ) {
      continue;
    }

    // Because we gathered meta data on each characters positions, we know the
    // possible starting positions for this particular word based on it's first char.
    char first_character = word.at(0);
    std::vector<struct character_position> & positions = character_positions.at(first_character);

    // This kinda sucks though. Although each direction isn't always searched, it seems inefficient.
    for ( const auto & position : positions ) {
      SearchUp(word, position);

      SearchRight(word, position);
    }

    break;
  }
}

int main()
{
  GatherMeta();

  SearchForWords();
}
