#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include "main_header.h"


// Declarations

Helper helper;

// Prototypes

void generate_thumbnails(string input);
string query_string_input();



// Program beginning
int main(){
	string search_input;
	cout << "Content-type: text/html" << endl << endl;
	
	search_input = query_string_input();
	
	generate_thumbnails(search_input);
	
	return 0;
}

string query_string_input() {
	
	char * query_string;
	string input;
	vector<string> parameters;
	
	query_string = getenv ("QUERY_STRING");

	input = helper.char_to_string(query_string);

	helper.get_parameters(input, parameters);
	
	return helper.get_parameter("search", parameters);
}



void generate_thumbnails(string input) {
	
	Prospero prospero;
	Property_get property_get;
	Search search;
	Property_elements property_element;
	
	vector<int>list;
	search.property_id_search(input, list);
	
	
	
	for (int i = 0; i < list.size(); i++) {

		property_element.thumbnail(list[i]);
	}
	
	if(list.size() < 1) {
		
		cout << "<h3>No search results found.</h3>" << endl;
		cout << "<h3>Please try searching with different criteria or browse via category" << endl;
	}
}
