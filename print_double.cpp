#include <iostream>
#include <iomanip>

void printDigit(int digit) {
	std::cout << digit;
}

// From the book.
void printOut( int n ) {
	if( n >= 10 )
		printOut( n / 10 );
	printDigit( n % 10 );
}

void printDouble(double d) {
	// Handle negative.
	if ( d < 0 ) {
		std::cout << '-';
		d = -d;
	}

	int decimal = static_cast<int>(d);
	double fractional = d - (double)decimal;

	// Print the decimal part.
	printOut(decimal);

	// No fractional part to print, just return.
	if ( fractional == 0.0 ) {
		return;
	}

	std::cout << '.';

	// I couldn't figure out how to print the fractional part!
}

int main() {
	printDouble(-12.34);
}
