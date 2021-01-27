// Program to show the use of access specifiers in inheritance

#include <iostream>

using namespace std;

class Enemy {
public:
	Enemy();
	void Attack();

// Protected members can only be used in a class and its derieved classes
protected:
	int damage;
};

Enemy::Enemy() {
	damage = 10;
}

void Enemy::Attack() {
	cout << "Attack: " << damage << endl;
}

/** declaring the base class as public means all the public members of the base class become public members of the derived class,
protected members of the base class become protected members of the derived class and
private members of the base class are inacessible by the derived class (we can use getters and setters for using those) **/
class Boss : public Enemy {
public:
	Boss();
	void SpecialAttack();
protected:
	int damageMultiplier;
};

Boss::Boss() {
	damageMultiplier = 5;
}

void Boss::SpecialAttack() {
	cout << "Attack: " << damageMultiplier*damage << endl;
}

int main() {
	cout << "Enemy:\n";
	Enemy ob1;
	ob1.Attack();
	cout << "Boss:\n";
	Boss ob2;
	ob2.Attack();
	ob2.SpecialAttack();
}