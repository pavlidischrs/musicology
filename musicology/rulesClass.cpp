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


