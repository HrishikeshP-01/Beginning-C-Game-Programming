#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
	srand(static_cast<unsigned int>(time(0)));
	cout << "Guess my number. It's between 1-100" << endl;
	int x = (rand() % 100) + 1;
	int y;
	for (int i = 1;i <= 5;i++) {
		cin >> y;
		if (y > x)
			cout << "Too high!" << endl;
		else if (y < x)
			cout << "Too low!" << endl;
		else {
			cout << "Right Answer. You win!" << endl;
			return 0;
		}
	}
	cout << "You lost. Answer was: " << x << endl;
	return 0;
}