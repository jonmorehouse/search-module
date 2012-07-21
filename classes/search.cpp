#include "../main_header.h"
/*this class extends prospero and is to be supplied with a search parameter
	
	this search parameter will be used to grab property ids that are most like the input data
	
*/


Search::Search() {
	
	
}

Search::~Search() {
	
	
	
}

void Search::property_id_search(string input, vector<int> &results) {
	
	/** Note the results is a list of the integers--in the correct order and compressed **/

	// DATABASE QUERY VECTORS
	vector<string> * categories, select_list;
	vector<where_statement> where (1);
	vector<row_result> query_results;
	
	// RESULTS ANALYSIS
	vector<int>raw_list;
	vector<integer_key_value> key_value_results;
	categories = &configuration.search_categories;

	// Vanilla variables -- helpers
	string * category, table;
	int * property_id;
	
	input = helper.string_to_lower(input);
	select_list.push_back("property_id");//we only want to grab the id for each property
	where[0].column_value = input;
	
	
	for (int i = 0; i< (* categories).size(); i++) {//get a list of the tables to query

		category = &(* categories)[i];//this is the current category

		where[0].column_name = * category;
		
		table = category_table(* category);//table to be queried
		
		database.query_like(table, select_list, where, query_results);//actually grab the ids--the results will constantly be added to!
		
	}

	for (int i = 0; i < query_results.size(); i++) {
		
		property_id = & query_results[i].row_column[0].integer_value;

		if(* property_id > 0)
			raw_list.push_back(* property_id);//push the integer into the vector of raw integers!
	} 

	duplicates(raw_list, key_value_results);
	
	sort(key_value_results, results);
	
	key_value_results.clear();
}

void Search::duplicates(vector <int> &unsorted_list, vector <integer_key_value> &key_value_results) {
	
	bool flag;

	// pointers
	int * property_id, counter;
	integer_key_value * key_value, new_key_value;
	
	for (int i = 0; i < unsorted_list.size(); i++) {
		
		property_id = &unsorted_list[i];
		flag = false;
		counter = 0;

		while(!flag) {
			
			key_value = &key_value_results[counter];//the current element

			if(counter == key_value_results.size() || key_value_results.size() == 0) { // value not found in the current results list--need to add it!
				new_key_value.value = 1;
				new_key_value.key = *property_id;
				key_value_results.push_back(new_key_value);
				flag = true;
			}//end if loop for new_key_value

			else if(*property_id == (*key_value).key){//the key has already been found!
					(*key_value).value++;
					flag = true;
			}
			
			counter++;
			
		}//end while loop
		
	}//end for loop
	
	// end duplicate removal
	unsorted_list.clear();
}

void Search::sort(vector <integer_key_value> key_value_results, vector <int> &sorted_results) {
/*This function takes a list of unsorted integers with duplicates and will return a sorted list showing which one's are most likely*/	
//first re-order the key_value_results
// then go through the sorted one and create a basic integer

	integer_key_value current, next;
	bool flag;
	int * current_property_id;
	
	flag = false;
	
	while(!flag) {
		
		for (int i = 0; i < key_value_results.size()-1; i++) {
			
			flag = true;
			current = key_value_results[i];//copy i value into the current one
			next = key_value_results[i++];//copy the next one into a new memory

			if(current.value < next.value) {//switch them in the vector and then flag false!

				key_value_results[i] = next;
				key_value_results[i++] = current;
				flag = false;
				
			}//end if loop
			
		}//end for loop
		
	}//end while loop
	
	for (int i = 0; i < key_value_results.size(); i++) {//copy the property_ids from teh sorted list, key_value_results into the sorted_results

		current_property_id = &key_value_results[i].key;

		sorted_results.push_back(*current_property_id);
		
	}//end for loop
}


