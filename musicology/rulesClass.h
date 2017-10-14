/// <summary>
/// 
/// In this file we read the rules of the valid Musical Note Sequences
/// 
/// The Rules are stored in a Map where its key of the Map (a number which corresponds to Musical Note)
/// matches to a vector. This vector contains all the rules of the Musical Note. 
/// Each rule is another vector as well, where each position has a number (which corresponds to a note).
/// 
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
	void printRules(map<int, vector<vector<int>>> globalRules);



	/// <summary>
	/// Returns the read rules!
	/// </summary>
	/// <returns></returns>
	map<int, vector<vector<int>>> getRulesMap() {
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
	map<int, vector<vector<int>>> globalRules_;

	// Path for the rules file
	string pathToRulesFile_;

};