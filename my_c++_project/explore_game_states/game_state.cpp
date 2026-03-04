#include "splashkit.h"

/** An enumeration of the different screens
 */
enum game_state
{
    PLAYING,
    SHOWING_DETAILS,
    SHOWING_MENU
};

/** composite type game_data
 * state conatin the state of the game which of the enum game_state typr
 * player_pos store the position of the player
 */
struct game_data
{
    game_state state;
    point_2d player_pos;
    bool quit;
};

/** function that returns a variable of type game_data 
 * this function is used at the start the game.
 * @return A variable of type game_data
*/
game_data new_game()
{
    game_data game;
    game.state = PLAYING;
    game.quit = false;
    return game;
}

/**procedure to create the playing screen 
* @param game of type game_data 
*/
void draw_playing(game_data game)
{
    clear_screen(COLOR_WHITE);
    fill_circle(COLOR_RED, game.player_pos.x, game.player_pos.y, 20);
}

/**procedure to create the details screen 
 * @param game of typr game_data
*/
void draw_details(game_data game)
{
    clear_screen(COLOR_LIGHT_BLUE);
    fill_circle(COLOR_ORANGE, game.player_pos.x, game.player_pos.y, 20);
    fill_circle(COLOR_BLACK, game.player_pos.x, game.player_pos.y, 2);

   
    draw_text(point_to_string(game.player_pos), COLOR_BLACK, 20, 20);
}

/**procedure to create the menu screen 
 *@param game of typr game_data
*/
void draw_menu(game_data game)
{
    clear_screen(COLOR_LIGHT_GREEN);
    draw_text("Press SPACE to Play, Q to Quit", COLOR_BLACK, 20, 20);
}

/**procedure to draw screen depending on the current state
 * @param game of type game_data 
 */
void draw_game(game_data game)
{
    switch (game.state)
    {
    case PLAYING:
        draw_playing(game);
        break;
    case SHOWING_DETAILS:
        draw_details(game);
        break;
    case SHOWING_MENU:
        draw_menu(game);
        break;
    }
}


int main()
{
    open_window("Game State Example", 800, 600);

    game_data game = new_game();

    while (not quit_requested() && !game.quit)
    {
        process_events();

       
        switch (game.state)
        {
        case PLAYING:
            if (key_typed(SPACE_KEY))
            {
                game.player_pos = random_screen_point();
            }
            else if (key_typed(NUM_1_KEY))
            {
                game.state = SHOWING_DETAILS;
            }
            else if (key_typed(NUM_2_KEY))
            {
                game.state = SHOWING_MENU;
            }
            break;

        case SHOWING_DETAILS:
            if (key_typed(SPACE_KEY))
            {
                game.state = PLAYING;
            }
            break;

        case SHOWING_MENU:
            if (key_typed(SPACE_KEY))
            {
                game.state = PLAYING;
            }
            else if (key_typed(Q_KEY))
            {
                game.quit = true;
            }
            break;
        }
        
        draw_game(game);
        refresh_screen(60);
    }

    return 0;
}
