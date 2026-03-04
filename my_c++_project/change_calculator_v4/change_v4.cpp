#include "splashkit.h"
#include <stdio.h>
#include "utilities.h"

const int MAX_COINS_TYPES = 10; 


/** struct to represent a coin type in the machine
 *
 * @field value - the coin’s value in cents (e.g., 200 for $2, 50 for 50c)
 * @field text  - the coin’s text label (e.g., "$2, ", "50c, ")
 */
struct coin_data
{
    int value;     
    string text;    
};

/** struct to represent the coin machine
 *
 * @field coins      - an array holding up to MAX_COINS_TYPES coin_data
 * @field coin_count - the number of coin types currently in the machine
 */
struct machine_data
{
    coin_data coins[MAX_COINS_TYPES]; 
    int coin_count;                   
};


/** procedure to set up the machine with Australian coin types
 *
 * @param machine passed by reference, of data type machine_data; will be filled with coin values and labels
 * 
 */
void setup_machine(machine_data &machine)
{
    // There are 6 Australian coins
    machine.coin_count = 6;

    machine.coins[0].text = "$2, ";
    machine.coins[0].value = 200;

    machine.coins[1].text = "$1, ";
    machine.coins[1].value = 100;

    machine.coins[2].text = "50c, ";
    machine.coins[2].value = 50;

    machine.coins[3].text = "20c, ";
    machine.coins[3].value = 20;

    machine.coins[4].text = "10c, ";
    machine.coins[4].value = 10;

    machine.coins[5].text = "5c ";
    machine.coins[5].value = 5;
}

/** procedure to calculate and display change for a transaction
 *
 * @param change_value an integer representing the amount of change (in cents)
 * @param machine      passed by reference, of data type machine_data;contains the available coin types
 *
 * The procedure outputs the number of each coin to be given as change.
 * 
 */
void give_change(int change_value, machine_data &machine)
{
    int to_give;

    write("Change: ");

    for (int i = 0; i < machine.coin_count; i++)
    {
        coin_data &coin = machine.coins[i];  // reference to avoid copy

        to_give = change_value / coin.value;
        change_value -= to_give * coin.value;

        if (to_give > 0)
        {
            write(std::to_string(to_give) + " x " + coin.text);
        }
    }

    write_line();
}

/** main program for change calculator program
 *
 * The program:
 *  - asks the user for the cost of an item
 *  - asks the user for the amount paid
 *  - calculates and displays the change in coins (if sufficient funds)
 *  - prompts the user to run again until 'N' or 'n' is entered
 */
int main()
{
    int cost_of_item;
    int amount_paid;
    string again = "";
    machine_data machine;
    setup_machine(machine);

    do
    {
        cost_of_item = read_integer("Enter cost of item in cents: ");
        amount_paid = read_integer("Enter amount paid in cents: ");

        if (amount_paid >= cost_of_item)
        {
            give_change(amount_paid - cost_of_item, machine);
        }
        else
        {
            write_line("Insufficient funds!!!");
        }

        write_line("");
        write("run again: ");
        again = read_line();

    } while (again != "N" && again != "n");
}
