#ifndef FILES_H_
#define FILES_H_
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class files
{
private:
    double income;
    double expenses;
    double savings;

public:
    files()
    {
        income = 0.0;
        expenses = 0.0;
        savings = 0.0;
    }
    files(double, double, double);
    ~files() {}
    void addEntry(sql::Statement &statement, sql::ResultSet *res);
    void deleteEntry(sql::Statement &statement, sql::ResultSet *res);
    double totalIncome(sql::Statement &statement, sql::ResultSet *res);
};

#endif