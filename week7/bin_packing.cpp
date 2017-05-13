#include <iostream>
#include <vector>
#include <algorithm>

#define BIN_CAPACITY 1.0

struct item {
	float size;

	item(float size) : size(size) {}
};

struct bin {
	float capacity;
	std::vector<item> contents;

	bin(float capacity = BIN_CAPACITY)
		: capacity(capacity)
	{}

	void addItem(float size) {
		this->contents.emplace_back(size);
		this->capacity -= size;
	}
};

void PrintBins(const std::vector<bin> & bins) {
	for ( int i = 0; i < bins.size(); ++i ) {
		std::cout << "Bin(" << (i + 1) << "), ";

		for ( auto const & item : bins.at(i).contents ) {
			std::cout << item.size << " ";
		}

		std::cout << "\n";
	}
}

// Next Fit Bin packing algorithm.
// For each item, if it fits in the last used bin put it there, else create a new bin.
void NextFit(const std::vector<float> & numbers, std::vector<bin> & bins) {
	if ( numbers.empty() ) {
		return;
	}

	bins.emplace_back();

	for ( const auto & number : numbers ) {
		// If the number exceeds the current bin's capacity, push a new one on.
		if ( number > bins.back().capacity ) {
			bins.emplace_back();
		}

		// Add the number to the current bin.
		bins.back().addItem(number);
	}
}

// First Fit Bin packing algorithm.
// Scan all bins for the first fit. Create a new bin only if that fails.
void FirstFit(const std::vector<float> & numbers) {
	// We start with 1 bin
	std::vector<bin> bins = {bin()};

	for ( const auto & number : numbers ) {
		bool found_first_fit = false;

		// Search all bins.
		for ( auto & bin : bins ) {
			if ( number <= bin.capacity ) {
				bin.addItem(number);
				found_first_fit = true;
				break;
			}
		}

		// Only if we couldn't find a bin large enough do we create a new one.
		if ( !found_first_fit ) {
			bins.push_back(bin());
			bins.back().addItem(number);
		}
	}

	PrintBins(bins);
}

void BestFit(const std::vector<float> & numbers) {
	std::vector<bin> bins = {};

	for ( const auto & number : numbers ) {
		if ( bins.empty() ) {
			bins.emplace_back();
			bins.back().addItem(number);
			continue;
		}

		bool best_fit_found = false;
		int best_fit_bin = -1;

		for ( auto i = 0; i < bins.size(); ++i ) {
			// If it can fit in this bin
			if ( number <= bins.at(i).capacity) {
				if ( best_fit_bin == -1 || bins.at(i).capacity < bins.at(best_fit_bin).capacity ) {
					best_fit_bin = i;
					best_fit_found = true;
				}
			}
		}

		if ( !best_fit_found ) {
			bins.emplace_back();
			bins.back().addItem(number);
		} else {
			bins.at(best_fit_bin).addItem(number);
		}
	}

	PrintBins(bins);
}

int main() {
	std::vector<float> items = {
		0.42, 0.25, 0.27, 0.07, 0.72, 0.86, 0.09, 0.44, 0.50, 0.68, 0.73, 0.31, 0.78, 0.17, 0.79, 0.37, 0.73, 0.23, 0.30
	};

	std::cout << "Next Fit\n";
	std::vector<bin> next_fit_bins;
	NextFit(items, next_fit_bins);
	PrintBins(next_fit_bins);

	std::cout << "First Fit\n";
	FirstFit(items);

	std::cout << "Best Fit\n";
	BestFit(items);

	return EXIT_SUCCESS;
}
