// Game Lobby

#include <iostream>
#include <string>

using namespace std;

// Instead of using STL I'll use a custom data member here as that's common in game programming
// Here I've created a Player data member that has a name value and the pointer to the next player
class Player {
public:
	Player(const string& name = "");
	string getName() const;
	Player* getNext() const;
	void setNext(Player* next);
private:
	string Name;
	Player* pNext;
};

Player::Player(const string& name) {
	Name = name;
	pNext = 0;
}

string Player::getName() const {
	return Name;
}

Player* Player::getNext() const {
	return pNext;
}

void Player::setNext(Player* next) {
	pNext = next;
}

class Lobby {
	friend ostream& operator<<(ostream& os, const Lobby& aLobby);
public:
	Lobby();
	~Lobby();
	void AddPlayer();
	void RemovePlayer();
	void Clear();
private:
	Player* pHead;
	Player* pTail;
};

Lobby::Lobby() {
	pHead = 0;
	pTail = 0;
}

Lobby::~Lobby() {
	Clear();
}

void Lobby::AddPlayer() {
	cout << "Enter name of player: ";
	string n;
	cin >> n;
	Player* newPlayer = new Player(n);
	pTail->setNext(newPlayer);
	if (pHead == 0)
		pHead = pTail;
}

void Lobby::RemovePlayer() {
	if (pHead == 0) {
		cout << "Lobby is empty\n";
		pTail = 0;
	}
	else {
		Player* temp = pHead;
		pHead = pHead->getNext();
		delete temp;
	}
}

void Lobby::Clear() {
	while (pHead != 0) {
		RemovePlayer();
	}
}

ostream& operator<<(ostream* os, Lobby* aLobby) {
	Player* pIter = aLobby.pHead;
	os << "\nPeople in Lobby:\n";
	if (pIter == 0) {
		os << "Empty";
	}
	else {
		while (pIter != 0) {
			pIter->getName();
			pIter = pIter->getNext();
		}
	}
	return os;
}

int main() {
	cout << "0. Exit \n1. Add Player \n2. Remove Player \n3. Print List\n";
	int c = 5;
	Lobby lobby;
	while (c != 0) {
		cin >> c;
		switch (c) {
		case 1:
			lobby.AddPlayer();
			break;
		case 2:
			lobby.RemovePlayer();
			break;
		case 3:
			cout << lobby;
			break;
		}
	}
}