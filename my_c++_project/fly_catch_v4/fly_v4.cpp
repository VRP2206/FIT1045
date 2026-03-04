#include "splashkit.h"

/**
 * The spider has a location on the screen.
 *
 * @field x the distance from the left side of the window
 * @field y the distance from the top of the window
*/
struct spider_data
{
    double x;
    double y;
};

/**
 * The fly can appear and escape (disappear), but is otherwise
 * located on the screen at a certain point.
 *
 * @field appeared  indicates if the fly is shown
 * @field x its distance from the left of the window (to the center)
 * @field y its distance from the top of the window (to the center)
 * @field appear_at_time  the time when the fly will appear
 * @field escape_at_time  the time when the fly will escape
*/
struct fly_data
{
    bool appeared;
    double x;
    double y;
    int appear_at_time;
    int escape_at_time;
};

/**
 * The game involves a spider and a fly. The player is
 * controlling the spider and the fly is trying to escape.
 *
 * @field spider  the data about the spider
 * @field fly     the data for the fly
*/
struct game_data
{
    spider_data spider;
    fly_data fly;
};


const string GAME_TIMER = "GameTimer";
const int GAME_SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GAME_SCREEN_HEIGHT = SCREEN_HEIGHT - 100;
const int SPIDER_RADIUS = 25;
const int SPIDER_SPEED = 3;
const int FLY_RADIUS = 10;

/**
 * Draw the spider on the screen
 *
 * @param spider  the spider's data
*/
void draw_spider(spider_data spider)
{
    fill_circle(color_black(), spider.x, spider.y, SPIDER_RADIUS);
}

/** procedure to handle inputs from the user
 * 
 * @param spider of data type spider_data
 */
void handle_input(spider_data &spider)
{
// Spider movement code
    if ((key_down(RIGHT_KEY)) && (spider.x + SPIDER_RADIUS < GAME_SCREEN_WIDTH)) // spider move right
    {
        spider.x += SPIDER_SPEED;
    }
    if ((key_down(LEFT_KEY)) && (spider.x - SPIDER_RADIUS > 0)) // spider move left
    {
        spider.x -= SPIDER_SPEED;
    }

    if ((key_down(DOWN_KEY)) && (spider.y + SPIDER_RADIUS < SCREEN_HEIGHT)) // spider move down
    {
        spider.y += SPIDER_SPEED;
    }
    if ((key_down(UP_KEY)) && (spider.y - SPIDER_RADIUS > 100)) // spider move up
    {
        spider.y -= SPIDER_SPEED;
    }
    // spider movenent code end
}

/** function to determine if the fly has to appeared
 * 
 * @param fly of data type fly_data passed by constant reference; contains fly details
 * @param current_time of data type long pass by constant reference; conatins current time of the program
 * 
 * @return bool value for if the fly has appeared.
 */
bool time_to_appear(const fly_data &fly,const long &current_time)
{
  return !fly.appeared && current_time > fly.appear_at_time;
}

/** function to determine if the fly has to escape
 * 
 * @param fly of data type fly_data passed by constant reference; contains fly details
 * @param current_time of data type long pass by constant reference; conatins current time of the program
 * 
 * @return bool value for if the fly has appeared.
 */
bool time_to_escape(const fly_data &fly, long current_time)
{
  return fly.appeared && current_time > fly.escape_at_time;
}


/** procedure to update fly details
 * 
 * @param fly of data type fly_data; store data about the fly
 * @param current_time of data type long pass by constant reference; conatins current time of the program
 * @param countgame of data type int passed by reference; counts the number of games
 * 
 */

