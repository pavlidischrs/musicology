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

		// Read the Note for which you will read its rules
		while (myfile >> keyNote) {

			vector<vector<int>> keyRules;	// Vector for storing all the rules of a Note

			// Read the rules of the Note
			for (int i = 0; i < 3; i++) {

				vector<int> tempVector; // Vector for storing a rule 

				// Read the sequence which can be follow after the keyNote
				for (int j = 0; j < 2; j++) {
					int temp;	// Temp note
					myfile >> temp;
					tempVector.push_back(temp);
				}
				// Insert a single rule
				keyRules.push_back(tempVector);
			}
			// Insert all the rules for the Note-key
			globalRules_.insert(pair<int, vector<vector<int>>>(keyNote, keyRules));
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
		vector<vector<int>> temp = it->second;

		for (auto it1 = temp.begin(); it1 != temp.end(); it1++) {

			for (auto it2 = it1->begin(); it2 != it1->end(); it2++) {
				cout << *it2 << " ";
			}

			cout << endl;
		}

		cout << endl;
	}
}

void RulesClass::printRules(map<int, vector<vector<int>>>) {

	for (auto it = globalRules_.begin(); it != globalRules_.end(); ++it) {

		cout << it->first << endl;
		vector<vector<int>> temp = it->second;

		for (auto it1 = temp.begin(); it1 != temp.end(); it1++) {

			for (auto it2 = it1->begin(); it2 != it1->end(); it2++) {
				cout << *it2 << " ";
			}

			cout << endl;
		}

		cout << endl;
	}
}


