#include "rulesClass.h"

RulesClass::RulesClass() {
	readRules();
	cout << "Rules have been read" << endl;
}

RulesClass::~RulesClass() {

}

void RulesClass::readRules () {

	string line;
	ifstream myfile("rsc/rules.txt");
	int key;

	if (myfile.is_open()) {

		// Read the Note for which you will read the rules
		while (myfile >> key) {

			vector<vector<int>> keyRules;	// Vector for storing all the rules of a Note

											// Read the rules of the Note
			for (int i = 0; i < 3; i++) {

				vector<int> tempVector; // Vector for storing a rule 

										// Read the sequence which can be follow
				for (int j = 0; j < 2; j++) {
					int temp;	// Temp note
					myfile >> temp;
					tempVector.push_back(temp);
				}
				// Insert a single rule
				keyRules.push_back(tempVector);
			}
			// Insert all the rules for the Note-key
			this->globalRules.insert(pair<int, vector<vector<int>>>(key, keyRules));
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file";
	}

	myfile.close();

}



void RulesClass::printRules() {

	//for (int i = 1; i <= 9; i++) {
	for (auto it = this->globalRules.begin(); it != this->globalRules.end(); ++it) {

		cout << it->first << endl;
		vector<vector<int>> temp = it->second;
		//cout << globalRules[i] << " " << endl;

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

	//for (int i = 1; i <= 9; i++) {
	for (auto it = this->globalRules.begin(); it != this->globalRules.end(); ++it) {

		cout << it->first << endl;
		vector<vector<int>> temp = it->second;
		//cout << globalRules[i] << " " << endl;

		for (auto it1 = temp.begin(); it1 != temp.end(); it1++) {

			for (auto it2 = it1->begin(); it2 != it1->end(); it2++) {
				cout << *it2 << " ";
			}

			cout << endl;
		}

		cout << endl;
	}
}


