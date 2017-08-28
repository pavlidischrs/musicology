
// main.cpp file, it is

#include "rulesClass.h"
#include "musicalSymbols.h"

using namespace std;



int main(int argc, char *argv[]) {

	//// For the rules
	RulesClass rulesObj;
	map<int, vector<vector<int>>> rules;
	rules = rulesObj.getRulesMap();
	//rulesObj.printRules();

	MusicalSymbols picObj(rules);
	vector<int> sequence;


	picObj.createExercise(5);

	picObj.createCanvas();
	int show = -1;
	while (show!=27) {

		if (show > 0) {
			//sequence.push_back(show - 48);
			picObj.putSymbol(show - 48);
		}

		show = picObj.showSequence();

		if (show == 13) {
			sequence = picObj.getSequence();
			picObj.makeAssessment(sequence);
			break;
		}
	}


	return 0;
}
