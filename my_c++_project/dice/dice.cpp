#include "splashkit.h"

/**
 * @brief Read a line of input from the user as a string.
 *
 * Prompts the user with a given message and returns the input as a string.
 *
 * @param prompt The message displayed to the user
 * @return The string entered by the user
 */
string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

/**
 * @brief Read an integer from the user.
 *
 * Keeps prompting until the user enters a valid integer.
 *
 * @param prompt The message displayed to the user
 * @return The integer entered by the user
 */
int read_integer(string prompt){
    string line = read_string(prompt);
    
    while (!is_integer(line))
    {
        write_line("Please enter a integer number.");
        line = read_string(prompt);
    }
    return stoi(line);
}

/**
 * @brief Read an integer within a given range from the user.
 *
 * Keeps prompting until the user enters a valid integer between min and max.
 *
 * @param prompt The message displayed to the user
 * @param min The minimum valid value
 * @param max The maximum valid value
 * @return The integer entered by the user, guaranteed to be in [min, max]
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
 * @brief Represents a die (dice) with a given number of faces.
 *
 * Provides methods to roll the die and print its current value.
 */
class dice
{
private:
    int face;
    int current_value;
public:

    /**
     * @brief Construct a new dice object with a specified number of faces.
     *
     * @param die_face The number of sides of the die
     */
    dice(int die_face){
        this->face = die_face;
    }

    /**
     * @brief Print the die's number of sides and its current rolled value.
     */
    void print_die(){
        printf("%d sides: value is %d\n", face, current_value);
    }

    /**
     * @brief Roll the die to generate a new random value.
     *
     * Uses splashkit's rnd function to generate a random number
     * between 1 and the number of sides of the die.
     */
    void roll_die(){
        current_value = rnd(1,face);
    }
};

/**
 * @brief Display the program menu options to the user.
 */
void menu(){
    printf("\n1: Roll die\n");
    printf("2: Get new die\n");
    printf("3: Quit\n");
}

/**
 * @brief Main program entry point.
 *
 * Creates a die with user-specified sides, then provides
 * a menu to roll the die, create a new die, or quit.
 *
 * @return Exit status code
 */
int main(){
    dice die(read_integer("Sides: "));

    int choice;

    do
    {
        menu();
        choice = read_integer_limit("> ", 1, 3);

        if (choice == 1){
            die.roll_die();
            die.print_die();
        }
        else if (choice == 2)
        {
            die = dice(read_integer("Sides: "));
        }
       
    } while (choice != 3);
 
    return 0;
}

