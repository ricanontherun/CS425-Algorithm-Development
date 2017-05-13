#include <iostream>
#include <vector>

template <typename T>
void PrintCommaSeparated(const std::vector<T> & v) {
	if ( v.empty() ) {
		return;
	}

	std::size_t size = v.size();
	int i = 0;

	for ( ; i < size - 1; ++i ) {
		std::cout << v[i] << ",";
	}

	std::cout << v[i] << "\n";
}

template <typename T>
void insertion_sort(std::vector<T> & v) {
	std::size_t size = v.size();

	if ( size <= 1 ) {
		return;
	}

	for ( std::size_t p = 1; p < size; ++p  ) {
		T tmp = std::move(v[p]);

		int q;
		for ( q = p; q > 0 && tmp < v[q - 1]; --q ) {
			v[q] = std::move(v[q - 1]);
		}

		v[q] = std::move(tmp);
	}
}

template <typename Comparable>
void shellsort( std::vector<Comparable> & a )
{
	int distances[] = {7,3,1};

	for( int distance : distances ) {
//	for( int distance = a.size( ) / 2; distance > 0; distance /= 2 ) {
		for( int i = distance; i < a.size(); ++i ) {
			Comparable tmp = std::move(a[i]);
			int j = i;

			for( ; j >= distance && tmp < a[j - distance]; j -= distance ) {
				a[j] = std::move(a[j - distance]);
			}

			a[j] = std::move(tmp);
		}

		PrintCommaSeparated(a);
	}
}

int main() {
	std::vector<int> v = {9,8,7,6,5,4,3,2,1};

	shellsort(v);
}
