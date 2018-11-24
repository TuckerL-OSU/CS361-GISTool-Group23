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

//vector<int> readFile(ifstream &inputFile, vector<int> &values) {
//	int input;
//
//	while (inputFile >> input) {
//		values.push_back(input);
//	}
//	return values;
//}
//
//void writeFile(ofstream &outputFile, vector<int> sorted) {
//	for (int i = 0; i < sorted.size(); i++) {
//		outputFile << sorted[i] << " ";
//	}
//}

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

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Invalid number of Arguments" << endl;
		return -1;
	}

	if (!validFile(argv[1])) {
		cout << "Could not open file 1: " << argv[1]  << endl;
		return -1;
	}

	if (!validFile(argv[2])) {
		cout << "Could not open file 2: " << argv[2] << endl;
		return -1;
	}

	return 0;
}