// A basic High Scores simulation which uses sort, find and random_shuffle STL algorithms

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	vector<int> scores;
	vector<int>::iterator iter;
	vector<int>::const_iterator CIter;
	cout << "Enter \n1. To add score\n2. To search for a score \n3. To shuffle scores \n4. To sort scores \n5. To print scores \n6. To exit \n";
	int choice = 0;
	int s;
	while (choice != 6) {
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Enter score: ";
			cin >> s;
			scores.push_back(s);
			break;
		case 2:
			cout << "Enter score to search: ";
			cin >> s;
			iter = find(scores.begin(), scores.end(), s);
			if (iter != scores.end())
				cout << "Score Found\n";
			else
				cout << "Score Not Found\n";
			break;
		case 3:
			srand(static_cast<unsigned int>(time(0)));
			random_shuffle(scores.begin(), scores.end());
			break;
		case 4:
			sort(scores.begin(), scores.end());
			break;
		case 5:
			for (CIter = scores.begin();CIter != scores.end();CIter++) {
				cout << (*CIter) << endl;
			}
			break;
		}
	}
}