#ifndef CLASSES_H
#define CLASSES_H


class Table_statement {
	
	public:	
		Table_statement();
		string column_name;
		string column_type;
		string column_default;
		bool primary_key;
};

class Configuration {
	
	private:
		string username;
		string password;
		string host;
		string database;
		string site_url;
		string base_url;
		void set_search_categories(void);
		void set_database_configuration(void);
		void set_urls(string type = "local");
		
	public:
		Configuration();
		Configuration(string type);
		~Configuration();

		string get_username(void);
		string get_password(void);
		string get_host(void);
		string get_database(void);
		string get_site_url(void);
		string get_base_url(void);
		
		vector<string>search_categories;
};

class Database {
	
	private:
		// VARIABLES
		Configuration configuration;//configuration settings that will go to the database object
		Helper helper;//helper functions -- please note helper.h
		
		//note could have used namespace sql but chose not too
		sql::Driver *driver;//initiate the driver
		sql::Connection *con;//initiate the connection
		sql::Statement *stmt;//statement
		sql::ResultSet *res;//results
		sql::PreparedStatement *pstmt;//prepared statement--for queries
		
		// FUNCTIONS
		string from(string);
		string where(vector<where_statement>where_parameter, string type = "=");
		string select(vector<column_description> select);
		string join(vector<join_statement>, string type = "FULL");
		void statement_results(string statement, vector<column_description> select_parameter, vector<row_result> &results);
		void table_description(string table, vector<string> select, vector<column_description> &select_statement);

	public:
		Database();
		Database(Configuration);//will open the connection to the database
		~Database();//will close out the connection
		void database_error(std::exception);

		// TO BE IN AN EXTENDED CLASS LATER
		void create_table(string, vector<Table_statement>);
		void query_join(string, vector<column_description>, vector<join_statement>, vector<where_statement>);
		void query(string table, vector<string> select, vector<where_statement> where, vector<row_result> &results);
		void query_like(string table, vector<string> select_list, vector<where_statement> where_parameter, vector<row_result> &results);
		
};



#endif