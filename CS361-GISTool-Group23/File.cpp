#include "File.hpp"

bool openFile(ifstream &inputFile, string fileName) {
	inputFile.open(fileName);
	return !inputFile;
}

bool openFile(ofstream &outputFile, string fileName) {
	outputFile.open(fileName);
	return !outputFile;
}

void closeFile(ifstream &inputFile) {
	if (inputFile)
		inputFile.close();
}

void closeFile(ofstream &outputFile) {
	if (outputFile)
		outputFile.close();
}

vector<int> readFile(ifstream &inputFile, vector<int> &values) {
	int input;

	while (inputFile >> input) {
		values.push_back(input);
	}
	return values;
}

void writeFile(ofstream &outputFile, vector<int> sorted) {
	for (int i = 0; i < sorted.size(); i++) {
		outputFile << sorted[i] << " ";
	}
}

// appends .txt to the file name if the proper file type extension is not used
// was skipping first getString, the was leaving an extra \n in the buffer
// this has modified my getStringInput that I will continue using
// http://www.cplusplus.com/forum/general/66029/
string getFileName(string message) {
	string fileName;

	cout << message;

	fileName = getStringInput();

	if (fileName.length() > 4 &&
		fileName.substr(fileName.length() - 4) == ".txt") {
		return fileName;
	}
	else {
		return fileName.append(".txt");
	}
}
