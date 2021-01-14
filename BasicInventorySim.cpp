#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main() {
	vector<string> inventory;
	vector<string>::iterator myIterator;
	vector<string>::const_iterator cIter;
	cout << "Enter \n1. To insert \n2. To print inventory \n3. To remove items\4 To print str length of items \n5 To exit";
	int choice = 0;
	string new_item;
	int index, i;
	while (choice != 5) {
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Enter item" << endl;
			cin >> new_item;
			inventory.push_back(new_item);
			break;
		case 2:
			for (cIter = inventory.begin();cIter != inventory.end();cIter++) {
				cout << (*cIter) << endl;
			}
			break;
		case 3: 
			cout << "Enter index of item to be removed: ";
			cin >> index;
			inventory.erase(inventory.begin() + index);
			break;
		case 4:
			cout << "Enter index of item: ";
			cin >> i;
			myIterator = inventory.begin() + i;
			cout << myIterator->size() <<endl;
			break;
		case 5:
			break;
		}
	}
}
