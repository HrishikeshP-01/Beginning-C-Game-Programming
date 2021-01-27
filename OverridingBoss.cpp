// Program that demonstrates calling and overriding base member functions

#include <iostream>

using namespace std;

class Enemy {
public:
	Enemy(int damage = 10);

	// If a base member function will be overwritten it must've virtual keyword in function declaration
	void virtual Attack() const;
	void virtual Taunt() const;
private:
	int D;
};

Enemy::Enemy(int damage) {
	D = damage;
}

// virtual keyword is necessary only in function declaration and not in definition
void Enemy::Attack() const{
	cout << "Damage: " << D << endl;
}

void Enemy::Taunt() const{
	cout << "Enemy Taunts" << endl;
}

class Boss : public Enemy {
public:
	Boss(int damage = 10);
	// All the virtual fns in base class are virtual automatically in the derived class without having to explicitly declare them
	void virtual Attack() const; // virtual keyword optional
	void virtual Taunt() const; // virtual keyword optional
private:
	int multipleD;
};

Boss::Boss(int damage) :
	Enemy(damage)
{
	multipleD = damage / 2;
}

void Boss::Attack() const{
	Enemy::Attack();
	cout << "Extra damage: " << multipleD << endl;
}

void Boss::Taunt() const{
	cout << "Boss Taunts" << endl;
}

int main() {
	Enemy ob1;
	ob1.Taunt();
	ob1.Attack();
	
	Boss ob2(30);
	ob2.Taunt();
	ob2.Attack();
	return 0;
}