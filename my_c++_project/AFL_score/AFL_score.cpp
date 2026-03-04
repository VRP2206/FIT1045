#include "splashkit.h"

/**
 * Claculate the score base of number of goals and behinds
 * @param goals pass the number of goals for a team
 * @param behinds pass the number of behind for a team
 */
int scoring(int goals, int behinds)
{
    return goals * 6 + behinds;
}

/**
 * compares the score between the two team and return who is winning or wether they are in a draw
 * @param team_1 conatin the name for the first team, this data is returned if team 1 is winnning
 * @param score_1 contains the score for team 1 
 * @param team_2 conatin the name for the first team, this data is returned if team 2 is winnning
 * @param score_2 contains the score for team 2 
 */
string winner(string team_1, int score_1, string team_2, int score_2)
{
    if (score_1> score_2)
    {
        return "The "+ team_1 + " winning";
    }
    else if (score_1< score_2)
    {
        return "The "+ team_2 + " winning";
    }
    else
    return "It is currently a draw";

}

/**
 * calls function winning and output the returened value
 * it also outputs each team deatil(goals,behinds, score)
 * @param team_1 contains name for team 1
 * @param goal_1 contains the number of goals for team 1
 * @param behind_1 contains the numeber of goals for team 1
 * @param team_2 contains name for team 2
 * @param goal_2 contains the number of goals for team 2
 * @param behind_2 contains the numeber of goals for team 2
 */
void calculating_detail(string team_1,int goal_1,int behind_1,string team_2, int goal_2,int behind_2)
{
    write_line("");
    write_line("Calculating details...");
    write_line(winner(team_1,scoring(goal_1,behind_1),team_2,scoring(goal_2,behind_2)));
    write_line("");
    write_line(team_1 +", "+ std::to_string(goal_1) +", " + std::to_string(behind_1) + ", " + std::to_string(scoring(goal_1,behind_1)));
    write_line(team_2 +", "+ std::to_string(goal_2) +", " + std::to_string(behind_2) + ", " + std::to_string(scoring(goal_2,behind_2)));
        
}


/**
 * function that return a vaild interger
 * @param prompt conatin an output prompt incase the valuse the user entered the first time is wrong, this prompt will be used to tell the user what to input.
 */
int input_valid_integer(string prompt)
{
    string temp;
    int temp2;
    bool good;
    size_t pos;

    do
    {
    good = true;
    try
    {
        temp = read_line();
        temp2= stoi(temp, &pos);
        if (pos != temp.length())
        {
            good=false;

        }
    
    }
    catch(const std::exception& e)
    {
        good = false;
    }
    if (!good)
    {
        write_line("Please enter a whole number");
        write(prompt);
    }
    } while (!good);
    return temp2;
}


/**
 * let user update data depending on that is is call from in menu.
 * it can update goals and behinds.
 * @param prompt ouput proompt to let user know that to input
 * @param data this is passed as reference, meaning any change to the value will also occur to the varible passed to the function.
 */
void update_data(string prompt,int &data)
{
    write(prompt);
    data = input_valid_integer(prompt);
}

/**
 * menu to give the user option of what to do:
 * they can update each team detail and print the details
 * @param team_1 contains name for team 1
 * @param goal_1 contains the number of goals for team 1
 * @param behind_1 contains the numeber of goals for team 1
 * @param team_2 contains name for team 2
 * @param goal_2 contains the number of goals for team 2
 * @param behind_2 contains the numeber of goals for team 2
 */
void menu(string team_1, int goal_1, int behind_1, string team_2, int goal_2, int behind_2)
{
    string choice;
    int option;
    bool flag = true;
    
    do
    {
        write_line("");
        write_line("Menu:");
        write_line("1: Update " + team_1 + " goals");
        write_line("2: Update " + team_1 + " behind");
        write_line("3: Update " + team_2 + " goals");
        write_line("4: Update "+ team_2 +" behindS");
        write_line("5: Print details");
        write_line("6: Quit");

        write("Option: ");
        option = input_valid_integer("option: ");
        
        while (option<1 || option>6)
        {
            write_line("Please enter a whole number beteen 1 to 6");
            write("Option: ");
            option = input_valid_integer("option: ");
        }

        switch(option)
        {
        case 1: //update goals for team 1
            update_data("Updated goal: ", goal_1);
            break;

        case 2: //upadte behinds for team 1
           update_data("Updated behind: ", behind_1);
           break;

        case 3: //update goals for team 2
            update_data("Updated goal: ", goal_2);
            break;

        case 4: //update behinds for team 2
            update_data("Updated behind: ", behind_2);
            break;

        case 5: //calculate details and output it all done by procedure calculating_details
            calculating_detail(team_1,goal_1,behind_1,team_2,goal_2,behind_2);
            break;

        case 6: //quit the program 
            write("Are you sure you want to quit? [y/n]: ");
            choice= read_line();

            while(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
            {
                write_line("Please enter y or n");
                write("Are you sure you want to quit? [y/n]: ");
                choice= read_line();
            }
            if (choice == "y" || choice == "Y")
            {
                flag= false;
            }
            break;
        }
    } while (flag); 
   
}

int main()
{
    string name_1,name_2;
    int goal_1,goal_2, behind_1, behind_2;

    write_line("Welcome to AFL score calculator!");

    write_line("Enter team 1 details");
    write("name: ");
    name_1 = read_line();

    write("goals: ");
    goal_1 = input_valid_integer("goals: ");

    write("behinds: ");
    behind_1= input_valid_integer("behinds: ");

    write_line("");
    write_line("Enter team 2 details");
    write("name: ");
    name_2 = read_line();

    write("goals: ");
    goal_2 = input_valid_integer("goals: ");

    write("behinds: ");
    behind_2= input_valid_integer("behinds: ");
   
   
    calculating_detail(name_1,goal_1,behind_1,name_2,goal_2,behind_2);
        
    menu(name_1,goal_1,behind_1,name_2,goal_2,behind_2);
    write_line("");
    write_line("Bye");
}