#include "splashkit.h"
#include "utilities.h"

/** emumarated day type created to allows only specific roles
 * role allowed are: NO_ACCESS, USER, ADMIN, SUPER_USER
 */
enum role_level
{
    NO_ACCESS,
    USER,
    ADMIN,
    SUPER_USER
};

/**structured data type user_data, it stores data of the user:
 * these data are: username, password, role 
 */
struct user_data
{
    string username;
    string password;
    role_level role;
};

/** function that read the option for role from user input and return the role
 * 
 * @return role of the user
 */
role_level read_role()
{
    int role_input = read_integer_limit("Enter role level (0 for NONE, 1 for USER 2 For ADMIN, 3 for SUPER_USER): ", 0, 3);

    switch (role_input)
    {
    case 0:
        return NO_ACCESS;
        break;
    case 1:
        return USER;
        break;
    case 2:
        return ADMIN;
        break;
    case 3:
        return SUPER_USER;
        break;
    default:
        write_line("Invalid role level. Setting role to NONE");
        return NO_ACCESS;
        break;
    }
}

/** Function to return the role in string data type from role_level data type
 * @param role of role_level data type
 * 
 * @return role in string data type
 */
string to_string(role_level role)
{
    switch (role)
    {
    case NO_ACCESS:
        return "No Access";
        break;

    case USER:
        return "User";
        break;

    case ADMIN:
        return "Admin";
        break;

    case SUPER_USER:
        return "Super User";
        break;

    default:
        return "ERROR!!!";
        break;
    }
}

/** Prints the details of the user
 * 
 * @param user of data type user_data; passed as a const reference to save memory
 */
void print_user(const user_data &user)
{
    write_line("The username is " + user.username + " and their role is " + to_string(user.role));
}


/** update user any details, can be one edit or multiple edits
 * 
 * @param user of data type user_data; passed by reference 
 */
void update_user(user_data &user)
{
    int choice;
    string line;
    string flag;

    do
    {
        // menu
        write_line("");
        write_line("1. Update username");
        write_line("2. Update password");
        write_line("3. Update role");
        choice = read_integer_limit("Enter choice: ", 1, 3);

        switch (choice)
        {
        case 1:
            write_line();
            write("Enter new username: ");
            user.username = read_line();
            write_line("Username change successfully.");
            break;
        case 2:
            write_line();
            write("Enter old password: ");
            line = read_line();

            if (user.password == line)
            {
                line = "";
                write("Enter new password: ");
                line = read_line();
                user.password = line;
                write_line("Password change successfully.");
            }
            else
            {
                write_line("Incorrect Password");
            }
            break;
        case 3:
            write_line();
            write("Enter new role: ");
            user.role = read_role();
            write_line("Role change successfully.");
            break;

        default:
            write_line("ERROR!!!");
            break;
        }
        write_line("");
        write("Anything more to change[y/n]: ");
        flag = read_line();

    } while (flag == "y" || flag == "Y");
}

int main()
{
    user_data user = {"My_user_name", "monash", USER};

    update_user(user);
    print_user(user);

    return 0;
}