#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// Card class
class Card {
public:
	enum rank{ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
	enum suit{SPADES, CLUBS, DIAMONDS, HEARTS};
	// overloading << operator to display card
	friend ostream& operator<<(ostream& os, const Card& aCard);
	Card(rank r = ACE, suit s = SPADES, bool ifu = true);
	int getValue() const;
	void Flip();
private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) {
	m_Rank = r;
	m_Suit = s;
	m_IsFaceUp = ifu;
}

int Card::getValue() const {
	int value = 0;
	// if card is face down, its value is 0
	if (m_isFaceUp) {
		value = m_Rank;
		if (value > 10)
			value = 10;
	}
	return m_Rank;
}

void Card::Flip() const {
	m_IsFaceUp = !m_IsFaceUp;
}

class Hand {
public:
	Hand();
	virtual ~Hand();
	// adds a card to the hand
	void Add(Card* pCard);
	// clears the hand of all cards
	void Clear();
	// gets total hand value, intelligently treats aces as 1 or 11
	int GetTotal() const;
protected:
	vector<Card*> m_Cards;
};

Hand::Hand() {
	m_Cards.reserve(7);
}

Hand::~Hand() {
	Clear();
}

void Hand::Add(Card* pCard) {
	m_Cards.push_back(pCard);
}

void Hand::Clear() {
	vector<Card*>::iterator iter = m_Cards.begin();
	// free all memory on the heap
	for (iter = m_Cards.begin();iter <= m_Cards.end();iter++) {
		delete* iter;
		*iter = 0;
	}
	// clear vector of pointers
	m_Cards.clear();
}

int Hand::GetTotal() const{
	// if no cards in hand return 0
	if (m_Cards.empty())
		return 0;
	// if first card is face down, its value is. In that case return  
	if (m_Cards[0]->getValue() == 0)
		return 0;
	// add up card values, treat each ace as 1
	int total = 0;
	vector<Card*>::iterator iter;
	bool ContainsAce;
	for (iter = m_Cards.begin();iter <= m_Cards.end();iter++) {
		total += *iter->getValue();
		if ((*iter)->getValue() == Card::ACE)
			ContainsAce = true;
	}
	// if hand contains an ace and total is less than 11, treat the ace as 11
	if (ContainsAce && total <= 11) {
		total += 10; // As 1 aldready has been added
	}
	return total;
}

// Generic player contains common elements of a human and computer player
class GenericPlayer :public Hand {
	friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
public:
	GenericPlayer(const string& name = "");
	virtual ~GenericPlayer();
	// indicates whether or not player wants to keep hitting
	// abstract fn as const=0
	virtual bool IsHitting() const = 0;
	// returns whether generic player has busted i.e. total > 21
	bool isBusted() const;
	// announces that the generic player busts
	void Bust() const;
protected:
	string m_Name;
};

GenericPlayer::GenericPlayer(const string& name) {
	m_Name = name;
}

GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::isBusted() const {
	return (GetTotal() > 21);
}

void GenericPlayer::Bust() const {
	cout << m_Name << " busts\n";
}

class Player :public GenericPlayer {
public:
	Player(const string& name = "");
	virtual ~Player();
	virtual bool IsHitting() const;
	// announces that player wins
	void Win() const;
	// announces that player loses
	void Lose() const;
	// announces that the player pushes
	void Push() const;
};

Player::Player(const string& name) {
	m_Name = name;
}

Player::~Player(){}

bool Player::IsHitting() const {
	cout << m_Name << " do you want to hit?(y/n)\n";
	char response;
	cin >> response;
	return (response == 'y' || response == 'Y');
}

void Player::Win() const {
	cout << m_Name << " wins\n";
}

void Player::Lose() const {
	cout << m_Name << " loses\n";
}

void Player::Push() const {
	cout << m_Name << " pushes\n";
}

class House : public GenericPlayer {
public:
	House(const string& name = "House");
	virtual ~House();
	// indicates whether house is hitting - will always hit on <=16
	virtual bool isHitting() const;
	// flips over first card
	void FlipFirstCard();
};

House::House(const string& name) {
	GenericPlayer(name);
}

House::~House(){}

bool House::IsHitting() const {
	return (GetTotal() <= 16);
}

void House::FlipFirstCard() {
	if (!m_Cards.empty())
		m_Cards[0]->Flip();
	else
		cout << "No card to flip\n";
}

class Deck : public Hand {
public:
	Deck();
	virtual ~Deck();
	// create a standard deck of 52 cards
	void Populate();
	// shuffle cards
	void Shuffle();
	// deal one card to a hand
	void Deal(Hand& aHand);
	// give additional cards to a generic player
	void AdditionalCards(GenericPlayer& aGenericPlayer);
};

Deck::Deck() {
	m_Cards.reserve(52);
	Populate();
}

Deck::~Deck(){}

void Deck::Populate() {
	Clear();
	// create a standard deck
	for (int s = Card::CLUBS; s <= Card::SPADES;++s) {
		for (int r = Card::ACE;r <= Card::KING;++r) {
			Add(new Card(static_cast<Card::rank>(r)), static_cast<Card::suit>(s));
		}
	}
}

void Deck::Shuffle() {
	random_shuffle(m_Cards.begin(), m_Cards.end());
}

void Deck::Deal(Hand& aHand) {
	if (!m_Cards.empty()) {
		aHand.Add(m_Cards.back());
		m_Cards.pop_back();
	}
	else {
		cout << "Out of cards. Unable to deal.";
	}
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer) {
	cout << endl;
	// continue to deal a card as long as generic player isn't busted
	// and he wants to another hit
	while (!(aGenericPlayer.isBusted()) && aGenericPlayer.IsHitting()) {
		Deal(aGenericPlayer);
		cout << aGenericPlayer << endl;
		if (aGenericPlayer.isBusted()) {
			aGenericPlayer.Bust();
		}
	}
}

class Game {
public:
	Game(const vector<string>& names);
	~Game();
	// plays the game of blackjack
	void Play();
private:
	Deck m_Deck;
	House m_House;
	vector<Player> m_Players;
};

Game::Game(const vector<string>& names) {
	// create a vector of players from a vector of names
	vector<string>::const_iterator pName;
	for (pName = names.begin();pName != names.end();++pName) {
		m_Players.push_back(Player(*pName));
	}
	// seed the random number generator
	srand(static_cast<unsigned int>(time(0)));
	m_Deck.Populate();
	m_Deck.Shuffle();
}

Game::~Game(){}

void Game::Play() {
	// deal initial 2 cards to everyone
	vector<Player>::iterator pPlayer;
	for (int i = 0;i < 2;i++) {
		for (pPlayer = m_Players.begin();pPlayer != m_Players.end();++pPlayer) {
			m_Deck.Deal(*pPlayer);
		}
		m_Deck.Deal(m_House);
	}
	// hide the house's first card
	m_House.FlipFirstCard();
	// display everyone's hand
	for (pPlayer = m_Players.begin();pPlayer != m_Players.end();++pPlayer) {
		cout << *pPlayer << endl;
	}
	cout << m_House << endl;
	// deal additional cards to players
	for (pPlayer = m_Players.begin();pPlayer != m_Players.end();++pPlayer) {
		m_Deck.AdditionalCards(*pPlayer);
	}
	// reveal house's first card
	m_House.FlipFirstCard();
	cout << endl << m_House;
	// deal additional cards to house
	m_Deck.AdditionalCards(m_House);
	if (m_House.isBusted()) {
		// everyone still playing wins
		for (pPlayer = m_Players.begin();pPlayer != m_Players.end();pPlayer++) {
			if (!(pPlayer->isBusted())) {
				pPlayer->Win();
			}
		}
	}
	else {
		// compare each player still playing to house
		for (pPlayer = m_Players.begin();pPlayer != m_Players.end();pPlayer++) {
			if (!(pPlayer->isBusted())) {
				if (pPlayer->GetTotal() > m_House.GetTotal()) {
					pPlayer->Win();
				}
				else if (pPlayer->GetTotal() < m_House.GetTotal() {
					pPlayer->Lose();
				}
				else {
					pPlayer->Push();
				}
			}
		}
	}
	// remove everyone's cards
	for (pPlayer = m_Players.begin();pPlayer != m_Players.end();++pPlayer) {
		pPlayer->Clear();
	}
	m_House.Clear();
}

// function prototype
ostream& operator<<(ostream& os, const Card& aCard);
ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

int main() {
	cout << "Welcome to Blackjack!\n";
	int numPlayers = 0;
	while (numPlayers < 1 && numPlayers>7) {
		cout << "How many players?\n";
		cin >> numPlayers;
	}
	vector<string> names;
	string name;
	for (int i = 0;i < numPlayers;i++) {
		cout << "Enter player name: ";
		cin >> name;
		names.push_back(name);
	}
	cout << endl;
	// the game loop
	Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N') {
		aGame.Play();
		cout << "\nDo you want to play again? (Y/N): ";
		cin >> again;
	}
	return 0;
}

// overloads << operator so Card object can be sent to cout
ostream& operator<<(ostream& os, const Card& aCard) {
	// begin array with 0 to compensate for the fact that rank enum defined in Card begins at 1
	// this way RANKS[1] = A
	const string RANKS[] = { "0","A","2","3","4","5","6","7","8","9","10",
							"J","Q","K" };
	const string SUITS[] = { "c","d","h","s" };
	if (aCard.m_IsFaceUp) {
		os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
	}
	else {
		os << "XX";
	}
	return os;
}

// overloads << operator so a GenericPlayer object can be sent to cout
ostream& operator<<(ostream& os, const GenericPlayer aGenericPlayer) {
	os << aGenericPlayer.m_Name << ":\t";
	vector<Card*>::const_iterator pCard;
	if (!aGenericPlayer.m_Cards.empty()) {
		for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end();++pCard) {
			os << *(*pCard) << "\t";
		}
		if (aGenericPlayer.GetTotal() != 0) {
			cout << "(" << aGenericPlayer.GetTotal() << ")";
		}
	}
	else {
		os << "<empty>";
	}
	return os;
}