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

#ifndef RULESCLASS_H
#define RULESCLASS_H

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include <QDebug>


enum state {FIRST_POS ,JUMP_OF, SINGLE_STEP};
enum rulesSource {READ_FROM_FILE, USE_ALGORITHM};

using namespace std;

class RulesClass {

public:


    /// <summary>
    /// Constructor
    /// </summary>
    RulesClass();

	/// <summary>
	/// The constructor calls the  readRules() method to read the rules.
	/// The rules can later be accessed with the getRulesMap() method
	/// </summary>
	/// <param name="path">The path to the rulesFile</param>
	RulesClass(string path);

	~RulesClass();


    ///
    /// \brief checkAnswer: In this method method we examine the given answer according to the Rules
    ///
    ///                     If it is correct returns True, otherwise False
    ///
    ///


    ///
    /// \brief checkAnswer      In this method method we examine the given answer according to the Rules from the file
    /// \param givenAnswer      The answer which will be examined
    /// \param givenExercise    The exercise that was given
    /// \param rS               In this parameter we choose whether the rules will be read from a file (default) or we will
    ///                         use an aglorithmic solution. This misunderstood happens here because we are not sure whether
    ///                         it is better to write the rules in a file or to create an algorithm.
    /// \return                 -1 if false, 0 if the user didn't answered, 1 if it's correct
    int checkAnswer(std::vector<int> *givenAnswer, std::vector<int> *givenExercise, rulesSource source = READ_FROM_FILE );


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

    //
    state sequenceState_;
};

#endif
