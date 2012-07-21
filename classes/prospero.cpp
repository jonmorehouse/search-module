#include "../main_header.h"
/*

Prospero is the main parent for saerch, property_get classes for the prospero 
Dependencies are main_header.h files--helper class, configuration class, database class

*/


/********* CONSTRUCTORS / DESTRUCTORS **************/


Prospero::Prospero() {
	
	category_table_list();
	
}

Prospero::~Prospero() {
	
	
	
}

/************ PUBLIC FUNCTIONS ********************/

string Prospero::category_table(string category) {
	
	return category_list_search(category);

}

string Prospero::category_datatype(string category) {

	return category_list_search(category, "datatype");
}


/************** PRIVATE FUNCTIONS *****************/

void Prospero::category_table_list() {
	
	// 	this function will take in a category and will return the table that it is located in by searching through the category list table
	vector<string>selection;
	vector<where_statement>where;
	vector<row_result> results;
	category current_category;
	
	database.query("table_schema", selection, where, results);
	
	for(int i=0; i<results.size(); i++) {//for each member of the results, save the category to teh category list--which is universal to the class
		
		current_category.category = results[i].row_column[0].string_value;//category_name
		current_category.table = results[i].row_column[1].string_value;//category_location
		current_category.datatype = results[i].row_column[2].string_value;//category_datatype
		
		category_list.push_back(current_category);
	}
}

string Prospero::category_list_search(string category, string type) {
	
	int i;
	bool flag;
	string statement;
	
	i = 0;
	flag = false;
	
	do {

		if(helper.equal_strings(category, category_list[i].category)) {

			if(helper.equal_strings(type, "datatype"))
				statement = category_list[i].datatype;
			else
				statement = category_list[i].table;
			
			flag = true;
		}//end of if loop--search section
		
		i++;
		
		if(i == category_list.size()) {
			// throw("Category not found");
			flag = true;
		}//while loop constraint
		
	} while (!flag);
	
	return statement;
}




