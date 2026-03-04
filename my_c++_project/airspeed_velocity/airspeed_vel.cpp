#include "splashkit.h"

int main()
{
 string BirdName, line;
double freq, amp, resultmax, resultmin;
const double STROUHAL_LOW_EFFICIENCY = 0.4;
const double STROUHAL_HIGH_EFFICIENCY = 0.2;

//prompt the user to input the bird name
write("Enter bird name: ");
BirdName = read_line();
write_line();

//prompt the user to enter said bird's frequency
write("Enter " + BirdName + "'s frequency: ");
line = read_line();
write_line();
freq = stod(line);   // converts the user input from string to interger and storing it in freq
line = "";           // re-initialising line to "" to be able to take another user's input

//prompt the user to enter said bird's amplitude
write("Enter " + BirdName + "'s amplitude: ");
line = read_line();
write_line();
amp = stod(line);    // converts the user input from string to interger and storing it in amp
line = "";           // re-initialising line to "" to be able to take another user's input(if program were to be expanded)

resultmax = freq * amp / STROUHAL_HIGH_EFFICIENCY;   //calculating max speed 
resultmin = freq * amp / STROUHAL_LOW_EFFICIENCY;    //calculating min speed 

//ouputing the bird's speeds
write_line(BirdName + "maximum air speed is " + std::to_string(resultmax) + "m/s and its minimum air speed is " + std::to_string(resultmin) + "m/s");
read_line();
   
}


