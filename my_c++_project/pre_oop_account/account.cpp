#include "splashkit.h"

/**
 * @brief Represents a bank account with a name and balance.
 *
 * Provides methods to print the account, deposit money, and withdraw money.
 */
class bank_account{
private:
    double balance;
public:
    string name;

    /**
     * @brief Construct a new bank account with a given name and initial balance.
     *
     * @param name the account holder's name
     * @param balance the initial balance of the account
     */
    bank_account(string name, double balance){
        this->name = name;
        this->balance = balance;
    }

    /**
     * @brief Construct a new bank account with default values.
     *
     * Default name is "Unknown", balance is 0.
     */
    bank_account(){
        name = "Unknown";
        balance = 0;
    }

    /**
     * @brief Print the account name and balance.
     */
    void print(){
        write_line(name + ": $" + std::to_string(balance));
    }

    /**
     * @brief Deposit money into the account.
     *
     * @param amount the amount to deposit
     */
    void deposit(double amount){
        balance += amount;
        write_line("$" + std::to_string(amount) + " has been deposited");
    }

    /**
     * @brief Withdraw money from the account.
     *
     * If there is not enough balance, the withdrawal will fail.
     *
     * @param amount the amount to withdraw
     */
    void withdraw(double amount){
        if (balance >= amount){
            balance -= amount;
            write_line("$" + std::to_string(amount) + " has been withdraw");
        }
        else{
            write_line("Not enought money...");
        }
    }
};

/**
 * @brief Base class for transactions performed on a bank account.
 *
 * Defines the common interface and state for all transactions,
 * such as whether it has been performed, whether it succeeded,
 * and the transaction amount.
 */
class transaction{
    protected:
        bool performed = false;
        bool succeeded = false;
        double amount;
        bank_account *d_account;

    public:


        /**
         * @brief Construct a new transaction.
         *
         * @param d_acc pointer to the bank account
         * @param a the transaction amount
         */
        transaction(bank_account *d_acc, double a){
            this->d_account = d_acc;
            this->amount = a;
        }

        /**
         * @brief Perform the transaction.
         *
         * Must be overridden by derived classes.
         */
        virtual void perform() = 0;

        /**
         * @brief Check whether the transaction has been performed.
         *
         * @return true if the transaction has been performed
         * @return false otherwise
         */

        bool was_performed() const{
            return performed;
        }

        /**
         * @brief Check whether the transaction was successful.
         *
         * @return true if the transaction succeeded
         * @return false otherwise
         */
        bool was_successful() const{
            return succeeded;
        }
};

/**
 * @brief A withdrawal transaction that deducts money from a bank account.
 */
class widthdraw_transaction : public transaction{
    public:

        /**
         * @brief Construct a new withdraw transaction.
         *
         * @param acc pointer to the bank account
         * @param a the amount to withdraw
         */
        widthdraw_transaction(bank_account *acc, double a) : transaction(acc, a) {}

        /**
         * @brief Perform the withdrawal.
         *
         * If already performed, throws an error string.
         * Attempts to withdraw money from the account.
         *
         * @throws string if the transaction has already been performed
         */
        void perform() override{
            if (performed){
                string error_msg = "Transaction already performed";
                throw error_msg;
            }

            try
            {
                d_account->withdraw(amount);
                succeeded = true;
            }
            catch(const string &e)
            {
                write_line("Transaction failed: " + e);
                succeeded = false;
            }
            performed = true;
        }
};

/**
 * @brief A deposit transaction that adds money to a bank account.
 */
class deposit_transaction : public transaction{
    public:
        /**
         * @brief Construct a new deposit transaction.
         *
         * @param acc pointer to the bank account
         * @param a the amount to deposit
         */
        deposit_transaction(bank_account *acc, double a) : transaction(acc,a) {}

        /**
         * @brief Perform the deposit.
         *
         * If already performed, throws an error string.
         * Attempts to deposit money into the account.
         *
         * @throws string if the transaction has already been performed
         */
        void perform() override{
            if (performed){
                string err_msg= "Transaction already performed" ;
                throw err_msg;
            }

            try {
                d_account->deposit(amount);
                succeeded = true;
            }
            catch(const string &e)
            {
                write_line("Transaction failed " + e);
                succeeded = false;
            }
            performed = true;
        }
};

int main(){
    bank_account acc("sam", 90125);

    transaction *test;

    acc.print();

    test = new widthdraw_transaction(&acc, 1000);

    test->perform();

    if (test->was_successful()){
        write_line("Transaction successful!");
    }
    else {
        write_line("Transaction failed");
    }

    acc.print();

    test = new deposit_transaction(&acc, 2000);
    test->perform();

    if (test->was_successful()){
        write_line("Transaction successful!");
    }
    else{
        write_line("Transaction failed");
    }
    acc.print();
    return 0;
}

