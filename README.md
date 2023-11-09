# MoneyManager
This is a personal finance management system that utilizes c++ to help the user track their income, expenses, and savings.

First install MySQL if you do not have it using 
    sudo apt-get install mysql-server

Make sure you have the mysql C++ connector which can be done on linux by

    sudo apt-get install libmysqlcppconn-dev


Log into MySql user (usually root)
    mysql -u root -p
    "password"

Create your database
    CREATE DATABASE moneymanager

Run the appropriate sql commands given in moneymanager.sql

To run the program on a command line use the following command

    g++ main.cpp -lmysqlcppconn

    ./a.out

View contents of the statements table using 
    SELECT * FROM statements
