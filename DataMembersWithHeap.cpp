// Using data members with heap
// We'll look at the use of copy constructors, destructors

#include <iostream>
#include <string>

using namespace std;

class Critter {
public:
	Critter(const string& name = "", int age = 0);
	// destructor
	~Critter();
	// copy constructor
	Critter(const Critter& c);
	// operator overloading
	Critter& Critter::operator=(const Critter& c);
	void Greet() const;
private:
	string* pName;
	int Age;
};

Critter::Critter(const string& name, int age) {
	cout << "Constructor called\n";
	pName = new string(name);
	Age = age;
}

// All objects have a default destructor but it has a shallow definition i.e. only the variables are deleted
// Here the a variable points to a memory location in heap the default destructor only deletes the variable i.e. the address therefore causing a leak
// We write a custom destructor to PREVENT MEMORY LEAKS
Critter::~Critter() { // destructor definition
	cout << "Destructor called\n";
	delete pName;
}

// The default copy constructor has a shallow deinition i.e. the variable's values are copied
// As the variable pName of c contains the address of the location in heap it's the address that's copied 
// So both object's pName point to the same location which is not what we want. We want 2 seperate copies
// So we write a custom copy constructor
// Also if we use the default constructor whenever any 1 of the objects gets destroyed then the variable pName of the other becomes a dangling pointer
// This way we PREVENT DANGLING POINTERS
Critter::Critter(const Critter& c) { // copy constructor definition
	cout << "Copy constructor called\n";
	pName = new string(*c.pName);
	Age = c.Age;
}

// while using the assignment operator the same concerns as above hold
// So we overload the assignment operator to make 2 seperate copies in the heap
Critter& Critter::operator=(const Critter& c) { // overloading assignment operator
	// do it only if the objects are different else it's a futile effort
	if (this != &c) {
		delete pName;
		pName = new string(*c.pName);
		Age = c.Age;
	}
	return *this;
}

void Critter::Greet() const {
	cout << "Name: " << *pName;
	cout << "&Name: " << &pName << endl;
}

void testDestructor();
void testCopyConstructor(Critter aCopy);
void testAssignmentOverloading();

int main() {
	testDestructor();
	cout << endl;
	Critter crit("P", 5);
	crit.Greet();
	testCopyConstructor(crit);
	crit.Greet();
	cout << endl;
	testAssignmentOverloading();
	return 0;
}

// Once this function ends ob gets destroyed 
void testDestructor() {
	Critter ob("Rover", 3);
	ob.Greet();
}

// As we use pass by value a copy of crit is created
void testCopyConstructor(Critter aCopy) {
	aCopy.Greet();
}

void testAssignmentOverloading() {
	Critter ob1("A", 4);
	Critter ob2("B", 7);
	ob1 = ob2;
	ob1.Greet();
	ob2.Greet();
	Critter ob3("X", 11);
	ob3 = ob3;
	ob3.Greet();
}