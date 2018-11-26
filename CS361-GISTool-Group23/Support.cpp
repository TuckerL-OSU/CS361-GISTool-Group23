#include "Support.hpp"

int getInteger(string message, int min, int max) {
	string str = "";
	int newStr = 0;
	bool intCheck = false;

	//cout << message;
	while (!intCheck) {
		cin >> str;
		stringstream stream(str);

		if (stream >> newStr) {
			string remainingStr;
			getline(stream, remainingStr);

			if (newStr < min || newStr > max) {
				cout << message;
			}
			else if (remainingStr == "") {
				intCheck = true;
			}
			else {
				cout << message;
			}
		}
		else {
			cout << message;
		}
	}
	return newStr;
}

string getStringInput() {
	string input = "";
	if (cin.peek() == '\n') {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	getline(cin, input);
	return input;
}

char getCharInput(string message) {
	char input = ' ';
	string str = "";
	bool charCheck = false;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//cout << message;
	while (!charCheck) {
		cin >> str;
		stringstream stream(str);

		if (stream >> input) {
			string remainingStr;
			getline(stream, remainingStr);

			if (remainingStr == "") {
				charCheck = true;
			}
			else {
				cout << message;
			}
		}
		else {
			cout << message;
		}
	}
	return tolower(input);
}

int RNG(int min, int max) {
	return (rand() % max) + min;
}

bool playAgain() {
	int tempChoice = 0;

	std::cout << "Would you like to play again?" << std::endl;
	std::cout << "1. Yes." << std::endl;
	std::cout << "2. No." << std::endl;

	tempChoice = getInteger("Enter an option: ", 1, 2);

	switch (tempChoice) {
	case 1:
		return true;
		break;
	case 2:
		return false;
		break;
	default:
		return 0;
	}
}