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
    files(){
        income = 0.0;
        expenses = 0.0;
        savings = 0.0;
    }
    files(double, double, double);
    ~files(){}
    double addEntry( sql::Statement& statement, double total);
    double modifyEntry();
    double deleteEntry();
    double totalIncome();
    double totalExpenses();
    double totalSavings();



};










#endif