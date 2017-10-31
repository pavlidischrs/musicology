#include "rulesClass.h"

RulesClass::RulesClass(string path) {
	

	pathToRulesFile_ = path; 

	bool read = this->readRules();

	if (read) {
		cout << "Rules have been read" << endl;
	}
	else {
		cout << "Rules have not been read!!" << endl;
	}

}

RulesClass::~RulesClass() {

}

bool RulesClass::readRules () {

	string line;
	ifstream myfile( pathToRulesFile_ );
	int keyNote;


	if (myfile.is_open()) {

        // Read the Musical Note for which you will read its rules
		while (myfile >> keyNote) {

            vector<int> keyRules;	// Vector for storing all the rules of a Note

            // Read the rules of the Note. (We have two in our current implementation)
            for (int i = 0; i < 2; i++) {
                int temp;	// Temp note
                myfile >> temp;
                keyRules.push_back(temp);
			}
			// Insert all the rules for the Note-key
            globalRules_.insert(pair<int, vector<int>>(keyNote, keyRules));
		}
		myfile.close();

		return true;
	}
	else {

		cout << "Error occured with opening file" << endl;
		return false;
	}

}



void RulesClass::printRules() {

	for (auto it = globalRules_.begin(); it != globalRules_.end(); ++it) {

		cout << it->first << endl;
        vector<int> temp = it->second;

		for (auto it1 = temp.begin(); it1 != temp.end(); it1++) {

            cout << *it1 << " ";

            cout << endl;
		}

		cout << endl;
	}
}

void RulesClass::printRules(map<int, vector<int>>) {

	for (auto it = globalRules_.begin(); it != globalRules_.end(); ++it) {

		cout << it->first << endl;
        vector<int> temp = it->second;

		for (auto it1 = temp.begin(); it1 != temp.end(); it1++) {

            cout << *it1 << " ";

			cout << endl;
		}

		cout << endl;
	}
}



int RulesClass::checkAnswer( std::vector<int> *givenAnswer, std::vector<int> *givenExercise  )
{

    int sizeOfAnswer = givenAnswer->size();

    if(sizeOfAnswer==0){
        return 0;
    }

    int i=0;
    for(i=0; i<sizeOfAnswer; i++){

        //pick up the rules of the symbol in the lower pentagram
        std::vector<int> symbolRules = globalRules_[givenExercise->at(i)];

        int numberOfRules = symbolRules.size();
        int numberOfMismatches = 0;
        //check if the given symbol in the upper pentagram obeys the rules
        for(int j=0; j<numberOfRules; j++){
            if( givenAnswer->at(i) == symbolRules.at(j) ){
                break;
            }
            else{
                numberOfMismatches++;
            }
        }

        // If the mismatches is equal to the number of rules,
        // means that your choice does not obey to any of the rules
        // so your answer is wrong
        if(numberOfMismatches == numberOfRules){
            break;
        }

    }

    // If you have examined all the symbols and are correct
    // then the i index will be equal to the size of the
    // sequence (sizeOfAnswer)
    if(i==sizeOfAnswer){
        return 1;
    }
    else{
        return -1;
    }
}
