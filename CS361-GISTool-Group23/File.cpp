#include "File.hpp"

bool openFile(ifstream &inputFile, string fileName) {
	inputFile.open(fileName);
	//return !inputFile;
	return 1;
}

bool openFile(ofstream &outputFile, string fileName) {
	outputFile.open(fileName);
	//return !outputFile;
	return 1;
}

void closeFile(ifstream &inputFile) {
	if (inputFile)
		inputFile.close();
}

void closeFile(ofstream &outputFile) {
	if (outputFile)
		outputFile.close();
}

string formatFileName(string fileName) {

	//cout << "fileName2: " << fileName << endl;

	if (fileName.length() > 4 &&
		fileName.substr(fileName.length() - 4) == ".png") {
		return fileName;
	}
	else {
		return fileName.append(".png");
	}
}

bool validFile(char* fileName) {
	// create filestream
	ifstream ifs;

	//cout << "fileName1: " << fileName << endl;

	// check if the name has .png or append it if it doesn't
	string name = formatFileName(fileName);

	//cout << "name: " << name << endl;

	//now try to open the file
	if (openFile(ifs, name)) {
		closeFile(ifs);
		return 1;
	}
	else {
		return 0;
	}
}

void getNewFiles(char **args) {
	const int numFiles = 2;
	char* files[numFiles];
	for (int i = 0; i < numFiles; i++) {
		files[i] = (char *)malloc(255 * sizeof(char));
	}

	// display "fake out" of command
	cout << args[0] << " " << args[1] << " ";

	// add on to the fake out for the user to type in the new files
	string str = getStringInput();

	//cout << "About to parse str: " << str << endl;

	// get the names of the files to a usable format
	// function call with the array gets the position in functions returned array
	for (int j = 0; j < numFiles; j++) {
		strcpy(files[j], parseInput(str, numFiles)[j]);
	}

	int i = 0;
	int j = 2;

	// doesn't really do much. if we could pass args by reference it would work
	while (i < numFiles) {
		//cout << "files[" << i << "]: " << files[i] << endl;
		strcpy(args[j], files[i]);
		i++;
		j++;
	}

	//change the return type to char** if this gets fixed, change it in the hpp too. 
	return;
}

// not in header, because we don't want other parts of the program using this
bool runProgram(int numArgs, char** parameters) {
	static int runAgain = 0;

	do {
		// this input validation will need to be played with depending on how this gets fixed
		if (numArgs != 4) {
			cout << "Invalid number of Arguments" << endl;
			break;
		}
		
		// check damage parameter
		if (strcmp(parameters[1], "road") != 0 && strcmp(parameters[1], "flood") != 0) {
			cout << "The damage type " << parameters[1] << " was not recognized. Try road or flood." << endl;
			return -1;
		}

		// check files
		if (!validFile(parameters[2])) {
			cout << "Could not open file 1: " << parameters[2] << endl;
			break;
		}

		if (!validFile(parameters[3])) {
			cout << "Could not open file 2: " << parameters[3] << endl;
			break;
		}

		cout << "All parameters look good." << endl;

		switch (playAgain()) {
		case 1:
			continue;
			break;
		case 2:
			strcpy(parameters[1], "road");
			// get new files
			getNewFiles(parameters);
			runAgain = 1;
			break;
		case 3:
			strcpy(parameters[1], "flood");
			// get new files
			getNewFiles(parameters);
			runAgain = 1;
			break;
		case 4:
			runAgain = 0;
			break;
		default:
			cout << "If you see this message please submit a bug report!" << endl;
			runAgain = 0;
			break;
		}

	} while (runAgain != 0);

	return false;
}

int main(int argc, char** argv) {

	while(runProgram(argc, argv));

	return 0;
}