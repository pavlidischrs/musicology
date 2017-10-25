/// <summary>
/// 
/// This class is used to read the rules
/// 
/// Currently the rules are organised as following.
///
///
/// We are on the Level 1 of Counterpoint i.e we put a Musical Symbol in a postion according to the Musical Symbol in the below position.
/// So, we only care about the below symbol.
///
/// We have a "rules" file where we store the rules. In this file you can see a column of numbers separated with empty lines.
/// Note, each number represents a Musical Note and it is the Note's ID. So what we see in the document is IDs.
///
/// The last two numbers of each batch are the Musical Symbols (we see IDs in our case)
/// that are valid to be entered
/// if in the lower pentagram we have a Musical Symbol, which has an ID equal to the first number of the batch.
///
/// So, imagine that the first number is the below symbol and the next numbers are the symbols that could be entered
/// in the upper pentagram (i.e the rules).
/// 
/// </summary>

#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class RulesClass {

public:

	/// <summary>
	/// The constructor calls the  readRules() method to read the rules.
	/// The rules can later be accessed with the getRulesMap() method
	/// </summary>
	/// <param name="path">The path to the rulesFile</param>
	RulesClass(string path);

	~RulesClass();




	/// <summary>
	/// This method prints the rules, which is given as parameter. It could be used for debug purposes
	/// since the printRules() [without arguments] can print the read rules.
	/// </summary>
	/// <param name="globalRules">The given rules</param>
    void printRules(map<int, vector<int>> globalRules);



	/// <summary>
	/// Returns the read rules!
	/// </summary>
	/// <returns></returns>
    map<int, vector<int>> getRulesMap() {
		return globalRules_;
	}

private:

	/// <summary>
	/// The method which reads the rules from the rulesFile
	/// </summary>
	/// <returns>True if Rules was read, False otherwise</returns>
	bool readRules();


	/// <summary>
	/// Prints the rules that have been read from the constructor of the class.
	/// </summary>
	void printRules();



	// In this variable we will store the rules for is musical Symbol
    map<int, vector<int>> globalRules_;

	// Path for the rules file
	string pathToRulesFile_;

};
