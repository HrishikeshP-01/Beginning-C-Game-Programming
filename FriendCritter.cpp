#include <iostream>
#include <string>

using namespace std;

class Critter{
	friend void Peek(const Critter& aCritter);
	friend ostream& operator<<(ostream& os, const Critter& aCritter);
public:
	Critter(const string& name = "");
private:
	string Name;
}

Critter::Critter(const string& name):
	Name(name)
{}

void Peek(const Critter& aCritter);
ostream& operator<<(ostream& os, const Critter& aCritter);

int main() {
	Critter crit("Pooh");
	cout << "Calling Peek to access crit's private data member - Name : " << Peek(crit) << endl;
	cout << "Sending crit object to cout with the << operator: " << endl;
	cout << crit;
	return 0;
}

// Global friend function that can access all of Critter object's members
void Peek(const Critter& aCritter) {
	cout << aCritter.Name;
}

// Global friend fn that can access all of Critter object's members and overloads << operator to output the below details
ostream& operator<<(ostream& os, const Critter& aCritter) {
	os << "Critter object -";
	os << "Name : " << aCritter.Name;
	return os;
}

