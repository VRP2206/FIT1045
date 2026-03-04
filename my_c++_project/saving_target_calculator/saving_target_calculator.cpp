#include "splashkit.h"
using std::stoi;
using std::to_string;


int main()
{

string name, temp;
double how_much_to_save, time_before_purchace, money_have, save_per_week, temp1,temp2;

//prompt the user to input the name of the reason to save
write("What are you saving for? Enter title: ");
name = read_line();
write_line();

//prompt the user to input the anmount to save
write("How much do you need to save? Enter dollars: ");
temp = read_line();
how_much_to_save = stoi(temp);
temp = "";
write_line();

//prompt the user to input how many week left to use that money
write("How long before the purchase? Enter weeks: ");
temp = read_line();
time_before_purchace = stoi(temp);
temp = "";
write_line();

//prompt the user to input have much they already have
write("How much do you have already? Enter dollars: ");
temp = read_line();
money_have = stoi(temp);
temp = "";
write_line();

//prompt the user to input how they can save per week
write("How much can you save each week? Enter dollars: ");
temp = read_line();
save_per_week = stoi(temp);
temp = "";
write_line();

temp1= (how_much_to_save - money_have) / time_before_purchace;
temp2= (how_much_to_save - money_have) / save_per_week;

write_line("For the Holiday, you need to save " + to_string(temp1) + " dollars a week");
write_line("Based on current savings you will need " + to_string(temp2) + " weeks to save " + to_string(how_much_to_save));

}
