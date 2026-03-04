#include "splashkit.h"
const int target_radius = 30; //radius of the target

/**
 * function that return a vaild interger
 * @param prompt conatin an output prompt incase the valuse the user entered the first time is wrong, this prompt will be used to tell the user what to input.
 */
int input_valid_integer(string prompt)
{
    string temp;
    int temp2;
    bool good;
    do
    {
        good = true;
        try
        {
            size_t pos;
            temp = read_line();
            temp2 = stoi(temp, &pos);
            if (pos != temp.length())
            {
                good = false;
            }
        }
        catch (const std::exception &e)
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

/** create a 'health' bar for the target, indicating how many hits is left for game to end.
 * @param target_remaining indicate how much 'health is left of the target, this willbe used to generate the target(health) bar
 * 
 */
void target_bar(double target_remaining)
{

    double position = 600 * target_remaining;
    fill_rectangle(color_lime_green(), 10, 10, position, 80);
    draw_rectangle(color_black(), 10, 10, 600, 80);
}

/** Write on screen how many hit is left and the total number of hit that was needed
 * @param current_health Contain the current health of the target, i.e. how many hit is left.
 * @param max_health Contain the max health of the target, i.e. how many hit was need to kill the target.
 * 
 */
void target_health(int current_health, int max_health)
{
    draw_text(std::to_string(current_health) + "/" + std::to_string(max_health), color_black(), "main", 80, 700, 10);
}

/** contain the code about how to generate the screen 
 * @param target_current_score Contain the current health of the target, i.e. how many hit is left.
 * @param target_max_score Contain the max health of the target, i.e. how many hit was need to kill the target.
 * @param target_x contains the x-coordinates of the position where the target is to be spawn 
 * @param target_y contains the y-coordinates of the position where the target is to be spawn 
 */
void draw_game(int target_max_score, int target_current_score, int target_x, int target_y)
{
    double target_left;

    clear_screen(color_white());

    target_left = (double)target_current_score / target_max_score;
    target_bar(target_left);
    target_health(target_current_score, target_max_score);
    fill_circle(color_red(), target_x, target_y, target_radius);

    refresh_screen(60);
}

/** Check whether the user hit the target
 * @param target_x contains the x-coordinates of the position where the target is to be spawn 
 * @param target_y contains the y-coordinates of the position where the target is to be spawn 
 */
bool target_hit(int target_x, int target_y)
{
    float mouse_x_pos, mouse_y_pos;
    process_events();
    if (mouse_clicked(LEFT_BUTTON))
    {
        mouse_x_pos = mouse_x();
        mouse_y_pos = mouse_y();
        return point_in_circle(mouse_x_pos, mouse_y_pos, target_x, target_y, target_radius);
    }

    return false;
}

/** contains the logic on how to run the game
 * @param target_score contain the amount of time the user needs to hit the target
 */
void play_game(int target_score)
{
    int target_x, target_y;
    int target_max_score = target_score;
    target_x = rnd(1000);
    target_y = 100 + rnd(700);

    while (target_score > 0)
    {
        process_events();

        draw_game(target_max_score, target_score, target_x, target_y);

        if (target_hit(target_x, target_y))
        {
            target_score -= 1;
            target_x = target_radius + rnd(1000 - 2 * target_radius);
            target_y = 100 + target_radius + rnd(700 - 2 * target_radius);
        }
    }
}

int main()
{
    int target_score;
    load_font("main", "Roboto-Light.ttf");

    write_line("Welcom to Target click");
    write_line("");

    write("What is the target score: ");
    target_score = input_valid_integer("What is the target score: ");

    write_line("");
    write_line("Click " + std::to_string(target_score) + " target to end game.");

    open_window("The Click Game", 1000, 800);
    play_game(target_score);
}