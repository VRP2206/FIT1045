#include "splashkit.h"
#include <stdio.h>
/** Struct data type to store account details;
 * name of account holder
 * Annual Interest percentage
 * Amount in account
 */
struct account_details
{
    string name;
    double intrest;
    double amount;
};

/** function to validate user input for intrest amount
 * 
 * @param prompt conatin the output message to let the user know what to enter; pass as const reference
 * 
 * @return intrest of type double
 */
double read_interest(const string &prompt)
{
    write(prompt);
    string line = read_line();
    double num;
    while (!is_double(line))
    {
        write_line("Please enter a numerical value greater than or equal to 0.");
        write(prompt);
        line = read_line();
    }
    num = stod(line);
    return num;
}

/** function to validate user input for amount
 * 
 * @param prompt conatin the output message to let the user know what to enter; pass as const reference
 * 
 * @return amount of type double
 */
double read_amount(const string &prompt)
{
    write(prompt);
    string line = read_line();
    bool flag = false;
    double num;
    do
    {
        while (!is_double(line))
        {
            write_line("Please enter a numerical value greater than or equal to 0.");
            write(prompt);
            line = read_line();
        }
        num = stod(line);
        if (num >= 0.0)
        {
            flag = true;
        }
        else
        {
            write_line("Please enter a value >= 0.");
            write(prompt);
            line = read_line();
        }
    } while (!flag);
    return num;
}

/** function to validate user input for choice
 * @param prompt conatin the output message to let the user know what to enter; pass as const reference
 * @param lower_limit contain the smallest valid number that can be entered by then user
 * @param upper_limit contain the largest valid number that can be entered by then user
 * 
 * 
 * @return choice of type integer
 */
int read_integer_limit(string prompt, int lower_limit, int upper_limit)
{
    write(prompt);
    string line = read_line();
    bool flag = false;
    int num;
    do
    {
        while (!is_integer(line))
        {
            write_line("Please enter a whole number between " + std::to_string(lower_limit) + " and " + std::to_string(upper_limit));
            write(prompt);
            line = read_line();
        }
        num = stoi(line);
        if (num >= lower_limit && num <= upper_limit)
        {
            flag = true;
        }
        else
        {
            write_line("Please enter a whole number between " + std::to_string(lower_limit) + " and " + std::to_string(upper_limit));
            write(prompt);
            line = read_line();
        }
    } while (!flag);
    return num;
}

/** Procedure to output the user account details
 * 
 * @param account of data type account_details; contain the deatils of the account; passed as const reference
 * 
 */
void print_acc_details(const account_details &account)
{
    printf("Account: %s\nRate: %lf\nBalance: %lf\n", account.name.c_str(), account.intrest, account.amount);
}

/** Procedure to allow the user to deposit money into the account
 * 
 * @param amount  of data type double; contain the amount in account; passed as reference as this value will change
 * 
 */
void deposit(double &amount)
{
    amount = amount + read_amount("Amount deposited: ");
    printf("Amount = %lf\n", amount);
}

/** Procedure to allow the user to withdraw money into the account
 * 
 * @param amount  of data type double; contain the amount in account; passed as reference as this value will change
 * 
 */
void withdrawn(double &amount)
{
    double w = read_amount("Enter amount to withdraw: ");
    if (w > amount)
    {
        write_line("Insufficient funds!");
    }
    else
    {
        amount -= w;
    }
}

/** Procedure to allow the user to process intrest into the account
 * 
 * @param intrest of data type double; contain the intrest percentage per annum of the account; passed as const reference
 * @param amount  of data type double; contain the amount in account; passed as reference as this value will change
 */
void add_intrest(const double &interest, double &amount)
{
    int days;
    double current_interest;
    days = read_integer_limit("Intrest for how many days: ", 1, 365);
    current_interest = interest * days / 365;
    printf("Rate is %lf%%  PA = %lf%%\n", interest, current_interest);
    printf("Interest = %lf\n", amount * current_interest / 100);
    amount += amount * current_interest / 100;
    printf("Amount = %lf\n", amount);
}

/** Menu function to process access the different option of the program
 * 
 * @param account of data type account_details; contain the deatils of the account; passed by reference
 * 
 * @return a boolean value for if the user want to quit the program
 */
bool menu(account_details &account)
{
    int choice;
    write_line("");
    write_line("Actions:");
    write_line("1. Print account details");
    write_line("2. Deposit");
    write_line("3. Withdraw");
    write_line("4. Add interest");
    write_line("5. Quits");
    choice = read_integer_limit("option ", 1, 5);

    switch (choice)
    {
    case 1:
        write_line("");
        print_acc_details(account);
        break;
    case 2:
        write_line("");
        deposit(account.amount);
        break;
    case 3:
        write_line("");
        withdrawn(account.amount);
        break;
    case 4:
        write_line("");
        add_intrest(account.intrest, account.amount);
        break;
    case 5:
        return true;
        break;

    default:
        write_line("");
        write_line("Error!!!!");
        break;
    }
    return false;
}

int main()
{
    printf("Simple transaction record!\n\n");

    account_details account;
    string choice;

    printf("Enter account name: ");
    account.name = read_line();
    account.intrest = read_interest("Enter interest percent (-/+): ");
    account.amount = read_amount("Enter initial ammount: ");

    do
    {
    } while (!menu(account));  // continue to process the user request until the user menu return true
}