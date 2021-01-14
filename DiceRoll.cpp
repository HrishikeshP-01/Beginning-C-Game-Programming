#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
	int x = 1;
	srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

	/*Computers use a pseudo random number generator, something like a book of random numbers but the problem is that each time
	it starts from the beginning which means that the same result can be repeated any number of times to prevent this we use a seed.
	A seed basically makes it read from a different location. In this case the seed is the current date and time. As this changes with each iteration
	we can get a different result*/

	while (x == 1) {
		int m = rand(); // Generate the random number
		cout << (m % 6)+1 << endl << "Enter 1 to continue: ";
		cin >> x;
	}
}