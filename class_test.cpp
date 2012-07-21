#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include "main_header.h"

// Declarations


// Prototypes

void test(string test_string = "and");
void create_table();
void database_query_test();
void prospero_test();

// Global variables

Configuration configuration;
Database database(configuration);
Helper helper;

// Program beginning
int main(){
	cout << endl;
	
	prospero_test();
	
	cout << endl;
}

void create_table_test() {
	
	vector<Table_statement> columns;
	Table_statement column;
	
	column.column_name = "test_column";
	column.column_type = "int(11)";
	column.column_default = "10";
	
	columns.push_back(column);
	
	database.create_table("database_class_table", columns);
	
}

void database_query_test() {
	
	string table;
	table = "database_class_table";
	vector<string> select;
	vector<row_result> results;
	vector<where_statement> where;
	where_statement current_where;
	
	current_where.column_name = "test_column";
	current_where.column_value = "22";
	where.push_back(current_where);

	database.query_like(table, select, where, results);
}

void prospero_test() {
	
	Search search;
	Prospero prospero;
	Property_get property_get;
	Property_elements property_element;
	
	vector<int>list;
	search.property_id_search("default", list);
	
	property_element.thumbnail(3);
	
	
}
