#pragma once

#include <string>
#include <vector>
using namespace std;


// class to generate insult itself
class InsultGenerator {
public:
//calls on method reading text file and initializing the insult generator
    void initialize();
    //calls on method to put insult into a full sentance
    string talkToMe();
    //method to put insult in a vector string
    vector<string> generate(const int insultNum);
    //method to create and save a new file for generated output
    void generateAndSave(const string outputtedInsults, const int insultNum);

private:
// vector string variables for isults
    vector<string> firstInsult;
    vector<string> secInsult;
    vector<string> thirdInsult;
};
//end of InsultGenerator class

//================================================================================================================================================================================
//Built in cpp class for file exception
class FileException {
public:
//calling on itself and will output specific error
    FileException(const string&);
    string what() const;
private:
    string error;
};

// Checks for number of insults and by extension if it is valid or invalid
class NumInsultsOutOfBounds {
public:
    NumInsultsOutOfBounds(const string&);
    string what() const;
private:
    string error;
};
//end of FileException Class
//end of program
