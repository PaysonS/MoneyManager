#ifndef FILES_H_
#define FILES_H_


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
    double addEntry();
    double modifyEntry();
    double deleteEntry();
    double totalIncome();
    double totalExpenses();
    double totalSavings();



};










#endif