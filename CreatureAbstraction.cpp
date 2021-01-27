// Program to demonstrate the use of abstract classes

#include <iostream>

using namespace std;

class Creature {
public:
	Creature(int health = 100);
	// Pure virtual function i.e. it doesn't have a function definition
	// Define it by using a = 0 at the end of the function declaration
	// Doesn't make sense to define greet as different creatures have different sounds
	void virtual Greet() const = 0;
	// Makes sense to define health as all creatures display health in the same way
	void virtual Health();
protected:
	int H;
};

Creature::Creature(int health) {
	H = health;
}

void Creature::Health() {
	cout << "Health: " << H << endl;
}

class Orc : public Creature {
public:
	Orc(int health = 200);
	virtual void Greet() const;
};

Orc::Orc(int health) :
	Creature(health) {}

void Orc::Greet() const{
	cout << "Orc says hi!\n";
}

int main() {
	Creature* pCreature = new Orc();
	pCreature->Health();
	pCreature->Greet();
	delete pCreature;
	pCreature = 0;
	return 0;
}