#pragma once

#include <vector>
#include <ctime>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class MusicalSymbols {

private:

	int position=0;
	int x = 0;
	int y = 0;
	Mat canvas;
	map<int, vector<vector<int>>> rules;

	vector<int> sequence;
		 
public:
	MusicalSymbols(map<int, vector<vector<int>>> rules);
	~MusicalSymbols();

	void showSymbols();

	void createCanvas();

	int showSequence();

	void putSymbol(int symbolNumber);

	void makeAssessment(vector<int> sequence);

	void printVector(vector<int> v);

	void createExercise(int difficulty);

	vector<int> getSequence() {
		return this->sequence;
	}


};