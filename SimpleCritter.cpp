// A simple Critter game
#include <iostream>
#include <string>

using namespace std;

class Critters {
public:
	int hunger, boredom;
	Critters(int h = 0, int b = 0);
	void GetMood();
	void Talk();
	void Feed();
	static int number;
};

int Critters::number = 0;

Critters::Critters(int h, int b) {
	hunger = h;
	boredom = b;
}

void Critters::GetMood() {
	if (boredom != 10) // Just increasing boredom for no reason
		boredom++;
	cout << "My boredom level is: " << boredom << endl;
}

void Critters::Talk() {
	cout << "You have " << number << " of critters." << endl;
}

void Critters::Feed() {
	if (hunger != 10) {
		hunger++;
		cout << "Hunger level is: " << hunger <<endl;
	}
	else {
		cout << "I'm aldready full" << endl;
	}
}

int main() {
	Critters ob;
	Critters::number++;
	cout << "1. To Talk \n2. To Feed \n3.To Get Mood \n4. To make a new critter \n5. To Quit";
	int choice = 0;
	while (choice != 5) {
		cin >> choice;
		switch (choice) {
		case 1: ob.Talk();
			break;
		case 2: ob.Feed();
			break;
		case 3: ob.GetMood();
			break;
		case 4: ob.number++;
			break;
		}
	}
	return 0;
}