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

char** parseInput(string str, int numFiles) {
//char** parseInput(char* str, int numFiles) {
	char** parsedStr = (char **)malloc(numFiles * sizeof(char *));
	for (int i = 0; i < numFiles; i++) {
		parsedStr[i] = (char *)malloc(255 * sizeof(char));
	}
	string delimiter = " ";

	cout << "Parsing str: " << str << endl;

	size_t pos = 0;
	string token;
	while ((pos = str.find(delimiter)) != string::npos) {
		token = str.substr(0, pos);
		cout << token << endl;
		str.erase(0, pos + delimiter.length());
	}


	//int i = 0;
	//int j = 0;
	//int k = 0;
	//
	//while (j < numFiles) {
	//	while ((strcmp(str.c_str(), delimiter) && (strcmp(str.substr(i, i), "/n") != 0)) {
	//		i++;
	//	}
	//	strcpy(parsedStr[j], str.substr(k, i).c_str());

	//	j++;
	//	k = i + 1;
	//}

	

	//while (j < numFiles) {
	////while (strcmp(str + i, "/n") != 0) {
	//	if (str.substr(i,i) != delimiter || str.substr(i, i) != "/n") {
	//		cout << "str[i(" << i << "): " << str.substr(i, i) << endl;

	//		strcpy(parsedStr[j], str.substr(k, i).c_str());
	//		//cout << "parsedStr[j(" << j << ")] + k(" << k << "): " << parsedStr[j] + k << endl;

	//		/*k++;*/
	//	}
	//	else {
	//		j++;
	//		k = i + 1;
	//		i = 0;
	//	}

	//	//if (i == 5) {
	//	//	break;
	//	//}

	//	// when the delimiter is hit, it will allow the nested while to read the next parameter
	//	// into the next bin in parsed
	//	i++;
	//}

	cout << "Ending Parsing parsed: "; 
	for (int x = 0; x < numFiles; x++) {
		cout << parsedStr[x] << endl;
	}

	return parsedStr;
}

char* getCharInput() {
	string str = "";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	getline(cin, str);
	//cout << "cin input: " << str << endl;
	char *input = new char[str.length() + 1];
	strcpy(input, str.c_str());
	//cout << "char input: " << input << endl;
	return input;
}

int RNG(int min, int max) {
	return (rand() % max) + min;
}

int playAgain() {
	int tempChoice = 0;

	std::cout << "Would you like to run another test?" << std::endl;
	std::cout << "1. Exact Same Test" << std::endl;
	std::cout << "2. New Road Damage Test" << std::endl;
	std::cout << "3. New Flood Damage Test" << std::endl;
	std::cout << "4. Quit" << std::endl;



	tempChoice = getInteger("Enter an option: ", 1, 4);

	switch (tempChoice) {
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 4;
		break;
	default:
		return 0;
	}
}