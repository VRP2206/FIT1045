#include "splashkit.h"

/**
*allows the user to input a value(his guess number), then compares it to the secret number and return a boolean value on where he guessed correctly
* @param current_no The current number of tries of guess the user is on
* @param secret_num The number the user is trying to guess
*/
bool perform_guess(int current_no,int secret_num)
{
    int guess;
    write("Guess " + std::to_string(current_no)+ ": ");
    guess = stoi(read_line());

    if (secret_num<guess)
    {
        write_line("The number is less than " + std::to_string(guess));
        return false;
    }
    else if(secret_num>guess)
    {
        write_line("The number is larger than " + std::to_string(guess));
        return false;
    }
    else if(secret_num== guess)
    {
        write_line("The number was indeed " + std::to_string(guess) + ". GOOD JOB!!!");
        return true;
    }
    return false; 
}

/**
 * Prints a number of '-' to create a line for seperating section of output window.
 * @param len the number of '-' to print for the seperation line, this will affect the length of the speration line.
 */
void print_line(int len)
{
    for(int i = 0; i< len; i++)
    {
        write("-");
    }
    write_line("");
}


/**
 * Procedure that contain the logic of the program 
 */
void play_game()
{
    bool won = false;
    string play_again;
    int secret_num, current_guess_no;

    const int NUMBER_OF_GUESS =7;


    current_guess_no = 0;
    secret_num= rnd(101);

    while ((current_guess_no< NUMBER_OF_GUESS) && !won)
       {
            current_guess_no +=1;
            won = perform_guess(current_guess_no,secret_num);
            
        }

    if (!won)
        {
           write_line("You ran out of guesses... the number was " + std::to_string(secret_num));
        }
}


/**
 * The main program
 */
int main()
{
    string play_again;

    write_line("I am thinking of a number between 1 and 100");
    write_line("");

    do  // allow the user to play again
    {
        play_game();
        print_line(50);
        write_line("");
        write("Play again? [Y or N]: ");
        play_again = read_line();
    } while (play_again != "n" && play_again !="N");

    write_line("");
    write_line("Bye");

}