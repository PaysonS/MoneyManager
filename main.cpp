#include <iostream>
#include <fstream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "files.h"

bool userCheck(std::string, std::string);
void begin();
void action(sql::Statement *stmt, sql::ResultSet *);

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
        action(stmt, res);
        std::cout << "Would you like to do another action? (Y/N)\n";
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

void files::addEntry(sql::Statement &stmt, sql::ResultSet *res) // double &total)
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
        // total += deposit;
        try
        {
            stmt.execute("INSERT INTO statements(description, withdrawals, deposits) VALUES ('" + desc + "', 0.00, " + std::to_string(deposit) + ")");
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
        if (totalIncome(stmt, res) <= withdrawal)
        {
            std::cout << "You dont have enough money to withdraw please try again.\n";
            addEntry(stmt, res);
        }
        std::cout << "Enter a description.\n";
        std::cin >> desc;
        // total -= withdrawal;
        try
        {
            stmt.execute("INSERT INTO statements(description, withdrawals, deposits) VALUES ('" + desc + "', " + std::to_string(withdrawal) + ", 0.00)");
        }
        catch (sql::SQLException &e)
        {
            std::cout << "SQL Exception caught: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: Invalid Input\n";
        addEntry(stmt, res);
    }
}

void files::deleteEntry(sql::Statement &stmt, sql::ResultSet *res)
{

    try
    {
        stmt.execute("DELETE FROM statements WHERE id = (SELECT * FROM (SELECT MAX(id) FROM statements) AS temp)");
    }
    catch (sql::SQLException &e)
    {
        std::cout << "SQL Exception caught: " << e.what() << std::endl;
    }
}
double files::totalIncome(sql::Statement &stmt, sql::ResultSet *res)
{
    double total;

    res = stmt.executeQuery("SELECT * FROM statements");
    while (res->next())
    {
        total += res->getDouble("deposits") - res->getDouble("withdrawals");
    }

    return total;
}

void action(sql::Statement *stmt, sql::ResultSet *res)
{
    files obj;
    int input;
    std::string entry;

    std::cout << "What action would you like to perform?\n"
              << "Deposit/withdraw(1)\n"
              << "Delete a transcation(2)\n"
              << "See total balance(3)\n";
    std::cin >> input;
    if (input == 1)
    {
        obj.addEntry(*stmt, res);
    }
    else if (input == 2)
    {

        std::cout << "Would you like to delete the most recent entry? (Y/N)\n";
        std::cin >> entry;
        if (entry == "Y" || entry == "y")
        {
            obj.deleteEntry(*stmt, res);
            std::cout << "You have deleted the most recent entry\n";
        }
        else
            action(stmt, res);
    }
    else if (input == 3)
    {

        std::cout << "Would you like to see your balance? (Y/N)\n";
        std::cin >> entry;
        if (entry == "Y" || entry == "y")
        {
            std::cout << "Your current balance is " << obj.totalIncome(*stmt, res) << std::endl;
        }
        else
        {
            action(stmt, res);
        }
    }
    else
    {
        std::cout << "ERROR: Invalid Input\n";
        action(stmt, res);
    }
}