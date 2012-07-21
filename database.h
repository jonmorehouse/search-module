// HEADER GUARD--to prevent multiple inclusions of this document
#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>//it is definitely finding both of these files
#include <mysql_connection.h>//it is finding this as well-when I put the include in it gave a couldn't find error, not the couldn't find library error

//installed from brew-mysql-connector-c++--worked without moving it. Was able to find it in brew
// is this because of the brew path? or linking or something
//Included from brew install-working on mac
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <vector>

// WILL PUT FINALIZED DATABASE HEADER HERE

#endif