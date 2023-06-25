#include <iostream>
#include <fstream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "files.h"

bool userCheck(std::string, std::string);
void begin();
void action(sql::Statement *stmt,sql::ResultSet*, double &);

int main()
{
    std::string username, password, cont;
    double total;
    // checks if the login is correct and if not it restarts program
    begin();
    std::cin >> username >> password;
    if (!(userCheck(username, password)))
    {
        std::cout << "ERROR: Invalid Username or Password\n";
        main();
    }
    // creates the connection into the mysql database
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    // creates the driver object
    driver = sql::mysql::get_mysql_driver_instance();
    // creates the connection object
    con = driver->connect("tcp://127.0.0.1:3306", "root", "password"); // change to the appropriate address port, username, and password
    con->setSchema("management");                                      // change this to your database name
    sql::Statement *stmt;
    sql::ResultSet *res;
    stmt = con->createStatement();
    // test code to run to see if youre connected
    //  res = stmt->executeQuery("SELECT * FROM statements");

    // while(res->next()){
    //     int id = res->getInt("id");

    //     std::cout << id << std::endl;
    // }

        do
    {
        action(stmt,res,total);
        std::cout << total << std::endl;
        std::cout << "Would you like to add more? (Y/N)\n";
        std::cin >> cont;
    } while (cont == "Y" || cont == "y");

    // cleans up the connections
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

double files::addEntry(sql::Statement &stmt, double &total)
{
    std::string input;
    std::string desc;
    double deposit;
    double withdrawal;

    std::cout << "Which would you like to do?\n"
              << "Deposit(1)\n"
              << "Withdraw(2)\n";
    std::cin >> input;
    if (input == "1")
    {
        std::cout << "How much would you like to deposit?\n";
        std::cin >> deposit;
        std::cout << "Enter a description.\n";
        std::cin >> desc;
        total += deposit;
        try
        {
            stmt.execute("INSERT INTO statements(description, withdrawals, deposits, balance) VALUES ('" + desc + "', 0.00, " + std::to_string(deposit) + ", " + std::to_string(total) + ")");
        }
        catch (sql::SQLException &e)
        {
            std::cout << "SQL Exception caught: " << e.what() << std::endl;
        }
    }
    else if (input == "2")
    {
        std::cout << "How much would you like to withdraw?\n";
        std::cin >> withdrawal;
        if (total <= withdrawal)
        {
            std::cout << "You dont have enough money to withdraw please try again.\n";
            addEntry(stmt, total);
        }
        std::cout << "Enter a description.\n";
        std::cin >> desc;
        total -= withdrawal;
        try
        {
            stmt.execute("INSERT INTO statements(description, withdrawals, deposits, balance) VALUES ('" + desc + "', " + std::to_string(withdrawal) + ", 0.00, " + std::to_string(total) + ")");
        }
        catch (sql::SQLException &e)
        {
            std::cout << "SQL Exception caught: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: Invalid Input\n";
        addEntry(stmt, total);
    }

    return total;
}

double files::deleteEntry(sql::Statement &stmt,sql::ResultSet *res, double &total)
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

void action(sql::Statement *stmt,sql::ResultSet *res, double &total)
{
    files obj;
    int input;
    std::cout << "What action would you like to perform?\n"
              << "Add a transcation(1)\n"
              << "Delete a transcation(2)\n"
              << "See total Income(3)\n"
              << "See total expenses(4)\n"
              << "See total savings(5)\n";
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
        total = obj.addEntry(*stmt, total);
    }
    else if (input == 2)
    {
        obj.deleteEntry(*stmt, res, total);
    }
    else if (input == 3)
    {
        obj.totalIncome();
    }
    else if (input == 4)
    {
        obj.totalExpenses();
    }
    else if (input == 5)
    {
        obj.totalSavings();
    }
}