void update_fly(fly_data &fly, long current_time,int &countgame)
{
  // Check if the fly should appear
  if (time_to_appear(fly, current_time))
  {
    // Make the fly appear
    fly.appeared = true;

    // Give it a new random position
    fly.x = rnd(GAME_SCREEN_WIDTH);
    fly.y = 100+ rnd(GAME_SCREEN_HEIGHT);

    // Set its escape time
    fly.escape_at_time = current_time + 2000 + rnd(5000);
    countgame += 1;
    
  }
  else if (time_to_escape(fly, current_time))
  {
    fly.appeared = false;
    fly.appear_at_time = current_time + 1000 + rnd(2000);
  }
}


/**
 * Draw the fly if it has appeared
 *
 * @param fly the fly data
*/
void draw_fly(fly_data fly)
{
    if (fly.appeared)
    {
        
        fill_circle(color_dark_green(), fly.x, fly.y, FLY_RADIUS);
    }
}

/** function to check if the fly has been caught
 * 
 * @param spider of data type spider_data passed by constant reference
 * @param fly of data type fly_data passed by constant reference
 * 
 * @return a boolean value for if the fly has been caught of not
 */
bool spider_caught_fly(const spider_data &spider, const fly_data &fly)
{
    
  return fly.appeared && circles_intersect(
    spider.x, spider.y, SPIDER_RADIUS,
    fly.x, fly.y, FLY_RADIUS);
}


/** Upadte the game screen 
 * 
 * @param game of data type game_data passed by reference; conatin the game data 
 * @param current_time of data type long passed by reference; contain the current game time
 * @param countwin of data type int passed by reference; counts the numeber od game won
 * @param countgame of data type int passed by reference; counts the number of games
 * 
 * @return a boolean value for if the fly has been caught of not
 */
void update_game(game_data &game, long current_time, int &countwin,int &countgame)
{
  update_fly(game.fly, current_time,countgame);

  if ( spider_caught_fly(game.spider, game.fly))
  {
    countwin += 1;
    game.fly.appeared = false;
    game.fly.appear_at_time = current_time + 1000 + rnd(2000);
  }
}


/**
 * Draw the spider and the fly to the screen.
 *
 * @param game the game data
 * @param countwin of data type int passed by reference; counts the numeber od game won
 * @param countgame of data type int passed by reference; counts the number of games
*/
void draw_game(game_data game, int countwin, int &countgame)
{
    clear_screen(color_white());
    draw_spider(game.spider);
    // generate the game counter on screen
    draw_text("You won " + std::to_string(countwin) + " out of " + std::to_string(countgame) + " games!", color_black(), "main", 60, 10, 10);

    draw_fly(game.fly);
    refresh_screen(60);
}

/**
 * Initialise a new spider and return it to the caller.
 * The spider will be in the center of the screen.
 *
 * @return an initialised spider
*/
spider_data new_spider()
{
    spider_data spider;

    spider.x = GAME_SCREEN_WIDTH / 2;
    spider.y = GAME_SCREEN_HEIGHT / 2;
    return spider;
}

/**
 * Initialise and return new fly data. This will not have appeared,
 * but will be at a random position, and will appear within 1
 * to 3 seconds.
 *
 * @return the newly initialised fly
*/
fly_data new_fly()
{
    fly_data fly;

    fly.x = rnd(GAME_SCREEN_WIDTH);
    fly.y = rnd(GAME_SCREEN_HEIGHT);

    fly.appeared = false;
    fly.appear_at_time = 1000 + rnd(2000);
    fly.escape_at_time = 0;

    return fly;
}



int main()
{
    int countgame = 0;
    int countwin = 0;
    game_data game;

    game.spider = new_spider();
    game.fly = new_fly();

    load_font("main", "Roboto-Light.ttf");                      // Load front for text on screen
    open_window("Fly Catch", GAME_SCREEN_WIDTH, SCREEN_HEIGHT); // create the screen

    create_timer(GAME_TIMER); // create a timer for the game to based off of.
    start_timer(GAME_TIMER);

    while (!quit_requested())
    {
        handle_input(game.spider);
        update_game(game, timer_ticks(GAME_TIMER),countwin,countgame);

        draw_game(game, countwin, countgame);

        process_events();
    }
}
