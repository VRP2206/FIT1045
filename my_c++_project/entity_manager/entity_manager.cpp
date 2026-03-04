#include "splashkit.h"
#include "utilities.h"

/**
 * The menu_option enum represents the different choices a user can make
 * from the menu. Each option is assigned a numeric value for user input.
 */
enum menu_option
{
    READ_BOOK=1,
    PRINT_BOOK,
    QUIT
};

/**
 * The book struct stores information about a single book, including:
 * - name: the book’s title
 * - location: where the book is kept
 * - num_of_pages: total number of pages
 */
struct book
{
    string name;
    string location;
    int num_of_pages;
};

/** Creates a new book by asking the user to enter details.
 * 
 * @return A book struct with user-provided details.
 */
book new_book()
{
    book livre;  

    write("Entre the name of the book: ");
    livre.name = read_line();
    write("Entre book location: ");
    livre.location = read_line();
    livre.num_of_pages = read_integer("Pages: ");

    return livre;
}

/**Displays the menu options and reads the user’s choice.
 * 
 * @return A menu_option enum value based on user selection.
 */
menu_option menu()
{
    int choice;
    choice = read_integer("OPtion: ");

    switch (choice)
    {
    case 1:
        return READ_BOOK;
        break;
    case 2:
        return PRINT_BOOK;
        break;
    case 3:
        return QUIT;
        break;    
    default:
        write_line("Incorect input");
        return menu();
        break;
    }
}

/**
 * Prints details of the given book to the console.
 * 
 * @param livre The book struct containing the details to print.
 */
void print_book(book livre)
{
    write_line("Book details: ");
    write_line("Title: " + livre.name);
    write_line("Location: " + livre.location);
    write_line("Pages: " + std::to_string(livre.num_of_pages));
}

int main()
{
    book livre;
    menu_option choice;
    write_line("Book entry system: ");
    write_line("");

    livre =  new_book();

    do
    {
        write_line("");
        write_line("Menu");
        write_line("1 - Read book");
        write_line("2 - Print book");
        write_line("3 - Quit");
        choice = menu();

        switch (choice)
        {
        case READ_BOOK:
            livre = new_book();       
            break;
        case PRINT_BOOK:
            write_line("");
            print_book(livre);
            break;
        case QUIT:
        break;
        
        default:
            write_line("error!!!");
            break;
        }
    } while (choice != QUIT);
    
}


