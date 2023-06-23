#include <iostream>
#include <fstream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "files.h"

bool userCheck(std::string, std::string);
void begin();
void action(sql::ResultSet *res, sql::Statement *stmt);

int main()
{
    std::string username, password;
    //checks if the login is correct and if not it restarts program
    begin();
    std::cin >> username >> password;
    if (!(userCheck(username, password)))
    {
        std::cout << "ERROR: Invalid Username or Password\n";
        main();
    }
    //creates the connection into the mysql database
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    //creates the driver object
    driver = sql::mysql::get_mysql_driver_instance();
    //creates the connection object
    con = driver->connect("tcp://127.0.0.1:3306","root","password");//change to the appropriate address port, username, and password
    con->setSchema("management");//change this to your database name
    sql::Statement *stmt;
    sql::ResultSet *res;
    stmt = con->createStatement();
    //test code to run to see if youre connected
    // res = stmt->executeQuery("SELECT * FROM statements");

        // while(res->next()){
        //     int id = res->getInt("id");

        //     std::cout << id << std::endl;
        // }
    
    action(res,stmt);

    //cleans up the connections
    delete res;
    delete stmt;
    delete con;

    return 0;
}

files::files(double i, double e, double s)
{
    this->income = i;
    this->expenses = e;
    this->savings = s;
}

void begin()
{

    std::cout << "Hi, welcome to your personal finance management system!\n"
              << "Please enter your username and password.\n"; // the user and pass is username and password
}

bool userCheck(std::string user, std::string pass)
{
    if (user == "username" && pass == "password")
        return true;
    return false;
}

double files::addEntry(sql::ResultSet *res, sql::Statement &stmt)
{
    std::string input;
    double deposit;
    double overallAmount;
    std::cout << "Which would you like to do?\n"
              << "Deposit(1)\n"
              << "Withdraw(2)\n";
    std::cin >> input;
        if(input == "1"){
            std::cout << "How much would you like to deposit?\n";
            std::cin >> deposit;
            res = stmt.executeQuery("SELECT * FROM statements");
            while(res->next()){
            int id = res->getInt("id");

            std::cout << id << std::endl;
        }
        }


    return 0;
}
double files::modifyEntry()
{

    return 0;
}
double files::deleteEntry()
{

    return 0;
}
double files::totalIncome()
{

    return 0;
}
double files::totalExpenses()
{

    return 0;
}
double files::totalSavings()
{
    return 0;
}

void action(sql::ResultSet *res, sql::Statement *stmt)
{
    files obj;
    int input;
    std::cout << "What action would you like to perform?\n"
              << "Add a transcation(1)\n"
              << "Modify a transaction(2)\n"
              << "Delete a transcation(3)\n"
              << "See total Income(4)\n"
              << "See total expenses(5)\n"
              << "See total savings(6)\n";
    while (input < 1 || input > 6)
    {
        std::cout << "Please enter the corresponding number\n";
        std::cin >> input;
        if (input < 1 || input > 6)
        {
            std::cout << "Error: Invalid Entry Number\n";
        }
    }
    if (input == 1)
    {
        obj.addEntry(res,*stmt);
    }
    else if (input == 2)
    {
        obj.modifyEntry();
    }
    else if (input == 3)
    {
        obj.deleteEntry();
    }
    else if (input == 4)
    {
        obj.totalIncome();
    }
    else if (input == 5)
    {
        obj.totalExpenses();
    }
    else if (input == 6)
    {
        obj.totalSavings();
    }
}