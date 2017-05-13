#include <iostream>

#define CENTS_IN_COIN(coin) ( (coin) )
#define CENTS_IN_DOLLARS(dollars) ( (dollars) * 100 )

std::uint16_t ranked_currency[] = {
	CENTS_IN_DOLLARS(100),
	CENTS_IN_DOLLARS(50),
	CENTS_IN_DOLLARS(25),
	CENTS_IN_DOLLARS(10),
	CENTS_IN_DOLLARS(5),
	CENTS_IN_DOLLARS(1),
	CENTS_IN_COIN(25),
	CENTS_IN_COIN(10),
	CENTS_IN_COIN(5),
	CENTS_IN_COIN(1)
};

void MakeChange(float change) {
	float change_in_cents = change * 100.00;

	for ( std::uint16_t currency : ranked_currency ) {
		int times = change_in_cents / currency;

		if (times < 0) {
			continue;
		}

		std::cout << currency << ": " << times << "\n";
		change_in_cents -= (times * currency);
	}
}

int main(int argc, char ** argv) {
	if ( argc == 1 ) {
		return EXIT_FAILURE;
	}

	float change = atof(argv[1]);

	MakeChange(change);
}
