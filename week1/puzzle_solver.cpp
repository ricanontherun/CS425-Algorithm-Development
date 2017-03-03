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

struct position
{
  int x;
  int y;

  position(int x, int y) : x(x), y(y) {}
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

// Ordered map of individual characters in the map and their various positions.
std::map<char, std::vector<struct position>> character_positions;

void SearchUp(const std::string & word, struct position position)
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
    std::cout << "going to (" << position.x << "," << position.y - (word.length() - 1) << ")\n";
  }
}

void SearchRight(const std::string & word, struct position position)
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
    std::cout << "going to (" << position.x + (word.length() - 1) << "," << position.y << ")\n";
  }
}

void SearchDown(const std::string & word, struct position position)
{
  // Out of bounds check
  if ( position.y >= BOTTOM_BOUNDARY ) {
    return;
  }

  std::string context = "";
  for ( int y = position.y; y <= BOTTOM_BOUNDARY; ++y ) {
    context += puzzle[y][position.x];
  }

  if ( context.find(word) != std::string::npos ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << position.x << "," << position.y + (word.length() - 1) << ")\n";
  }
}

void SearchLeft(const std::string & word, struct position position)
{
  if ( position.x <= LEFT_BOUNDARY ) {
    return;
  }

  std::string context = "";
  for ( int x = position.x; x >= LEFT_BOUNDARY; --x ) {
    context += puzzle[position.y][x];
  }

  if ( context.find(word) != std::string::npos ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << position.x - (word.length() - 1) << "," << position.y << ")\n";
  }
}

/**
 * Search the puzzle for all words in the dictionary.
 *
 */
void SearchForWords()
{
  for ( const auto & word : dictionary ) {
    if ( word.length() == 0 ) {
      continue;
    }

    // Because we gathered meta data on each characters positions, we know the
    // possible starting positions for this particular word based on it's first char.
    char first_character = word.at(0);
    std::vector<struct position> & positions = character_positions.at(first_character);

    // We have to explicityly search each direction for a match.
    // This kinda sucks, and could probably be more efficient.
    for ( const auto & position : positions ) {
      SearchUp(word, position);
      SearchRight(word, position);
      SearchDown(word, position);
      SearchLeft(word, position);
    }
  }
}

/**
 * This function gathers the positions of each character
 * in the puzzle matrix. This allows us to know the starting
 * positions of potential matches by using the first character.
 *
 */
void GatherMeta()
{
  for ( int row = 0; row < PUZZLE_ROWS; ++row ) {
    for ( int col = 0; col < PUZZLE_COLS; ++col ) {
      character_positions[puzzle[row][col]].emplace_back(col, row);
    }
  }
}

int main()
{
  GatherMeta();

  SearchForWords();

  return 0;
}
