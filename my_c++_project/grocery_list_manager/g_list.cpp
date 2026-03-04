#include "splashkit.h"
#include <vector>

const int max_item = 20;

/**
 * @brief Prompts the user for a string input.
 *
 * @param prompt The message to display before input.
 * @return The string entered by the user.
 */
string read_string(string prompt){
    string line;
    write(prompt);
    line = read_line();
    return line;
}

/**
 * @brief Reads and validates an integer within a given range.
 *
 * Keeps asking until the user enters a valid integer between `min` and `max`.
 *
 * @param prompt The message to display before input.
 * @param min The minimum valid value.
 * @param max The maximum valid value.
 * @return The validated integer entered by the user.
 */
int read_int_limit(string prompt, int min, int max){
    string line = read_string(prompt);
    while (!is_integer(line) || stoi(line) < min || stoi(line) > max){
        write_line("Please enter a valid number");
        line = read_string(prompt);
    } 
    return stoi(line);
}

/**
 * @brief Adds a new item to the grocery list.
 *
 * @param items The vector storing grocery items.
 */
void add_item(std::vector<string> &items){
    string item;
    item = read_string("Enter item: ");
    items.push_back(item);
    write_line("Item added");
}

/**
 * @brief Displays all items in the grocery list.
 *
 * If the list is empty, it will display a message instead.
 *
 * @param items The vector storing grocery items.
 */
void print_items(std::vector<string> &items){
    if (items.size() == 0){
        write_line("List is empty");
        return;
    }
    write_line("Items in the grocery list: ");
    for(int i = 0; i < items.size(); i++){
        write_line("-> " + items[i]);
    }
}

/**
 * @brief Removes an item from the grocery list by name.
 *
 * If the item exists, it is removed. Otherwise, a "not found" message is shown.
 *
 * @param items The vector storing grocery items.
 */
void remove_item(std::vector<string> &items){
    string item;
    item = read_string("Enter item to remove: ");
    for(int i = 0; i < items.size(); i++){
        if(items[i] == item){
            items.erase(items.begin() + i);
            write_line("Item removed");
            return;
        }
    }
    write_line("Item not found");
}

/**
 * @brief Displays the main menu options.
 */
void menu(){
    write_line("1. Add item");
    write_line("2. Print items");
    write_line("3. Remove item");
    write_line("4. Quit");
}

/**
 * @brief Entry point for the Grocery List Manager program.
 *
 * Allows the user to:
 * - Add up to 20 items
 * - Print all items
 * - Remove items
 * - Quit the program
 *
 * @return 0 on successful program termination.
 */
int main(){
    std::vector<string> items;
    int curr_items = 0;
    int choice;
    do{
        menu();
        choice = read_int_limit("Enter choice: ",1,4);
        write_line("");
        switch (choice)
        {
        case 1:
            if (curr_items<max_item){
                add_item(items);
                write_line("");
                curr_items++;
            }else
            {
                write_line("List is full");
            }      
            break;

        case 2:
            write_line("");
            print_items(items);
            write_line("");
            break;
        case 3:
            write_line("");
            remove_item(items);
            write_line("");
            break;
        }

    }while(choice != 4);
    return 0;
}