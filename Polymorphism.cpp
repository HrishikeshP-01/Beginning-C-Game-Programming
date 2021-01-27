// A simple program to demonstrate polymorphism and dynamic binding

#include <iostream>

using namespace std;

class Enemy {
public:
	Enemy(int damage = 10);
	// A good rule of thumb is to create a virtual destructor if you have virtual fns in a class
	// If destructor isn't virtual, then due to early binding the Boss objects pointed by Enemy pointers will only call the enemy destructor
	// This might lead to memory leaks or dangling pointers so we make destructors virtual so as to implement late binding
	// The destructor would then be called only after inspecting the object
	virtual ~Enemy();
	void virtual Attack();
	void Early();
protected:
	int* D;
};

Enemy::Enemy(int damage) {
	D = new int(damage);
}

Enemy::~Enemy() {
	cout << "Enemy destructor\n";
	delete D;
	D = 0;
}

void Enemy::Attack() {
	cout << "Enemy attack: " << *D << endl;
}

void Enemy::Early() {
	cout << "Enemy early\n";
}

class Boss : public Enemy {
public:
	Boss(int damage = 20);
	virtual ~Boss();
	void virtual Attack();
	void Early();
protected:
	int* D;
};

Boss::Boss(int damage) {
	D = new int(damage);
}

Boss::~Boss() {
	cout << "Boss destructor\n";
	delete D;
	D = 0;
}

void Boss::Attack() {
	cout << "Boss attack: " << *D << endl;
}

void Boss::Early() {
	cout << "Boss early\n";
}

int main() {
	cout << "Going to call fns of Boss object through pointer to Enemy" << endl;
	/* Here we use an enemy pointer to point to a Boss object in heap
	A derived class' object is also a member of the base class
	as boss is the derived class of enemy, boss objects can be pointed by enemy pointers.
	The advantage of this is it allows us to write fns that deal with both enemy as well as boss objects.
	We can deal with objects irrespective of their exact type*/
	Enemy* obPointer = new Boss();
	// Virtual functions produce polymorphic behaviour through pointers as well as references
	// Virtual functions come with an overhead. Use it only when necessary
	// Functions of the derived class wouldn't have to know the exact type of object passed to it AS LONG AS THEY'VE BEEN DECLARED VIRTUAL
	// Function call is based on the type of object at runtime this is called late binding or dynamic bindin
	obPointer->Attack();
	// Early isn't a virtual function
	// If you try to override a non-virtual function, the function of the base class gets called
	// This is due to early binding or static binding
	obPointer->Early();
	cout << "Clearing heap and deleting pointer" << endl;
	delete obPointer;
	obPointer = 0;
	return 0;
}