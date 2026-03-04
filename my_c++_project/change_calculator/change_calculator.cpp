#include "splashkit.h"

int main()
{
    int cost, paid, diff, count2, count1, count50c, count20c, count10c, count5c;
    bool flag;
   

    string choice = "Y";

    /** 
     * while loop that it allow the user to continue to add cost and amount paid to get the change
     * as long as the user want. 
     * stays in loop until choice != "Y"
     */
    while (choice == "Y")
    {
        write("Cost of item (in cents): ");
        cost = stoi(read_line());
        write("Amount paid(in cents): ");
        paid = stoi(read_line());

        diff = paid - cost;
        flag = false;
        if (diff < 0)
        {
            flag= true;
            write_line("Insufficient payment");
        }

        //initialising the counters
        count2 = 0;
        count1 = 0;
        count50c = 0;
        count20c = 0;
        count10c = 0;
        count5c = 0;

        /** brain of the program 
         * calculate the type of coint to be given out
         * says in loop until diff is greater that 5
         */
        while (diff >= 5 && !flag)
        {
           
            if (diff >= 200)//checking for $2
            {
                count2 += 1;
                diff -= 200;
            }

            else if (diff >= 100 && diff < 200) //checking for $1
            {
                count1 += 1;
                diff -= 100;
            }

            else if (diff >= 50 && diff < 100)//checking for 50c
            {
                count50c += 1;
                diff -= 50;
            }

            else if (diff >= 20 && diff < 50)//checking for 20c
            {
                count20c += 1;
                diff -= 20;
            }

            else if (diff >= 10 && diff < 20)//checking for 10c
            {
                count10c += 1;
                diff -= 10;
            }

            else if (diff >= 5 && diff < 10)//checking for 5c
            {
                count5c += 1;
                diff -= 5;
            }
        }

        /**
         * if amount given > cost of items 
         */
        if (!flag)
        {
          write_line(std::to_string(count2) + " x $2, " + std::to_string(count1) + " x $1, " + std::to_string(count50c) + " x 50c, " + std::to_string(count20c) + " x 20c, " + std::to_string(count10c) + " x 10c, " + std::to_string(count5c) + " x 5c");
   
        }
       
        //allow the uses to decide whether to run program again 
        write_line();
        write("Run again? Y/N: ");
        choice = read_line();

        while (choice != "Y" && choice != "N")// Allowing only "Y" and "N" as inputs
        {
            write("Run again? Y/N: ");
            choice = read_line();
            
            
        
        }
    }
}
