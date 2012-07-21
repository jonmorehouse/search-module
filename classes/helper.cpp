#include "../helper.h"

string Helper::string_to_lower(string input) {
	
	std::transform(input.begin(), input.end(),input.begin(), ::tolower);

	return input;

}

string Helper::string_to_upper(string input) {
	
	std::transform(input.begin(), input.end(), input.begin(), ::toupper);

	return input;
	
}

string Helper::clean_time() {
	
	time_t base_time;
	
	base_time = time (NULL);
	cout << base_time;
	
	return "clean time";
}

string Helper::database_time() {
	
	return "database time";
}

bool Helper::equal_strings(string input_1, string input_2) {
	
	input_1 = string_to_lower(input_1);
	input_2 = string_to_lower(input_2);

	if(input_1.compare(input_2) == 0)
		return true;//they are the same!
	
	else
		return false;
		
}

string Helper::integer_to_string(int input) {
	
	ostringstream convert; // stream used to convert 

	convert << input;//send the input into the stream
	
	return convert.str();//return the stream as a string
	
}

string Helper::char_to_string(char * input) {
	
	ostringstream convert;

	convert << input;
	
	return convert.str();
	
}

void Helper::get_parameters(string input, vector<string> & parameters) {
	
	string parameter;

	for (int i = 0; i < input.size(); i++) {
	
		if(input[i] == '?' || input[i] == '&') {
			if(parameter.size() > 0)
				parameters.push_back(parameter);
			parameter.clear();
		}
		
		else if (i == input.size()-1) {
			parameter.push_back(input[i]);
			parameters.push_back(parameter);
		}
	
		else
			parameter.push_back(input[i]);
			// parameter.append(input[i]);//append is to append a string
	}//end for loop
}

string Helper::get_parameter(string name, vector<string>parameters) {
	
	// this will find the string in question and look for the next one to give
	bool flag;
	int i;
	string result;

	flag = false;
	i = 0;
	
	do {
		
		if(equal_strings(name, parameters[i]) && i+1 < parameters.size()) {//if equal parameter and the next string exists
			
			result = parameters[i+1];
			flag = true;
		}
		
		i++;
		
	} while (!flag);
	
	return result;
}




