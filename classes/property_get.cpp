#include "../main_header.h"

Property_get::Property_get() {
	
	
	
	
	
}

Property_get::~Property_get() {
	
	
	
}

string Property_get::get_string_value(int property_id, string category) {
	
	vector<row_result> results;
	
	database_query(property_id, category, results);//query the database for this property
	
	return results[0].row_column[0].string_value;
}

int Property_get::get_integer_value(int property_id, string category) {
	
	vector<row_result> results;
	
	database_query(property_id, category, results);//query the database for this property_id
	
	return results[0].row_column[0].integer_value;
}

void Property_get::database_query(int property_id, string category, vector<row_result> &results) {

	string table;
	vector<string> select (1);
	vector<where_statement> where (1);
	
	
	table = category_table(category);
	select[0] = helper.string_to_lower(category);
	where[0].column_name = "property_id";
	where[0].column_value = helper.integer_to_string(property_id);
	
	database.query(table, select, where, results);
	
}

