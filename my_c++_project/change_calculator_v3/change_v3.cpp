#include "splashkit.h"
#include "utilities.h"

const int COIN_TYPES =6;


/**
 * The different kinds of coins in the system
 */
enum coin_type
{
    NO_COIN = -1,
    TWO_DOLLAR,
    ONE_DOLLAR,
    FIFTY_CENTS,
    TWENTY_CENTS,
    TEN_CENTS,
    FIVE_CENTS
};

/**
 * Each coin has a value and text. This is used to
 * calculate the number of coins to give in change, and
 * to determine what text to show the user.
 *
 * @field value The value of the coin
 * @field text  The coin text for output
 */
struct coin_data
{
    int value;
    coin_type kind;
    string descri;
};

/**
 * Initialise a new coin of the indicated kind
 *
 * @param kind  The kind of coin to setup
 * @return coin data of the indicated kind
 */
coin_data new_coin(coin_type type)
{
    coin_data coin;

    coin.kind = type;

    switch(type)
    {
        case TWO_DOLLAR:
            coin.descri = "$2, ";
            coin.value = 200;
            break;
        case ONE_DOLLAR:
            coin.descri = "$1, ";
            coin.value = 100;
            break;

        case FIFTY_CENTS:
            coin.descri = "50c, ";
            coin.value = 50;
            break;
        case TWENTY_CENTS:
            coin.descri = "20c, ";
            coin.value = 20;
            break;
        
        case TEN_CENTS:
            coin.descri = "10c, ";
            coin.value = 10;
            break;
        case FIVE_CENTS:
            coin.descri = "5c, ";
            coin.value = 5;
            break;
        default:
            coin.descri = "ERROR";
            break;     
    }
    return coin;

}

/**
 * Give the user change of the indicated amount.
 *
 * @param change_value the amount of change to give
 */
void give_change(int change_value)
{
  int to_give;

  write("Change: ");

  for (int i = 0; i < COIN_TYPES; i++)
  {
    coin_data coin = new_coin(coin_type(i));

    to_give = change_value / coin.value;
    change_value = change_value - to_give * coin.value;
    write(std::to_string(to_give) + " x " + coin.descri);
  }

  write_line();
}

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

        write_line("");
        write("run again: ");
        again = read_line();

    } while (again != "N" && again != "n");
}