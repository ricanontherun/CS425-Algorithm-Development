/**
 * Christian Roman
 * March 3rd 2017
 * Week 1 Assignment
 *
 * The algorithm I chose to use emulates how a human might search for words in a puzzle. The algorithm first maps each
 * character in the puzzle to their various locations (coordinate pairs). When searching a for a word, it references the
 * positions the word's first character. It then performs character by character searches along each direction possible
 * from that starting point.
 */
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
  std::size_t word_length = word.length();
  int word_i = 0;

  for (
    int y = position.y;
    y >= TOP_BOUNDARY, word_i < word_length, word[word_i] == puzzle[y][position.x];
    --y, ++word_i
  ) {
    context += puzzle[y][position.x];
  }

  if ( context == word ) {
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
  std::size_t word_length = word.length();
  int word_i = 0;

  for (
    int x = position.x;
    x <= RIGHT_BOUNDARY, word_i < word_length, word[word_i] == puzzle[position.y][x];
    ++x, ++word_i
  ) {
    context += puzzle[position.y][x];
  }

  if ( context == word ) {
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
  std::size_t word_length = word.length();
  int word_i = 0;

  // Search down the puzzle until we either 1) Reach the bottom or 2) Find a character which doesn't exist in the target
  // word.
  for (
    int y = position.y;
    y <= BOTTOM_BOUNDARY, word_i < word_length, puzzle[y][position.x] == word[word_i];
    ++y, ++word_i
  ) {
    context += puzzle[y][position.x];
  }

  if ( context == word ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << position.x << "," << position.y + (word.length() - 1) << ")\n";
  }
}

void SearchLeft(const std::string & word, struct position position)
{
  if ( position.x <= LEFT_BOUNDARY ) {
    return;
  }

  // Check if we have enough room to search.
  std::string context = "";
  std::size_t word_length = word.length();
  int word_i = 0;

  for (
    int x = position.x, y = 0;
    x >= LEFT_BOUNDARY, word_i < word_length, puzzle[position.y][x] == word[word_i];
    --x, ++y, ++word_i
  ) {
    context += puzzle[position.y][x];
  }

  if ( context == word ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << position.x - (word.length() - 1) << "," << position.y << ")\n";
  }
}

void SearchUpRight(const std::string & word, struct position position)
{
  if ( position.x >= RIGHT_BOUNDARY || position.y <= TOP_BOUNDARY ) {
    return;
  }


  std::string context = "";
  std::size_t word_length = word.length();
  int word_i = 0;

  int x, y;
  for (
    x = position.x, y = position.y;
    x <= RIGHT_BOUNDARY, y >= TOP_BOUNDARY, word_i < word_length, word[word_i] == puzzle[y][x];
    ++x, --y, ++word_i
  ) {
    context += puzzle[y][x];
  }

  if ( context.find(word) != std::string::npos ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << x - 1 << "," << y + 1 << ")\n";
  }
}

void SearchDownRight(const std::string & word, struct position position)
{
  if ( position.x >= RIGHT_BOUNDARY || position.y >= BOTTOM_BOUNDARY ) {
    return;
  }

  std::string context = "";
  std::size_t word_length = word.length();
  int word_i = 0;
  int x, y;

  for (
    x = position.x, y = position.y;
    x <= RIGHT_BOUNDARY, y <= BOTTOM_BOUNDARY, word_i < word_length, word[word_i] == puzzle[y][x];
    ++x, ++y, ++word_i
  ) {
    context += puzzle[y][x];
  }

  if ( context == word ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << x - 1 << "," << y - 1 << ")\n";
  }
}

void SearchDownLeft(const std::string & word, struct position position)
{
  if ( position.x <= LEFT_BOUNDARY || position.y >= BOTTOM_BOUNDARY ) {
    return;
  }

  std::string context = "";
  std::size_t word_length = word.length();
  int word_i = 0;
  int x, y;

  for (
    x = position.x, y = position.y;
    x >= LEFT_BOUNDARY, y <= BOTTOM_BOUNDARY, word_i < word_length, word[word_i] == puzzle[y][x];
    --x, ++y, ++word_i
  ) {
    context += puzzle[y][x];
  }

  if ( context == word ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << x + 1 << "," << y - 1 << ")\n";
  }
}

void SearchUpLeft(const std::string & word, struct position position)
{
  if ( position.x <= LEFT_BOUNDARY || position.y <= TOP_BOUNDARY ) {
    return;
  }

  std::string context = "";
  std::size_t word_length = word.length();
  int word_i = 0;
  int x, y;

  for (
    x = position.x, y = position.y;
    x >= LEFT_BOUNDARY, y >= TOP_BOUNDARY, word_i < word_length;
    --x, --y, ++word_i
  ) {
    context += puzzle[y][x];
  }

  if ( context == word ) {
    std::cout << "Found '" << word << "' starting at (" << position.x << "," << position.y << ") ";
    std::cout << "going to (" << x + 1 << "," << y + 1 << ")\n";
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

    char first_character = word[0];

    if ( character_positions.count(first_character) == 0 ) {
      return;
    }

    // Because we gathered meta data on each characters positions, we know the
    // possible starting positions for this particular word based on it's first char.
    std::vector<struct position> & positions = character_positions[first_character];

    for ( const auto & position : positions ) {
      // Lateral searches
      SearchUp(word, position);
      SearchRight(word, position);
      SearchDown(word, position);
      SearchLeft(word, position);

      // Diagonal searches
      SearchUpRight(word, position);
      SearchDownRight(word, position);
      SearchDownLeft(word, position);
      SearchUpLeft(word, position);
    }
  }
}

/**
 * This function gathers the positions of each character
 * in the puzzle matrix. This allows us to know the starting
 * positions of potential matches by using the first character of
 * each search word.
 *
 */
void GatherCharacterPositions()
{
  for ( int row = 0; row < PUZZLE_ROWS; ++row ) {
    for ( int col = 0; col < PUZZLE_COLS; ++col ) {
      character_positions[puzzle[row][col]].emplace_back(col, row);
    }
  }
}

int main()
{
  GatherCharacterPositions();

  SearchForWords();

  return 0;
}
