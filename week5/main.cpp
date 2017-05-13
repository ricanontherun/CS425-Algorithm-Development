#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "hash_table.h"

using StringVector = std::vector<std::string>;

std::size_t GetLineCount(std::ifstream & stream)
{
	std::size_t number_of_lines = std::count(
		std::istreambuf_iterator<char>(stream),
		std::istreambuf_iterator<char>(),
		'\n'
	);

	// Reset the stream.
	stream.clear();
	stream.seekg(0, std::ios::beg);

	return number_of_lines;
}

bool GetLinesFromFile(const std::string & path, std::vector<std::string> & lines)
{
	std::ifstream data(path);

	if ( !data.good() ) {
		return false;
	}

	lines.reserve(GetLineCount(data));

	std::string line;

	while ( std::getline(data, line) )      {
		lines.push_back(line);
	}

	return true;
}

void TestQuadraticHash(const StringVector & strings)
{
	HashTable::Quadratic<std::string> table;

	std::size_t collisions = 0;
	table.setCollisionCallback([&collisions]() {
		collisions++;
	});

	for ( const auto & string : strings ) {
		table.insert(string);
	}

	std::cout << "Quadratic Probing Collisions: " << collisions << "\n";
}

void TestLinearHash(const StringVector & strings)
{
	HashTable::Linear<std::string> table;

	std::size_t collisions = 0;
	table.setCollisionCallback([&collisions]() {
		collisions++;
	});

	for ( const auto & string : strings ) {
		table.insert(string);
	}

	std::cout << "Linear Probing Collisions: " << collisions << "\n";
}

int main()
{
	// Load in the random first names. Generated from mockaroo.com
	StringVector lines;
	GetLinesFromFile("MOCK_DATA.csv", lines);

	TestLinearHash(lines);
	TestQuadraticHash(lines);
}
