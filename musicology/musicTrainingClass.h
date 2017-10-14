/// <summary>
/// 
/// For now, this class will do all the job! It creates and visualises an exercise!
/// 
/// Since the rules are read, it creates an exercise, which is asked from the user to be solved.
/// It visualises a sequence of musical symbols with gaps in some positions.
/// 
/// The user is asked to fill this gaps so as to solve the exercise.
/// 
/// 
/// </summary>


#pragma once

#include <vector>
#include <ctime>
#include <chrono> 
#include <array>
#include <algorithm> 
#include <random>      

#include <string>


#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class MusicTrainingClass {


public:
	MusicTrainingClass(map<int, vector<vector<int>>> rules);
	~MusicTrainingClass();

	
	/// <summary>
	/// The method takes as input a symbol and displays it on an empty position. For our example, 
	/// places it in the gaps of the Symbol Sequence that the exercise has created.
	/// </summary>
	/// <param name="musicSymbol"></param>
	void fillHidenSymbol(int musicSymbol);

	/// <summary>
	/// This function creates an exercise. First, it creates a valid sequence from the rules
	/// and then chooses some symbols to hide. These Symbols will be asked from the user to be filled.
	/// 
	/// The result of this method is a vector which contains indexes to the positions of the created Symbol Sequence.
	/// These positions is the Symbols that we want to hide from the user.
	/// </summary>
	/// <param name="difficulty">The difficulty of the exercise</param>
	void createExercise(int difficulty);

	
	/// <summary>
	/// This method is called after the user has filled up the exercise.
	/// It checks if the given answer is correct.
	/// <summary>
	bool makeAssessment();


	/// <summary>
	/// Visualises the exercise.
	/// </summary>
	/// <returns></returns>
	int showExercise();


	/// <summary>
	/// Just prints a vector.
	/// </summary>
	/// <param name="v">The vector</param>
	void printVector(vector<int> v);


	// Return the given answer
	vector<int> getGivenAnswer() {
		return givenAnswer_;
	}

	// Returns the exercise
	vector<int> getExercise() {
		return exerciseSequence_;
	}

private:

	/// <summary>
	/// Create the canvas to visualise the exercise.
	/// 
	/// It reads the created sequence from the createExercise() method and visualises the appropriate symbols.
	/// </summary>
	void createCanvas();

	/// <summary>
	/// This method is used from the createCanvas function to read the image of the Symbol
	/// and put it on the canvas
	/// </summary>
	/// <param name="symbolNumber">The number of the SymBol</param>
	void putSymbolToCanvas(int symbolNumber);


	/// <summary>
	/// This functions is used to delete 
	/// </summary>
	void clearWorkspace();

	int position_ = 0;
	int x_ = 0;
	int y_ = 0;
	Mat canvas_;
	map<int, vector<vector<int>>> rules_;

	int numberOfAnsweredSymbol_;
	
	// This variable is used to display the symbols the one next to the other.
	vector < cv::Point > positionOfSymbolForTheCanvas_;

	vector<int> givenAnswer_;

	// This variable contains the random valid Symbol Sequeence of the exercise.
	// This is the Symbol Sequence that we want to hide some of its symbols.
	vector<int> exerciseSequence_;

	// This variable will have the position indexes of the Symbols that we want to hide. Result of createExercise()
	vector<int> posOfHiddenSymbols_;
};