
//		main.cpp file

#include "rulesClass.h"
#include "musicTrainingClass.h"

using namespace std;



int main(int argc, char *argv[]) {


	cout << "\n\n";


	// Instructions
	cout << "Press N for a new exercise \n" <<
		"Press Enter to validate exercise\n" <<
		"Press 0-9 to insert symbol\n" <<
		"Press Esq to exit\n" << endl;

	cout << "\n\n Since it is a demo you can just press the number shown in the pictures and see what is working";

	//// Read the rules
	RulesClass RulesObj("rsc/rules.txt");
	map<int, vector<vector<int>>> rules;
	rules = RulesObj.getRulesMap();


	// The MusicTrainingObj does all the job for now!
	// It starts with reading the rules on its constructor
	MusicTrainingClass MusicTrainingObj(rules);

	// Create an excercise
	MusicTrainingObj.createExercise(5);

	MusicTrainingObj.printVector(MusicTrainingObj.getExercise());
	

	int show = -1;
	while (show!=27) {

		//cout << show << endl;

		// Press N for new exercise
		if (show == 110) {
			MusicTrainingObj.createExercise(5);
		}

		// Press digit to insert symbol
		if (show >= 48 && show <= 58) {
			MusicTrainingObj.fillHidenSymbol(show - 48);
		}


		// Render exercise
		show = MusicTrainingObj.showExercise();


		// Check if answer is correct
		if (show == 13) {
			MusicTrainingObj.makeAssessment();
			//break;
		}

	}


	return 0;
}
