#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>//used for the to_lower/to_upper
#include <time.h>//used for time!
#include <vector>


using namespace std;

class Helper{
	
	public:
		string string_to_lower(string input);
		string string_to_upper(string input);
		string clean_time(void);
		string database_time(void);
		bool equal_strings(string input_1, string input_2);
		string integer_to_string(int input);
		string char_to_string(char * input);
		void get_parameters(string input, vector<string> & parameters);
		string get_parameter(string name, vector<string> parameters);
};

#endif