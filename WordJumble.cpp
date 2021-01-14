#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
	enum fields{WORD, HINT, NUM_FIELDS}; // just to declare indices beforehand so that if there's a change we just have to make them here
	const int NUM_WORDS = 4;
	string WORDS[NUM_WORDS][NUM_FIELDS] = { {"hello","A greeting"},{"jumble","What this game's all about"},{"hrishi","my name"},{"excuse","courtesy"} };

	// Picking a random word
	srand(static_cast<unsigned int>(time(0)));
	int pick = (rand() % NUM_WORDS);
	string p = WORDS[pick][WORD];

	// Jumbling the word
	string jumbled = p;
	int l = jumbled.size();
	for (int i = 0;i < l;i++) {
		int index1 = rand() % l;
		int index2 = rand() % l;
		char temp = jumbled[index1];
		jumbled[index1] = jumbled[index2];
		jumbled[index2] = temp;
	}

	//Starting the game
	cout << "WORD JUMBLE\n Gues this word: " << jumbled << "\n type hint to get a hint" << endl;
	string input;
	while (true) {
		cin >> input;
		if (input == "hint")
			cout << WORDS[pick][HINT]<<endl;
		else if (input == p) {
			cout << "Right Answer. You won!" << endl;
			return 0;
		}
		else {
			cout << "Wrong Answer. You lose." << endl;
			return 0;
		}
	}
}