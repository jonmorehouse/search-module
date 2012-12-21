#include "../main_header.h"

//********************** CONSTRUCTERS/DESTRUCTORS *********************
using namespace std;
using namespace sql;

Database::Database() {
	
	Configuration configuration;

	try{
		driver = get_driver_instance();
		con = driver->connect(configuration.get_host(), configuration.get_username(), configuration.get_password());
		con->setSchema(configuration.get_database());
	}
	
	catch(SQLException &e){
		database_error(e);//this will be called throughout
	}
}

Database::Database(Configuration configuration) {
	
	try{
		driver = get_driver_instance();
		con = driver->connect(configuration.get_host(), configuration.get_username(), configuration.get_password());
		con->setSchema(configuration.get_database());
	}
	
	catch(SQLException &e){
		database_error(e);//this will be called throughout
	}
}

Database::~Database() {

	
}

//********************** PRIVATE FUNCTIONS *********************
 
string Database::from(string table) {
	
	string statement;
	
	statement = " FROM ";
	statement.append(table);
	
	return statement;
}

string Database::where(vector<where_statement>where, string type) {
	
	int where_counter;
	string statement;

	where_counter = where.size();
	
	if(0 == where_counter)
		return statement;
	
	statement.append(" WHERE ");
		
	for (int i = 0; i < where_counter; i++) {
		
		if(i != 0)
			statement.append(" AND ");
			
		statement.append(where[i].column_name);
		statement.append(" ");
		statement.append(type);
		
		statement.append(" \'");//begining comma of statement
		
		// NEED TO ADD THE WILDCARD FOR LIKE STATEMENTS
		if(helper.equal_strings("LIKE", type))
			statement.append("%");
		
		statement.append(where[i].column_value);
		
		// NEED TO ADD WILDCARD ENDING FOR LIKE STATEMENT
		if(helper.equal_strings("LIKE", type))
			statement.append("%");
		
		statement.append("\'");
		
		// Final where statement should be something like WHERE column = 'value' AND column = 'value'
		// Final like statement should be something like where column like '%value%' 
	}

	return statement;
}

string Database::select(vector<column_description> select) {


	int select_counter;
	string statement;
	
	statement = "SELECT ";

	select_counter = select.size();

	if(select_counter == 0) {//this should not happen--
	
		statement.append("*");//select all values
		return statement;
		
	}

	//the select statement contains only certain fields
		
	for (int i = 0; i < select_counter; i++) {
		statement.append(select[i].name);
		
		if(i < select_counter-1)
			statement.append(", ");
	}

	return statement;
}

string Database::join(vector<join_statement>join, string type) {
	
	// Will modify this later to incorporate multiple joins

	string statement;
	int join_counter;
	
	join_counter = join.size();
	
	statement.append(type);

	statement.append(" JOIN ");
	statement.append(join[0].table);
	statement.append(" ON ");
	
	for(int i = 0; i < join_counter; i++) {
		
		if(i%2 != 0)
			statement.append("=");

		statement.append(join[i].table);
		statement.append(".");
		statement.append(join[i].column);
		
	}
	
	return statement;
}

void Database::table_description(string table, vector<string> select, vector<column_description> &select_statement) {
	/*This function takes a list of strings which correspond to the columns requested. If the string list is empty, then we want to do a select all*/
	
	string statement;
	column_description column;

	statement.append("DESCRIBE ");
	statement.append(table);	
	
	pstmt = con->prepareStatement(statement);
	res = pstmt->executeQuery();
	
	/*We now have the statement, just need to go through each row and grab the information needed */
	
	while(res->next()) {

		column.name = res->getString("Field");//need to store the field
		column.datatype = res->getString("Type");//need to store the type of the column
		
		if(0 == select.size()) {
			select_statement.push_back(column);
		}

		else { //this is not a select* so we need to validate that there is a match
			
			for (int i = 0; i < select.size(); i++) {//search through the input selections and see if the current column_name is there
				
				if(helper.equal_strings(select[i], column.name)) {//if both strings are the same--refer to helper.h method
					
					select_statement.push_back(column);
				}//end if loop
			}//end for loop
		}//end else loop
	}//end while loop
}

