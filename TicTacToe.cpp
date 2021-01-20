#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//global constants
const char x = 'X';
const char o = 'O';
// writing empty instead gives an ambiguous symbol error as it conflicts with pre-defined empty
const char EMPTY = ' ';
const char NO_ONE = 'N';
const char tie = 'T';

//function prototypes
void instructions();
char askYesNo(string question);
int askNumber(string question, int hight, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(int move, const vector<char>& board);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

int main() {
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = x;

	displayBoard(board);

	while (winner(board) == NO_ONE) {
		if (turn == human) {
			move = humanMove(board, human);
			board[move] = human;
		}
		else {
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}
	announceWinner(winner(board), computer, human);
	return 0;
}

void instructions() {
	cout << "Tic-Tac-Toe\n Make your move by entering a number between 0-8\n";
	cout << "This corresponds to the board position as shown:\n";
	cout << "0|1|2\n3|4|5\n6|7|8\nEnter your choice: ";
}

char askYesNo(string question) {
	char response;
	do {
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');

	return response;
}

int askNumber(string question, int high, int low) {
	int number;
	do {
		cout << question << "(" << low << "-" << high << "): ";
		cin >> number;
	} while (number > high || number < low);

	return number;
}

char humanPiece() {
	char go_first = askYesNo("Do you want to make the first move? ");
	if (go_first == 'y') {
		cout << "\nTake the first move\n";
		return x;
	}
	else {
		cout << "\nI'll go first\n";
		return o;
	}
}

char opponent(char piece) {
	if (piece == x)
		return o;
	else
		return x;
}

void displayBoard(const vector<char>& board) {
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}

char winner(const vector<char>& board) {
	// all possible winning rows
	const int WINNING_ROWS[8][3] = { {0,1,2}, {3,4,5},
									 {6,7,8}, {0,3,6},
									 {1,4,7}, {2,5,8},
									 {0,4,8}, {2,4,6} };
	// check whether either player has won
	// winning row has 3 values that are the same and not EMPTY
	// if such a thing happens then we have a winner
	const int TOTAL_ROWS = 8;
	for (int row = 0;row < TOTAL_ROWS;row++) {
		if ((board[WINNING_ROWS[row][0]] != EMPTY) && 
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) && 
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {
			return board[WINNING_ROWS[row][0]];
		}
	}

	// If neither player has won yet check for a tie i.e. no EMPTY squares left
	// I use count algorithm for this
	if (count(board.begin(), board.end(), EMPTY) == 0)
		return tie;

	// If neither player has won yet but the game isn't a tie
	return NO_ONE;
}

// using inline as the fn is just 1 line long
inline bool isLegal(int move, const vector<char>& board) {
	return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human) {
	int move = askNumber("Where will you move?", (board.size() - 1));
	while (!isLegal(move, board)) {
		cout << "Aldready occupied try again\n";
		move = askNumber("Where will you move?", (board.size() - 1));
	}
	cout << "OK..\n";
	return move;
}

// Determine the best position of the board
// Here I use pass by value so that the original board remains unchanged
// Also I'm free to change the copy of the board to find the best position available

// Tic-tac-toe games considers only the next move whereas other strategy games may compute a lot of future moves and positions
// As tic-tac-toe has a few possible combinations, it makes it fairly easy to play
int computerMove(vector<char> board, char computer) {
	unsigned int move = 0;
	bool found = false;
	// if the computer can win the next move, that's the move to make
	// loop through each available position in the board, set that pos to computer's char
	// check if it wins in the position and save the result in found. If it wins it exits the loop else checks next pos
	while (!found && move < board.size()) {
		if (isLegal(move, board)) {
			board[move] = computer;
			found = (winner(board) == computer);
			board[move] = EMPTY;
		}
		if (!found) {
			++move;
		}
	}
	// else if humans can win the next move, must prevent that
	if (!found) {
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size()) {
			if (isLegal(move, board)) {
				board[move] = human;
				found = (winner(board) == human);
				board[move] = EMPTY;
			}
			if (!found) {
				++move;
			}
		}
	}
	// else moving through the list of best moves in order of desirability and taking the first legal one
	if (!found) {
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4,0,2,6,8,1,3,5,7 };
		// pick the best open square
		while (!found && i < board.size()) {
			move = BEST_MOVES[i];
			if (isLegal(move, board)) {
				found = true;
			}
			i++;
		}
	}
	// at this point the position will have been found
	cout << "I take number: " << move << endl;
	return move;
}

void announceWinner(char winner, char computer, char human) {
	if (winner == computer) {
		cout << winner << "'s won!\nComputer wins!\n";
	}
	else if (winner == human) {
		cout << winner << "'s won!\nHuman wins!\n";
	}
	else {
		cout << "It's a tie!\n";
	}
}