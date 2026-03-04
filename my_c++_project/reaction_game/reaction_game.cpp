#include "splashkit.h"
#include <stdio.h>

// game timer
const string GAME_TIMER = "gametimer";

// screen size
const double SCREEN_WIDTH = 1000;
const double SCREEN_HEIGHT = 800;

// target radius
const int INITIAL_RADIUS = 50;

/** structured data type that contain the game details
 *
 * Game details:
 * -target of data type circle
 * -time of data time int that store the best reaction time
 * -score of data type int that store the number of target hit
 */
struct game_data
{
    circle target;
    int time;
    int score = 0;
};

/** Procedure that handle the user input and update the target data when hit
 *
 * @param game of data type game_data that contain data about the game: passed by reference
 */
void handle_input(game_data &game)
{
    do
    {
        process_events();
    } while ((!point_in_circle(mouse_position(), game.target)) && !quit_requested()); // Wait for user to hit target or if the user quits game

    int temp;
    temp = timer_ticks(GAME_TIMER);
    if (temp < game.time) // compare and store reaction if it is faster taht the stored one
    {
        game.time = timer_ticks(GAME_TIMER);
    }
    game.score += 1; // increament  game score
    reset_timer(GAME_TIMER);
    game.target.center = random_screen_point();
    temp = temp / 1000 * 100; // Calculate the radius based on reaction 100ms per second
    if (temp < 5)             // If radius equates to less than 5, set radius to 10
    {
        game.target.radius = 10;
    }
    else
    {
        game.target.radius = temp;
    }
}

/** Procedure that the update version of the screen
 *
 * @param game of data type game_data that contain data about the game: passed as const reference
 */
void update_game(const game_data &game)
{
    clear_screen(color_white());
    fill_circle(color_red(), game.target);
    draw_text("Targets hit: " + std::to_string(game.score), color_black(), 10, 10);
    draw_text("Fastest reaction (ms): " + std::to_string(game.time), color_black(), 10, 40);
    refresh_screen();
}

/** Procedure that draw the screen
 *
 * @param game of data type game_data that contain data about the game: passed as reference
 */
void draw_game(game_data &game)
{

    clear_screen(color_white());
    while (!quit_requested())
    {
        process_events();
        update_game(game);
        handle_input(game);
    }
}

int main()
{
    game_data game;

    create_timer(GAME_TIMER);
    start_timer(GAME_TIMER);
    game.time = 1000000;
    open_window("Raction time", SCREEN_WIDTH, SCREEN_HEIGHT);

    game.target.center = random_screen_point();
    game.target.radius = INITIAL_RADIUS;

    draw_game(game);
}