def read_string(prompt):
    """Prompt the user with a message and return their string input."""
    return input(prompt)

def read_integer_limit(prompt, min_val, max_val):
    """Prompt the user to enter an integer within a specified range."""
    while True:
        try:
            value = int(input(prompt))
            if min_val <= value <= max_val:
                return value
            print("Please enter a integer number in the correct range.")
        except ValueError:
            print("Please enter a integer number in the correct range.")

class AccDetails:
    """Represents an account with a username and password."""
    
    def __init__(self, username, password):
        """Construct a new account with the given username and password."""
        self.username = username
        self.password = password
        self.used_passwords = ["", "", ""]
        print("- Account set.")
    
    def test_login(self):
        """Prompt the user for username and password, and check login validity."""
        in_username = read_string("Username: ")
        in_password = read_string("Password: ")
        
        if in_username == self.username and in_password == self.password:
            print("- Login successful")
        else:
            print("- Login failed")
    
    def change_password(self):
        """Change the account password after validating credentials."""
        in_username = read_string("Username: ")
        in_password = read_string("Current password: ")
        new_password = read_string("New password: ")
        
        if in_username != self.username:
            print("- Failed to change password - invalid username")
        elif in_password != self.password:
            print("- Failed to change password - invalid password")
        elif new_password in self.used_passwords:
            print("- Failed to change password - password reuse")
        else:
            self.used_passwords[0] = self.used_passwords[1]
            self.used_passwords[1] = self.used_passwords[2]
            self.used_passwords[2] = self.password
            self.password = new_password
            print("Password changed successfully!")

def menu():
    """Display the account management menu options."""
    print("\n1: Set account")
    print("2: Test login")
    print("3: Change password")
    print("4: Quit")

def main():
    """Main entry point of the program."""
    account = AccDetails(read_string("Username: "), read_string("Password: "))
    
    while True:
        menu()
        print()
        choice = read_integer_limit("> ", 1, 4)
        
        if choice == 1:
            account = AccDetails(read_string("Username: "), read_string("Password: "))
        elif choice == 2:
            account.test_login()
        elif choice == 3:
            account.change_password()
        elif choice == 4:
            break

if __name__ == "__main__":
    main()