void Database::statement_results(string statement, vector<column_description> select_parameter, vector<row_result> &results) {
	
	column_result column;
	row_result individual_row;
	int result_counter;
	
	result_counter = 0;
	// DATABASE STATEMENT
	pstmt = con->prepareStatement(statement);
	res = pstmt->executeQuery();

	while(res->next()) {//this is for each row!
		
		individual_row.row_column.clear();
		
		// CREATE A ROW TO PUSH INTO THE VECTOR
		for (int i = 0; i < select_parameter.size(); i++) {//create a column entry for each row
			

			column.name = select_parameter[i].name;
			column.datatype = select_parameter[i].datatype;
			column.integer_value = res->getInt(select_parameter[i].name);
			column.string_value = res->getString(select_parameter[i].name);
				
			individual_row.row_column.push_back(column);
			result_counter++;
		}
		
		results.push_back(individual_row);
	}
	
	if(result_counter == 0){
		
		column.name = "not found";
		column.datatype = "not found";
		column.integer_value = 0;
		column.string_value = "not found";
		individual_row.row_column.push_back(column);
		results.push_back(individual_row);
	}
	
	delete pstmt;
	delete res;
}

void Database::database_error(std::exception error) {
	
	cout << "There was a bug";
	
	
}

//********************* PUBLIC FUNCTIONS--TO BE EXTENDED LATER *************

void Database::query(string table, vector<string> select_list, vector<where_statement> where_parameter, vector<row_result> &results) {
	
	string statement;
	vector<column_description> select_statement;
	
	table_description(table, select_list, select_statement);
	
	statement.append(select(select_statement));
	statement.append(from(table));
	statement.append(where(where_parameter));

	statement_results(statement, select_statement, results);
	
}

void Database::create_table(string name, vector<Table_statement>fields) {
		//name = string. categories = vector<string>
		
		string table_statement, exists_statement;
		int field_length;

		exists_statement = "drop table if exists ";
		exists_statement.append(name);
		
		// create table statement
		field_length = fields.size();
		
		table_statement.append("Create table ");
		table_statement.append(name);
		table_statement.append(" (");
		
		for (int i = 0; i<field_length; i++) {
			
			// append the field to the statement
			table_statement.append(fields[i].column_name);
			table_statement.append(" ");
			table_statement.append(fields[i].column_type);
			table_statement.append(" Default ");
			table_statement.append(fields[i].column_default);
			
			if(fields[i].primary_key) {
				
				table_statement.append(" Primary Key ");
			}

			// append a comma only if it is not the last item
			if(i!=field_length-1)//check if it is the last item
				table_statement.append(", ");
		}
		
		table_statement.append(")");//close the statement
		// Create table statement is completed
		
		try {
			stmt = con->createStatement();//create the statement to be used
			stmt->execute(exists_statement);
			stmt->execute(table_statement);
		} 
		catch (exception &e) {			
			database_error(e);
		}
		
		delete stmt;
		
}

void Database::query_join(string table_parameter, vector<column_description>select_parameter, vector<join_statement>join_parameter, vector<where_statement>where_parameter) {
	
	string statement;
	
	// statement.append(select(select_parameter));
	// statement.append(from(table_parameter));
	statement.append(join(join_parameter));
	// statement.append(where(where_parameter));
	
	cout << statement << endl << endl;
}

void Database::query_like(string table, vector<string> select_list, vector<where_statement> where_parameter, vector<row_result> &results) {

	string statement;
	vector<column_description> select_statement;
	
	table_description(table, select_list, select_statement);
	
	statement.append(select(select_statement));
	statement.append(from(table));
	statement.append(where(where_parameter, "LIKE"));//only append "LIKE IF SEARCHING"

	statement_results(statement, select_statement, results);
}
