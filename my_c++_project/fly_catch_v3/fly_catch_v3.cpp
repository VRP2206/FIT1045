#include "splashkit.h"

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
struct spider_data
{
    double x;
    double y;
};

/**
 * The spider has a location on the screen.
 *
 * @field x the distance from the left side of the window
 * @field y the distance from the top of the window
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

/**
 * Draw the fly if it has appeared
 *
 * @field fly the fly data
*/
void draw_fly(fly_data fly)
{
    if (fly.appeared)
    {
        fill_circle(color_dark_green(), fly.x, fly.y, FLY_RADIUS);
    }
}


/**
 * Draw the spider and the fly to the screen.
 *
 * @param game the game data
*/
void draw_game(game_data game, int countwin, int countgame)
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
    fly.y = 100 + rnd(GAME_SCREEN_HEIGHT);

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

    bool flag = false;

    game.spider = new_spider();
    game.fly = new_fly();

    load_font("main", "Roboto-Light.ttf");                      // Load front for text on screen
    open_window("Fly Catch", GAME_SCREEN_WIDTH, SCREEN_HEIGHT); // create the screen

    create_timer(GAME_TIMER); // create a timer for the game to based off of.
    start_timer(GAME_TIMER);

    while (!quit_requested())
    {
        // Spider movement code
        if ((key_down(RIGHT_KEY)) && (game.spider.x + SPIDER_RADIUS < GAME_SCREEN_WIDTH)) // spider move right
        {
            game.spider.x += SPIDER_SPEED;
        }
        if ((key_down(LEFT_KEY)) && (game.spider.x - SPIDER_RADIUS > 0)) // spider move left
        {
            game.spider.x -= SPIDER_SPEED;
        }

        if ((key_down(DOWN_KEY)) && (game.spider.y + SPIDER_RADIUS < SCREEN_HEIGHT)) // spider move down
        {
            game.spider.y += SPIDER_SPEED;
        }
        if ((key_down(UP_KEY)) && (game.spider.y - SPIDER_RADIUS > 100)) // spider move up
        {
            game.spider.y -= SPIDER_SPEED;
        }
        // spider movenent code end

        if (!game.fly.appeared && timer_ticks(GAME_TIMER) > game.fly.appear_at_time) // generate fly
        {
            game.fly.appeared = true;

            game.fly.x = rnd(GAME_SCREEN_WIDTH);
            game.fly.y = 100 + rnd(GAME_SCREEN_HEIGHT);
            countgame += 1;

            game.fly.escape_at_time = timer_ticks(GAME_TIMER) + 2000 + rnd(5000);
        }
        else if (game.fly.appeared && timer_ticks(GAME_TIMER) > game.fly.escape_at_time)
        {
            game.fly.appeared = false;
            game.fly.appear_at_time = timer_ticks(GAME_TIMER) + 1000 + rnd(2000);
        }

        flag = game.fly.appeared;
        if (circles_intersect(game.spider.x, game.spider.y, SPIDER_RADIUS, game.fly.x, game.fly.y, FLY_RADIUS)) // check if spider ate fly
        {
            game.fly.appeared = false;
            game.fly.appear_at_time = timer_ticks(GAME_TIMER) + 1000 + rnd(2000);
        }
        if (flag && !game.fly.appeared) // counts the number of rounds/games played
        {
            countwin += 1;
        }

        draw_game(game, countwin, countgame);

        process_events();
    }
}