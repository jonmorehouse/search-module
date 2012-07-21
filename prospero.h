#ifndef PROSPERO_H
#define PROSPERO_H

#include "main_header.h"
// THIS CLASS IS NOT UNIVERSAL--PRIMARILY BUILT TO BE USED BY PROSPERO.CA
// THIS CLASS IS BUILT TO QUERY A DATABASE AND RETURN THE PROPER RESULTS FOR EACH SEARCH

struct category {
	
	string category;
	string table;
	string datatype;
	
};

struct integer_key_value { //useful for sorting integers--note search.sort/search.duplicate
	
	int key;
	int value;
	
};


class Prospero{
	
	public:
		Prospero();
		~Prospero();
		string category_table(string category);
		string category_datatype(string category);
		
	protected:
		// OBJECTS
		Configuration configuration;
		Database database;
		Helper helper;

		// STRUCTURES
		vector<category> category_list;
		
		// FUNCTIONS
		
	private:
		void category_table_list();
		string category_list_search(string category, string type = "table");
		
			
	
};

class Search: public Prospero {
	// ******* PUBLIC * *********
	public:
		Search();
		~Search();
		void property_id_search(string input, vector<int> &results);

	/********* PRIVATE ***********/
	private:
		void duplicates(vector <int> &unsorted_list, vector <integer_key_value> &key_value_results);
		void sort(vector <integer_key_value> key_value_results, vector <int> &sorted_results);
		
	
	
};

class Property_get: protected Prospero {
	
	public:
		Property_get();
		~Property_get();
		string get_string_value(int property_id, string category);
		int get_integer_value(int property_id, string category);

	private:
		void database_query(int property_id, string category, vector<row_result> &results);
		
};

class Property_elements: public Property_get {
	
	public:
		Property_elements();
		~Property_elements();
		void thumbnail(int property_id, string output = "cout");

	private:
		string listing_url(int property_id);
		string listing_thumbnail_image(int property_id);
		string headers();
		
};
	
		
	

#endif