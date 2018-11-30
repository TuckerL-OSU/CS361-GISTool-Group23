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

char** getNewFiles(char **args) {
	const int numFiles = 2;
	char* files[numFiles];
	for (int i = 0; i < numFiles; i++) {
		files[i] = (char *)malloc(255 * sizeof(char));
	}

	// display "fake out" of command
	cout << args[0] << " " << args[1] << " ";

	//char* str = getCharInput();
	string str = getStringInput();

	//cout << "About to parse str: " << str << endl;

	// get the names of the files to a usable format
	// function call with the array gets the position in to functions returned array
	for (int j = 0; j < numFiles; j++) {
		strcpy(files[j], parseInput(str, numFiles)[j]);
	}

	int i = 0;
	int j = 2;

	while (i < numFiles) {
		//cout << "files[" << i << "]: " << files[i] << endl;
		strcpy(args[j], files[i]);
		i++;
		j++;
	}

	return;
}

// not in header, because we don't want other parts of the program using this
bool runProgram(char** parameters) {
	static int runAgain = 1;
	
	while (runAgain != 0) {
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
			break;
		case 3:
			strcpy(parameters[1], "flood");
			// get new files
			getNewFiles(parameters);
			break;
		case 4:
			runAgain = 0;
			break;
		default:
			cout << "If you see this message please submit a bug report!" << endl;
			runAgain = 0;
			break;
		}

	}

	return false;
}

int main(int argc, char** argv) {
	if (argc != 4) {
		cout << "Invalid number of Arguments" << endl;
		return -1;
	}

	// check damage parameter
	if (strcmp(argv[1], "road") != 0 && strcmp(argv[1], "flood") != 0) {
		cout << "The damage type " << argv[1] << " was not recognized. Try road or flood." << endl;
		return -1;
	}

	while(runProgram(argv));

	return 0;
}