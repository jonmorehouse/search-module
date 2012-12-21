# Dependencies--these are the following files I used in my main_header.h file

	# /usr/local/Cellar/mysql-connector-c++/1.1.0/include/mysql_connection.h
	# /usr/local/Cellar/mysql-connector-c++/1.1.0/include/mysql_driver.h
	# /usr/local/Cellar/mysql-connector-c++/1.1.0/include/cppconn/driver.h
	# /usr/local/Cellar/mysl-connector-c++/1.1.0/include/cppconn/exception.h
	# /usr/local/Cellar/mysql-connector-c++/1.1.0/incude/cppconn/resultset.h
	# /usr/local/Cellar/mysql-connector-c++/1.1.0/include/cppconn/statement.h
	
# lib files for mysql-connector-c++ library:
	# /usr/local/Cellar/Mysql-connector-c++/1.1.0/lib/libmysqlcppconn-static.a
	# /usr/local/Cellar/Mysql-connector-c++/1.1.0/lib/libmysqlcppconn.5.dylib
	# /usr/local/Cellar/Mysql-connector-c++/1.1.0/lib/libmysqlcppconn.5.1.1.0.dylib					
	# /usr/local/Cellar/Mysql-connector-c++/1.1.0/lib/libmysqlcppconn.dylib
	
##### BEGGINNING OF MAKE FILE

CC = g++

CFLAGS= -c -Wall

LINKFLAGS= -lmysqlcppconn

all: main.out

# which files main.out depends upon! -- 

main.out: main.cpp main.cpp classes/database.cpp classes/configuration.cpp classes/table_statement.cpp classes/helper.cpp classes/prospero.cpp classes/search.cpp classes/property_get.cpp classes/property_elements.cpp

	$(CC) $(LINKFLAGS) -o main.out main.cpp classes/database.cpp classes/configuration.cpp classes/table_statement.cpp classes/helper.cpp classes/prospero.cpp classes/search.cpp classes/property_get.cpp classes/property_elements.cpp


#END OF MAKE FILE



