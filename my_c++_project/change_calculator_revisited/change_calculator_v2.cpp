#include "splashkit.h"

/**
 * Prompt the user input data base on the prompt message passed to the function
 * The function returns an integer value
 * @param prompt_message A message to be outputed to the user dictating what to input
 */
int read_integer(string prompt_message)
{
    write(prompt_message);
    return stoi(read_line());
}

/**
 * The logic about how to break down the chage in the diffrent value coin.
 * @param change change to be brocken down in to the different coins.
 */
void give_change(int change)
{
    const int COINS_TYPES = 6;

    const int TWO_DOLLARS = 200;
    const int ONE_DOLLAR = 100;
    const int FIFTY_CENTS = 50;
    const int TWENTY_CENTS = 20;
    const int TEN_CENTS = 10;
    const int FIVE_CENTS = 5;

    int to_give;

    write("change: ");

    int coin_value;
    string coin_text;
    for (int i = 0; i < COINS_TYPES; i++)
    {
        switch (i)
        {
        case 0:
            coin_value = TWO_DOLLARS;
            coin_text = "$2, ";
            break;

        case 1:
            coin_value = ONE_DOLLAR;
            coin_text = "$1, ";
            break;

        case 2:
            coin_value = FIFTY_CENTS;
            coin_text = "50c, ";
            break;

        case 3:
            coin_value = TWENTY_CENTS;
            coin_text = "20c, ";
            break;

        case 4:
            coin_value = TEN_CENTS;
            coin_text = "10c, ";
            break;

        case 5:
            coin_value = FIVE_CENTS;
            coin_text = "5c, ";
            break;

        default:
            coin_value = 0;
            coin_text = "ERROR";
            break;
        }    
        to_give = change / coin_value;
        change = change - (to_give * coin_value);       
        write(std::to_string(to_give) + " x " + coin_text);
    }
    write_line();
}


/**
 * The main program
 */
int main()
{
    int cost_of_item;
    int amount_paid;
    string again = "";

    do
    {
        cost_of_item = read_integer("Enter cost of item in cents: ");
        amount_paid = read_integer("Enter amount paid in cents: ");

        if (amount_paid >= cost_of_item)
        {
            give_change(amount_paid - cost_of_item);
        }
        else
        {
            write_line("Insufficient funds!!!");
        }

        write("run again: ");
        again = read_line();

    } while (again != "N" && again != "n");
}