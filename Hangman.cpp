#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
using namespace std;
int main() {
	const int size = 3;
	string words[size] = { "hello","tell","cat" };
	string::iterator iter;
	srand(static_cast<unsigned int>(time(0)));
	int pick = (rand() % size);
	string TempWord = "";
	string Temp = words[pick];
	for (int i = 0;i < words[pick].size();i++)
		TempWord += "_";
	cout << "HANGMAN \nYou can make 8 incorrect guesse \nHere's the word: \n";
	int guess = 8;
	char g;
	while (guess > 0) {
		if (TempWord == words[pick]) {
			cout << "You Won!" << endl;
			return 0;
		}
		cout << TempWord << "\nMake your guess: ";
		cin >> g;
		iter = find(Temp.begin(), Temp.end(), g);
		if (iter != Temp.end()) {
			int pos = iter - Temp.begin(); // Calculate the index by stubtracting the pointers
			Temp[pos] = '_'; // Replace the value with _ so as to prevent getting the same index if the word has repeating letters eg: hello -> he_lo
			TempWord[pos] = g;
			cout << "Correct! The remaining: " << TempWord << endl;
		}
		else {
			cout << "Wrong! Guesses remaining: " << --guess;
		}
	}
	return 0;
}