#include "splashkit.h"

int main()
{

string line;
int percentfull;
double waterHeight, waterY;

const int window_height = 600;
const int window_width = 600;
const int BOTTLE_RADIUS = 80;
const int BOTTLE_HEIGHT = 400;
const int BOTTLe_diameter = 2 * BOTTLE_RADIUS;
const int BOTTLE_CENTER_X = window_width / 2;
const int BOTTLE_LEFT_X = BOTTLE_CENTER_X - BOTTLE_RADIUS;
const int BOTTLE_RIGHT_X = BOTTLE_CENTER_X + BOTTLE_RADIUS;
const int BOTTLE_BASE_Y = window_height - BOTTLE_RADIUS - 5;
const int BOTTLE_TOP_Y = BOTTLE_BASE_Y - BOTTLE_HEIGHT;

//Prompt the user to input the water level as a percentage.
write("Enter the percentage at which the bottle is full: ");
line = read_line();

percentfull = stoi(line); //convert water level from string to interger and storing it.
line = "";

waterHeight = BOTTLE_HEIGHT * percentfull / 100;
waterY = BOTTLE_BASE_Y - waterHeight;

//create screen for water bottle
open_window("Water Bottle Visualiser!", 600, 600);
clear_screen(color_white());

//code to generate the bottle and water at the specified level
fill_circle(color_blue(), BOTTLE_CENTER_X, waterY, BOTTLE_RADIUS);
fill_circle(color_blue(), BOTTLE_CENTER_X, BOTTLE_BASE_Y, BOTTLE_RADIUS);
fill_rectangle(color_blue(), BOTTLE_LEFT_X, waterY, BOTTLe_diameter, waterHeight);
draw_line(color_black(), BOTTLE_LEFT_X, BOTTLE_TOP_Y, BOTTLE_LEFT_X, BOTTLE_BASE_Y);
draw_line(color_black(), BOTTLE_RIGHT_X, BOTTLE_TOP_Y, BOTTLE_RIGHT_X, BOTTLE_BASE_Y);
draw_circle(color_black(), BOTTLE_CENTER_X, BOTTLE_TOP_Y, BOTTLE_RADIUS);



refresh_screen();
delay(50000);
   
}














