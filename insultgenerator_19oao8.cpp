/*
 * TestInsultGenerator.cpp
 *
 *      Author: Alan McLeod
 *      A testing program for CISC320 assignment 1.
 */

/*#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "insultgenerator_19oao8.h"

using namespace std;

int main() {

	InsultGenerator ig;
	vector<string> insults;
	clock_t start = 0, finish = 0;

	// The initialize() method should load all the source phrases from the InsultsSource.txt file into the attributes.
	// If the file cannot be read, the method should throw an exception.
	try {
		ig.initialize();
	}
	catch (FileException& e) {
		cerr << e.what() << endl;
		return 1;
	}

	// talkToMe() returns a single insult, generated at random.
	cout << "A single insult:" << endl;
	cout << ig.talkToMe() << endl;

	// Check number to generate limits.
	try {
		insults = ig.generate(-100);
	}
	catch (NumInsultsOutOfBounds& e) {
		cerr << e.what() << endl;
	}
	try {
		insults = ig.generate(40000);
	}
	catch (NumInsultsOutOfBounds& e) {
		cerr << e.what() << endl;
	}

	// generate() generates the requested number of unique insults.
	cout << "\n100 insults, all different:" << endl;
	insults = ig.generate(100);
	if (insults.size() > 0)
		for (int i = 0; i < 100; i++)
			cout << insults[i] << endl;
	else
		cerr << "Insults could not be generated!" << endl;

	// generateAndSave() generates the requested number of unique insults and saves them to the filename
	// supplied.  If the file cannot be written, the method should throw an exception.  Note that the
	// insults in the file should be in alphabetical order!
	// Check the number to generate limits first:
	try {
		ig.generateAndSave("Nothing.txt", 40000);
	}
	catch (NumInsultsOutOfBounds& e) {
		cerr << e.what() << endl;
	}
	cout << "\nSaving 1000 unique insults to a file...";
	try {
		ig.generateAndSave("SavedInsults.txt", 1000);
	}
	catch (FileException& e) {
		cerr << e.what() << endl;
		return 1;
	}
	cout << "done." << endl;

	// Test ability to generate the maximum number of insults and how long it takes.
	try {
		start = clock();
		insults = ig.generate(10000);
		finish = clock();
	}
	catch (NumInsultsOutOfBounds& e) {
		cerr << e.what() << endl;
	}
	cout << "\n" << insults.size() << " insults generated." << endl;
	cout << (1e3 * (finish - start) / CLOCKS_PER_SEC) << " msec to complete." << endl;

	return 0;

} // end main*/
//==========================================================================================================================================================================================================================================================

//Start of code
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <algorithm>
using namespace std;
#include "insultgenerator_19oao8.h"
//=========================================================================================================================================================================================================================================================

FileException::FileException(const string& error) : error(error) {}

string FileException::what() const {
	return error;
}
//end of FileException() method

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& error) : error(error) {}

string NumInsultsOutOfBounds::what() const {
	return error;
}
//end of NumInsultsOutOfBounds() method


void InsultGenerator::initialize() {
	//variables
	//Size of file initialized to zero
	int sizeOfFile = 0;
	string rowInFile;


	ifstream getFile("InsultsSource.txt");
	if (getFile.fail()) {
		throw FileException("ERROR: FILE NOT FOUND");
	}

// reading the insults from file and filling it into array
	while (!getFile.eof()) {
		getFile >> rowInFile;
		firstInsult.push_back(rowInFile);

		getFile >> rowInFile;
		secInsult.push_back(rowInFile);

		getFile >> rowInFile;
		thirdInsult.push_back(rowInFile);
	}
	getFile.close();
}
//end of initialize() method

//method to put generated insult into a full sentance
string InsultGenerator::talkToMe() {
	string insultSentance = ("Thou " + firstInsult[rand() % 50] + " " + secInsult[rand() % 50] + " " + thirdInsult[rand() % 50] + "!");
	return insultSentance;
}
//end of talkToMe() method

vector<string> InsultGenerator::generate(const int insultNum) {
	// if the user enters an insult lower or higher than accepted number error is thrown
	if (insultNum < 1 || insultNum > 10000) {
		throw NumInsultsOutOfBounds("ERROR: PLEASE ENTER A VALID INSULT AMOUNT");
	}
	string output;
	set<string> iSet;

	while (iSet.size() < insultNum) {
		output = talkToMe();
		iSet.insert(output);
	}
	vector<string> myVector(iSet.begin(), iSet.end());
	return myVector;
}
//end of generate() method

//Method to save generated insult into file
void InsultGenerator::generateAndSave(const string resultFile, const int insultNumb) {
	ofstream outputtedInsults;
	outputtedInsults.open(resultFile);

//filling insults into file by line
	vector<string> savedInsult = generate(insultNumb);
	if (outputtedInsults.is_open()) {
		for (int i = 0; i < insultNumb; i++) {
			outputtedInsults << savedInsult[i] << endl;
		}
	}
	//throwing error for when the file was not created
	else {
		throw FileException("ERROR: FILE FOR RESULTS WAS NOT CREATED");
	}
}
//end of generateAndSave() method
//end of program