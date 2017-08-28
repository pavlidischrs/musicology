#include "musicalSymbols.h"

MusicalSymbols::MusicalSymbols(map<int, vector<vector<int>>> rules) {

	this->rules = rules;

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
}

MusicalSymbols::~MusicalSymbols() {
}

/// <summary>
/// Create the canvas for the visualisation
/// </summary>
void MusicalSymbols::createCanvas() {
	this->canvas = Mat(1000, 1000, CV_8UC3, Scalar(0, 0, 0));
}

/// <summary>
/// Place a symbol in the canvas to be displayed
/// </summary>
/// <param name="symbolNumber">The corresponding number of the symbol</param>
void MusicalSymbols::putSymbol(int symbolNumber) {

	Mat symbol;

	this->sequence.push_back(symbolNumber);

	symbol = imread("rsc/" + to_string(symbolNumber) + ".png", CV_LOAD_IMAGE_COLOR);   // Read the file
	resize(symbol, symbol, Size(100,100));//resize image

	symbol.copyTo(this->canvas(cv::Rect(this->x, this->y, symbol.cols, symbol.rows)));
	
	this->x += 100;
	if (this->x % 1000 == 0) {
		this->x = 0;
		this->y += 100;
	}
}

/// <summary>
/// Show the sequence in the Canvas
/// </summary>
/// <returns></returns>
int MusicalSymbols::showSequence() {

	imshow("Display window", this->canvas);

	return  (int)waitKey(30);

}

/// <summary>
/// nothing
/// </summary>
void MusicalSymbols::showSymbols() {

	string suffix = "rsc/";
	string prefix = ".png";

	for (int i = 0; i < 9; i++) {

		string s = to_string(i);

		Mat image;
		image = imread(suffix + s + prefix, CV_LOAD_IMAGE_COLOR);   // Read the file

		imshow("Display window", image);

		waitKey();

	}

}


/// <summary>
/// Check the validity of the sequence
/// </summary>
/// <param name="sequence">The sequence to check</param>
/// <param name="rules">Musicology rules</param>
void MusicalSymbols::makeAssessment(vector<int> sequence) {

	cout << "I am going to check validity" << endl;

	//for (auto it = sequence.begin(); it != sequence.end(); it++) {
	auto it = sequence.begin();
	while (it != sequence.end() - 1) {

		// take all the rules for this Note
		vector<vector<int>> curRules = rules[*it];
		int rulesCnt = 0;
		for (auto it1 = curRules.begin(); it1 != curRules.end(); it1++) {

			// check sepparately each rule for current Note
			vector<int> tempRule = *it1;
			int ruleCnt = 1;

			// Check if the on going rule is bigget or equal than the left sequence
			int dist = distance(it, sequence.end());
			if (dist <=  tempRule.size()) {
				rulesCnt++;
				continue;
			}

			for (auto it2 = tempRule.begin(); it2 != tempRule.end(); it2++) {

				if (*(it + ruleCnt) != *(it2)) {

					cout << "\n\tThis rules does not match\n";
					break;
				}

				ruleCnt++;

			}

			// if you have found a rule which is acceptable, jump your sequence ruleSize positions
			if (ruleCnt == tempRule.size() + 1) {
				it = it + tempRule.size();
				break;
			}
			rulesCnt++;
		}

		// This is the case where all rules have been checked and noone has been matched,
		// If it had matched, the rulesCnt would have been at most (rulesCnt-1) [because of the continue statement]
		if (rulesCnt == curRules.size()) {
			cout << "\n\tThe sequence is not correct\n";
			cout << "The sequence is: ";
			printVector(sequence);
			break;
		}
	}

	if (it == sequence.end() - 1) {
		cout << "\n\tYou are Beethoven's descendant\n\n";
	}
}

/// <summary>
/// Just print a vector
/// </summary>
/// <param name="v">The vector</param>
void MusicalSymbols::printVector(vector<int> v) {

	for (auto it = v.begin(); it != v.end(); it++) {

		cout << *it << " ";

	}
	cout << endl;
}




void MusicalSymbols::createExercise(int difficulty)
{
	vector<int> exercise;

	srand(time(0));	//TODO:Make random random

	int symbol = rand() % 10;
	exercise.push_back(symbol);

	for (int i = 0; i < 5; i++) {

		vector<vector<int>> curRules = rules[symbol]; // retrieve the rules of the First Symbol
		
		int chosenRule = rand() % curRules.size(); // choose a rule

		for (auto it = curRules[chosenRule].begin(); it != curRules[chosenRule].end(); it++) {
			exercise.push_back(*it);
		}

		symbol = exercise.back();

	}


	printVector(exercise);

}
