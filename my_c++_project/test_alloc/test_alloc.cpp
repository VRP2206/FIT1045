#include "splashkit.h"
#include "utilities.h"

struct account{
    string name;
    int balance;
};

void print_account(account &act){
    write_line("Nmae: " + act.name);
    write_line("Balance: " + std::to_string(act.balance));
}

int main(){
    account *ptr;

    ptr =new account;
    ptr->name="My account";
    ptr->balance=154;

    print_account(*ptr);

    delete ptr;
    ptr = NULL;

    return 0;
}