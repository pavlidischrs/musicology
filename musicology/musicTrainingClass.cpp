// musicalSymbols.cpp file

#include "musicTrainingClass.h"

MusicTrainingClass::MusicTrainingClass(map<int, vector<vector<int>>> rules) {

	// Store the rules
	rules_ = rules;

	// Set the window
	namedWindow("Display window", WINDOW_AUTOSIZE);// Create the display window.
}

MusicTrainingClass::~MusicTrainingClass() {
}


void MusicTrainingClass::fillHidenSymbol(int musicSymbol) {

	// Store my answer
	int nextHiddenPosition = posOfHiddenSymbols_.at(numberOfAnsweredSymbol_);

	// Read the image of the Symbol
	Mat symbol = imread("rsc/" + to_string(musicSymbol) + ".png", CV_LOAD_IMAGE_COLOR);   // Read the file
	resize(symbol, symbol, Size(100, 100));//resize image

	// Add it to canvas
	Point positionOnCanvas = positionOfSymbolForTheCanvas_.at(nextHiddenPosition);
	symbol.copyTo(canvas_(cv::Rect(positionOnCanvas.x, positionOnCanvas.y, symbol.cols, symbol.rows)));

	// Note, that we only have to fill the hiden symbols. The rest symbols are already filled.
	givenAnswer_.at(nextHiddenPosition) = musicSymbol;

	numberOfAnsweredSymbol_++;

}




void MusicTrainingClass::createCanvas() {
	canvas_ = Mat(1000, 1000, CV_8UC3, Scalar(0, 0, 0));


	// Place to canvas all the symbols that were created from the createExercise()
	for (int i = 0; i < exerciseSequence_.size(); i++) {

		// If it is about to displa a Symbol that the exercise wants to hide, place a blank image.
		if( std::find(posOfHiddenSymbols_.begin(), posOfHiddenSymbols_.end(), i) != posOfHiddenSymbols_.end() ) {		

			// 100 means a blank image. I.e. a gap in the visualised  Symbol Sequence
			this->putSymbolToCanvas(100+exerciseSequence_[i]);
		}
		else {
			this->putSymbolToCanvas(exerciseSequence_.at(i));
		}
	}


}


void MusicTrainingClass::putSymbolToCanvas(int symbolNumber) {

	Mat symbolImage;


	givenAnswer_.push_back(symbolNumber);


	// Some cheat for the demo. Draw the number of the digit that the user has to press!
	if (symbolNumber > 100) {

		// Read the image of the Symbol
		symbolImage = imread("rsc/100.png", CV_LOAD_IMAGE_COLOR);   // Read the file
		resize(symbolImage, symbolImage, Size(100, 100));//resize image

		putText(symbolImage, to_string(symbolNumber - 100), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0), 1);

	}
	else {
		// Read the image of the Symbol
		symbolImage = imread("rsc/" + to_string(symbolNumber) + ".png", CV_LOAD_IMAGE_COLOR);   // Read the file
		resize(symbolImage, symbolImage, Size(100, 100));//resize image
	}

	// Add it to canvas
	symbolImage.copyTo(canvas_(cv::Rect(x_, y_, symbolImage.cols, symbolImage.rows)));
	


	Point temp(x_, y_);
	positionOfSymbolForTheCanvas_.push_back(temp);


	// and in the right position
	x_ += 100;
	if (x_ % 1000 == 0) {
		x_ = 0;
		y_ += 100;
	}
}


int MusicTrainingClass::showExercise() {
	imshow("Display window", canvas_);
	return  (int)waitKey(30);
}


bool MusicTrainingClass::makeAssessment() {

	cout << "Checking if the given answer is correct." << endl;

	//for (auto it = sequence.begin(); it != sequence.end(); it++) {
	auto it = givenAnswer_.begin();
	while (it != givenAnswer_.end() - 1) {

		// Take all the rules for this Note
		vector<vector<int>> curRules = rules_[*it];
		int rulesCnt = 0;
		for (auto it1 = curRules.begin(); it1 != curRules.end(); it1++) {

			// Check sepparately each rule for current Note
			vector<int> tempRule = *it1;
			int ruleCnt = 1;

			// Check if the on going rule is bigget or equal than the left sequence
			int dist = distance(it, givenAnswer_.end());
			if (dist <=  tempRule.size()) {
				rulesCnt++;
				continue;
			}

			for (auto it2 = tempRule.begin(); it2 != tempRule.end(); it2++) {

				if (*(it + ruleCnt) != *(it2)) {
					break;
				}

				ruleCnt++;

			}

			// If you have found a rule which is acceptable, jump your sequence ruleSize positions
			if (ruleCnt == tempRule.size() + 1) {
				it = it + tempRule.size();
				break;
			}
			rulesCnt++;
		}

		// This is the case where all rules have been checked and no one has been matched,
		// If it had matched, the rulesCnt would have been at most (rulesCnt-1) [because of the continue statement]
		if (rulesCnt == curRules.size()) {
			cout << "\nI am sorry! Your answer is not correct\n";
			//printVector(givenAnswer_);

			return false;

			break;
		}
	}

	if (it == givenAnswer_.end() - 1) {
		cout << "\nWell done! You are Beethoven's descendant\n\n";

		return 1;
	}
}


void MusicTrainingClass::printVector(vector<int> v) {

	for (auto it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}



void MusicTrainingClass::createExercise(int difficulty)
{

	// clear the appropriate values to set a new exercise
	this->clearWorkspace();

	numberOfAnsweredSymbol_ = 0;

	srand(time(0));	

	int symbol = rand() % 10;
	exerciseSequence_.push_back(symbol);


	// Create a valid sequence from the rules
	for (int i = 0; i < 4; i++) {

		vector<vector<int>> curRules = rules_[symbol]; // retrieve the rules of the First Symbol
		

		int chosenRule = rand() % curRules.size(); // choose a rule randomly

		for (auto it = curRules[chosenRule].begin(); it != curRules[chosenRule].end(); it++) {
			exerciseSequence_.push_back(*it);	// push the symbols of the rule to the exercise
		}

		symbol = exerciseSequence_.back();

	}


	// Now, we have a Symbol Sequence. What we need to do is to hide some symbols and the exercise is ready
	// Since the Symbols Sequence is a vector with Symbols on its position, we will choose randomly some position
	// and we will hide the Symbols of this position

	// Create a vector with all the positions. E.g. [0 1 2 3 4 5 6 7 8]
	for (int i = 0; i < exerciseSequence_.size(); i++) {
		posOfHiddenSymbols_.push_back(i);
	}
	
	// shuffle the positions. E.g. [6 7 3 2 1 5 9 4 0]
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(posOfHiddenSymbols_.begin(), posOfHiddenSymbols_.end(), default_random_engine(seed));

	
	// Keep the first X(=difficulty) position of the shuffled vector. These are the positions of the exerciseSequence_ that we will hide
	posOfHiddenSymbols_.resize(difficulty);


	// We sort them for later usage
	sort(posOfHiddenSymbols_.begin(), posOfHiddenSymbols_.end());


	// Create the image to visualise
	this->createCanvas();
}


void MusicTrainingClass::clearWorkspace() {

	givenAnswer_.clear();

	exerciseSequence_.clear();
	posOfHiddenSymbols_.clear();

	positionOfSymbolForTheCanvas_.clear();

	canvas_.release();


	x_ = 0;
	y_ = 0;

}
