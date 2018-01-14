#include "rulesClass.h"

RulesClass::RulesClass() {

}

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



int RulesClass::checkAnswer( std::vector<int> *givenAnswer, std::vector<int> *givenExercise, rulesSource source )
{

    int sizeOfAnswer = givenAnswer->size();

    if(sizeOfAnswer==0){
        return 0;
    }

    int i=0;

    if (source == READ_FROM_FILE) {
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
    }
    else if(source == USE_ALGORITHM){


        int pos = 0;
        int correctNotes=0;
        for( auto e : *givenAnswer){

            if ( pos == 0 ) {

                // The sequence has to start with the note 2 or 4.
                sequenceState_ = FIRST_POS;
                if( e!=2 && e!=4 ){
                    qDebug() << "You should start with 2 or 4";
                }
                else{
                    correctNotes++;
                }
            }
            else {

                if(sequenceState_ == JUMP_OF){  // If in the previous position we had a jump of any number (read bellow to understand what a jump is), it should follow a step in the difference direction.
                                                // For instace, 3->1->2 or 9->12->11 are valid. 3->1->0 or 3->1->3 not valid.
                    sequenceState_ = SINGLE_STEP;

                    int prevDiff = givenAnswer->at(pos-2) - givenAnswer->at(pos-1);
                    int currDiff = givenAnswer->at(pos-1) - e;

                    if( abs(currDiff)==1 && prevDiff*currDiff < 0){
                        correctNotes++;
                    }
                }
                else {

                    // Compute the difference of the preivous and current note.
                    int diff = abs ( givenAnswer->at(pos-1) - e );

                    if(diff == 1){

                        // If two consecutive notes have difference 1, we call it step. Steps are always allowed, therefore we go to check the next note.
                        sequenceState_ = SINGLE_STEP;
                        correctNotes++;

                    }
                    else if(diff == 2){

                        // If two consecutive notes have difference 2, we call it jump of 2. Jumps of 2 are always allowed.
                        sequenceState_ = JUMP_OF;
                        correctNotes++;

                    }
                    else if(diff == 3){

                        // Jumps of 3 are allowed except if the current note is 7 and the previous is 4 or the reverse.
                        sequenceState_ = JUMP_OF;
                        if( (givenAnswer->at(pos-1)==4 && e ==7) || (givenAnswer->at(pos-1)==7 && e ==4) ){
                            qDebug() << "You have a jump of 3 either from notes 4 to 7 or from 7 to 4. This is a rule missmatch!";
                        }
                        else{
                            correctNotes++;
                        }
                    }
                    else if(diff == 4){

                        // Jumps of 4 are allowed except if the current note is 7 and the previous is 11 or the reverse.
                        sequenceState_ = JUMP_OF;
                        if( (givenAnswer->at(pos-1)==7 && e ==11) || (givenAnswer->at(pos-1)==11 && e ==7) ){
                            qDebug() << "You have a jump of 4 either from notes 7 to 11 or from 11 to 7. This is a rule missmatch!";
                        }
                        else{
                            correctNotes++;
                        }
                    }
                    else if(diff == 5){ // Jump of 5.

                        // Jumps of 5 are allowed ONLY from notes 3 to 8, 6->11 and 7->12.
                        sequenceState_ = JUMP_OF;
                        if( givenAnswer->at(pos-1)==3 && e ==8  || givenAnswer->at(pos-1)==6 && e ==11 || givenAnswer->at(pos-1)==7 && e ==12 ){
                            correctNotes++;
                        }
                        else{
                            qDebug() << "You have an invalid jump of 5. From note: "<< givenAnswer->at(pos-1) <<" to note: " << e;
                        }
                    }
                    else if(diff == 7){ // Jump of 7.

                        // Jumps of 7 are always allowed.
                        sequenceState_ = JUMP_OF;
                        correctNotes++;
                    }
                }

            }

            pos++;
        }

        i=correctNotes;
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
