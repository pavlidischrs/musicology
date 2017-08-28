#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class RulesClass {



	private:

		map<int, vector<vector<int>>> globalRules;


	public:

		RulesClass();

		~RulesClass();

		// Read rules
		void readRules();	
		// Print rules to console
		void printRules();

		void printRules(map<int, vector<vector<int>>> globalRules);

		map<int, vector<vector<int>>> getRulesMap() {
			return globalRules;
		}

};