max_item = 20

def read_integer_limit(prompt,min,max):
    """Prompt the user for an integer input within a given range."""
    flag = True
    while flag:
        try:
            user_input = int(input(prompt))
            if user_input>= min and user_input <= max:
                flag = False
                return user_input
        except ValueError:
            flag= True
            print("Error: Invalid input. Please enter an integer.")
            
def add_item(array):
    """Add a new item to the grocery list."""
    item = input("Enter item: ")
    array.append(item)
    print("Item added")

def display_items(array):
    """Display all items currently in the grocery list."""
    print("Items in the grocery list: ")
    for item in array:
        print(item)
        
def remove_item(array):
    """Remove an item from the grocery list if it exists."""
    item = input("Enter item to remove: ")
    if item in array:
        array.remove(item)
        print("Item removed")
    else:
        print("Item not found")
        
def menu():
    """Display the main menu options for the grocery list manager."""
    print("1. Add item")
    print("2. Display items")
    print("3. Remove item")
    print("4. Quit")
    
def main():
    array = []
    item = 0
    menu()
    choice = read_integer_limit("Enter your choice: ",1,4)
    while choice != 4:
        if choice == 1:
            print("")
            if item < max_item:
                item += 1
                add_item(array)
            else:
                print("List is full")
            print("")
        elif choice == 2:
            print("")
            display_items(array)
            print("")
        elif choice == 3:
            print("")
            remove_item(array)
            print("")
            
        menu()
        choice = read_integer_limit("Enter your choice: ", 1, 4)
        
if __name__ == "__main__":
    main()