// HEADER GUARD

#ifndef STRUCTURES_H
#define STRUCTURES_H

struct where_statement {
	// to be used in the where statement. Send a vector of each one to the database query
	string column_name;
	string column_value;//remember that sql only takes in strings

};

struct join_statement {
	
	//to be used in joining-right now assuming that only a single full join exists
	string table;
	string column;
};

struct column_result {/*individual result*/
	
	string datatype;
	string name;
	string string_value;//this will be deleted in the results class depending upon the datatype specified
	int integer_value;//this will be deleted in the results function depending upon the datatype specified

};

struct row_result {
	
	vector<column_result> row_column;
	
};

struct column_description {
	
	string name;
	string datatype;
	
};


#endif