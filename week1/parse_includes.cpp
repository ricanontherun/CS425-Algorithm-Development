#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>
#include <exception>
#include <regex>

#include "header1.h"

bool isHeader(const std::string & line, std::string & filepath)
{
  std::size_t position = line.find("#include ");

  if ( position == std::string::npos || position != 0 ) {
    return false;
  }

  std::size_t first_quote = line.find_first_of('"');
  std::size_t last_quote = line.find_last_of('"');

  if (
      first_quote == std::string::npos ||
      last_quote == std::string::npos ||
      first_quote == line.length() - 1 // Make sure we aren't at the end of the line.
  ) {
    return false;
  }

  std::size_t start = first_quote;
  std::size_t end = last_quote - first_quote;

  filepath= line.substr(first_quote + 1, end - 1);

  return true;
}

// We need to prevent the reparsing of duplicate includes.
// We could keep a hash of filepaths to their contents. Also, disallow
// the parsing of a header whose path matches the one we're currently parsing
void parseFile(const std::string & filepath)
{
  std::ifstream stream(filepath);

  // What happens when the file isn't valid? Throw? Return?
  std::string line, header;

  while ( std::getline(stream, line) ) {
    if ( isHeader(line, header) ) {
      parseFile(header);
    } else {
      std::cout << line << "\n";
    }
  }
}

int main(int argc, char **argv)
{
  if ( argc == 1 ) {
    std::cerr << "No file provided.\n";
    return EXIT_FAILURE;
  }

  std::string filepath{argv[1]};
  std::ifstream stream(filepath);

  if (!stream.good()) {
    std::cerr << strerror(errno) << "\n";
    return EXIT_FAILURE;
  }

  parseFile(filepath);
}
