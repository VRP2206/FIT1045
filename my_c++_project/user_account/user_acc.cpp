#include "splashkit.h"
#include <stdio.h>

/**
 * @brief Prompt the user with a message and return their string input.
 *
 * @param prompt the message to display before input
 * @return string the user input read from the console
 */
string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

/**
 * @brief Prompt the user to enter an integer within a specified range.
 *
 * Keeps asking until the input is valid and within the range [min, max].
 *
 * @param prompt the message to display before input
 * @param min the minimum acceptable integer
 * @param max the maximum acceptable integer
 * @return int a valid integer between min and max
 */
int read_integer_limit(string prompt, int min, int max)
{
    string line = read_string(prompt);
    int temp = min - 1;
    while (temp < min || temp > max)
    {
        while (!is_integer(line))
        {
            write_line("Please enter a integer number in the correct range.");
            line = read_string(prompt);
        }
        temp = stoi(line);
    }

    return temp;
}

/**
 * @brief Represents an account with a username and password.
 *
 * The class stores the current password, a history of the last 3
 * used passwords (to prevent reuse), and provides methods for
 * login testing and password management.
 */
class acc_details
{
private:
    string password;
    string used_password[3];

public:
    string username;

    /**
    * @brief Construct a new account with the given username and password.
    *
    * @param user_name the username to set
    * @param pass_word the initial password
    */
    acc_details(string user_name, string pass_word)
    {
        this->username = user_name;
        this->password = pass_word;
        printf("- Account set.\n");
    }

    /**
    * @brief Prompt the user for username and password, and check login validity.
    *
    * If the input matches the stored username and password, login is successful.
    * Otherwise, login fails.
    */
    void test_login()
    {
        string in_username = read_string("Username: ");
        string in_password = read_string("Password: ");

        if (in_username == username && in_password == password)
        {
            printf("- Login successful\n");
            return;
        }
        else
        {
            printf("- Login failed\n");
        }
    }

    /**
     * @brief Change the account password after validating credentials.
     *
     * Checks:
     * - Username must match the stored username.
     * - Current password must match.
     * - New password must not be one of the last 3 used.
     *
     * If successful, the password is updated, and the password history is shifted.
     */
    void change_password()
    {
        string in_username = read_string("Username: ");
        string in_password = read_string("Current password: ");
        string new_password = read_string("New password: ");
        bool flag = false;

        for (int i = 0; i < 3; i++)
        {
            if (new_password == used_password[i])
            {
                flag = true;
            }
        }

        if (!(in_username == username))
        {
            printf("- Failed to change password - invalid username\n");
            return;
        }
        else if (!(in_password == password))
        {
            printf("- Failed to change password - invalid password\n");
            return;
        }
        else if (flag)
        {
            printf("- Failed to change password - password reuse\n");
        }
        else
        {

            for (int i = 1; i < 3; i++)
            {
                used_password[i - 1] = used_password[i];
            }
            used_password[2] = password;
            password = new_password;
            printf("Password changed successfully!\n");
        }
    }
};

/**
 * @brief Display the account management menu options.
 */
void menu()
{
    printf("\n1: Set account");
    printf("\n2: Test login");
    printf("\n3: Change password");
    printf("\n4: Quit");
}

/**
 * @brief Main entry point of the program.
 *
 * Provides a simple account management system that:
 * - Creates an account
 * - Allows login testing
 * - Allows password changes with history checks
 *
 * Runs in a loop until the user chooses to quit.
 */
int main(){
    acc_details account(read_string("Username: "), read_string("Password: "));

    int choice;
    do{
        menu();
        printf("\n");
        choice = read_integer_limit("> ", 1, 4);

        switch (choice){
        case 1:
            account = acc_details(read_string("Username: "), read_string("Password: "));
        case 2:
            account.test_login();
            break;

        case 3:
            account.change_password();
            break;

        case 4:
            break;
        }

    } while (choice != 4);
}
