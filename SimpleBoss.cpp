// A simple boss program to demonstrate inheritance
#include <iostream>

using namespace std;

class Enemy {
public:
	int damage;
	Enemy();
	void Attack();
};

Enemy::Enemy() {
	damage = 10;
}

void Enemy::Attack() {
	cout << "Damage: " << damage << endl;
}

// Derived classes don't inherit constructors, destructors, copy constructors, overloaded assignment operators
// However during the creation or destruction of the derived class objects the respective constructor or destructor of the base class is called
// When a Boss ob is created an Enemy constructor is also called followed by the Boss constructor
class Boss : public Enemy {
public:
	int damageMultiplier;
	Boss();
	void SpecialAttack();
};

Boss::Boss() {
	damageMultiplier = 5;
}

void Boss::SpecialAttack() {
	cout << "Damage: " << damage * damageMultiplier << endl;
}

int main() {
	cout << "Enemy: \n";
	Enemy ob1;
	ob1.Attack();
	cout << "Boss: \n";
	Boss ob2;
	ob2.Attack();
	ob2.SpecialAttack();
	return 0;
}