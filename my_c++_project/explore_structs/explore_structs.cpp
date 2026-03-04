#include "splashkit.h"

struct target_data
{
    double x;
    double y;
    double radius;
};

struct reaction_game_data
{
    target_data target;
    int hits;
};

/** New target is used to initialise a target. 
 * The passed in parameters allow the caller to adjust the location and size of the target as they desire
 * @param x The x value for the target.
 * @param y The y value for the target.
 * @param radius The target’s radius.
 * @return A target at the indicated location, with the indicated size.
 */
target_data new_target(double x,double y, double radius)
{
    target_data target = {x,y,radius};
    return target;
}


/** Random target will return target data for a target using the current screen size as its bounds. 
 * This will ensure that the target can be drawn and seen entirely on the screen.
 * @return a target at a random location and size.
 */
target_data random_target()
{
   int radius= rnd(1,300);
   return new_target(rnd(radius,800-radius),rnd(radius,600-radius),radius);
}

/**Use new reaction game to initialise a reaction game value. This will start with a random target and 0 hits.
 * A new reaction game, with a random target and no hits.
 */
reaction_game_data new_reaction_game()
{
    reaction_game_data result;
    result.target = random_target();
    result.hits =0;
    return result;
}

/** Draws a filled circle to the screen at the target’s location.
 * @param target  The target to draw (a target_data value).
 */
void draw_target(target_data target)
{
    fill_circle(color_black(), target.x,target.y,target.radius);
}


/** calculate the average time per hit in the reaction game.
 * @param game The reaction game time.
 * @return The average time per hit
 */
int game_average_time(reaction_game_data game)
{
    if (game.hits == 0)
    {
        return current_ticks();
    }
    else 
    {
        return current_ticks() / game.hits;
    }
}

/** Check and return a boolean that indicates if the mouse is over the target.
 * @param target the target we are testing
 * The function return True if the user has clicked, and their mouse is over the target.
 */
bool mouse_over_target(target_data target)
{
    return point_in_circle(mouse_x(),mouse_y(),target.x,target.y,target.radius);
}


/**Draw the game to the screen by clearing the screen, drawing the game’s target, 
 * and then drawing game stats to the top left of the screen.
 * This also refreshes the screen to ensure it is shown to the user.
 * @param game The reaction game data to draw to the screen
 */
void draw_game(reaction_game_data game)
{
    clear_screen(color_white());
    draw_text("Hits: " + std::to_string(game.hits), color_black(),0,0);
    draw_text("Average time: " + std::to_string(game_average_time(game)),color_black(),0,10);
    draw_target(game.target);
    refresh_screen();


}


int main()
{
  open_window("Reaction Timer", 800, 600);

  // Create the game data
  reaction_game_data game = new_reaction_game();

  while (!quit_requested())
  {
    process_events();

    if (mouse_clicked(LEFT_BUTTON) && mouse_over_target(game.target))
    {
      game.target = random_target();
      game.hits++;
    }

    draw_game(game);
  }

  return 0;
}

