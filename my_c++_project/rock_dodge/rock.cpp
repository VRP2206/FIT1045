#include "splashkit.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAX_ROCKS = 100;
const int PLAYER_RADIUS = 20;
const int PLAYER_SPEED = 3;


/**
 * The rock_data structure stores the information for a single falling rock.
 *
 * @field pos - of type point_2d; stores the (x, y) position of the rock.
 * @field size - of type double; the diameter of the rock.
 * @field speed - of type double; the vertical speed at which the rock falls.
 * @field active - of type bool; true if the rock is currently active on screen, false otherwise.
 */
struct rock_data
{
    point_2d pos;   
    double size;
    double speed;
    bool active;
};


/**
 * The game_data structure stores all the information needed
 * to manage and update the game state.
 *
 * @field rocks - an array of rock_data with size MAX_ROCKS; holds all rocks in the game.
 * @field rock_count - of type int; stores the total number of rocks created so far.
 * @field player_pos - of type point_2d; stores the (x, y) position of the player.
 * @field score - of type int; tracks the current player score.
 * @field lives - of type int; tracks how many lives the player has remaining.
 * @field next_rock_time - of type unsigned int; the system time when the next rock should spawn.
 */
struct game_data
{
    rock_data rocks[MAX_ROCKS];
    int rock_count = 0;

    point_2d player_pos;   
    int score = 0;
    int lives = 3;
    unsigned int next_rock_time = 0;
};

/** Creates and returns a new rock with random size, position, and speed.
 *
 * @return a rock_data object with initialized size, position, speed, and active flag set to true.
 */
rock_data new_rock()
{
    rock_data r;
    r.size = rnd(20, 200);
    r.pos.x = rnd(SCREEN_WIDTH - r.size);
    r.pos.y = -r.size; 
    r.speed = rnd(1, 5);
    r.active = true;
    return r;
}

/** Adds a new rock to the game if there is space available.
 * Also updates the time when the next rock will spawn.
 *
 * @param game passed by reference; the current game state where the rock will be added.
 */
void add_rock(game_data &game)
{
    if (game.rock_count < MAX_ROCKS)
    {
        game.rocks[game.rock_count] = new_rock();
        game.rock_count++;
        game.score++; 
    }
    game.next_rock_time = current_ticks() + rnd(1000, 6000);
}

/**
 * Handles player input and updates the player’s position.
 * Supports 'A' or LEFT arrow to move left, and 'D' or RIGHT arrow to move right.
 * Ensures the player remains within the screen boundaries.
 *
 * @param game passed by reference; the current game state containing player position.
 */
void handle_input(game_data &game)
{
    if (key_down(LEFT_KEY) || key_down(A_KEY))
    {
        game.player_pos.x -= PLAYER_SPEED;
        if (game.player_pos.x < PLAYER_RADIUS) game.player_pos.x = PLAYER_RADIUS;
    }
    if (key_down(RIGHT_KEY) || key_down(D_KEY))
    {
        game.player_pos.x += PLAYER_SPEED;
        if (game.player_pos.x > SCREEN_WIDTH - PLAYER_RADIUS)
            game.player_pos.x = SCREEN_WIDTH - PLAYER_RADIUS;
    }
}

/**
 * Checks whether a given rock collides with the player.
 *
 * @param r passed by const reference; the rock being checked.
 * @param game passed by const reference; the current game state with player position.
 *
 * @return true if the rock intersects with the player circle, false otherwise.
 */
bool check_collision(const rock_data &r, const game_data &game)
{
    circle rock_circle = circle_at(r.pos.x + r.size / 2, r.pos.y + r.size / 2, r.size / 2);
    circle player_circle = circle_at(game.player_pos.x, game.player_pos.y, PLAYER_RADIUS);

    return circles_intersect(rock_circle, player_circle);
}

/**
 * Updates the game state:
 *  - Spawns new rocks at the scheduled time.
 *  - Moves active rocks downward.
 *  - Increases score if a rock falls off the screen.
 *  - Decreases player lives if a rock collides with the player.
 *
 * @param game passed by reference; the current game state to be updated.
 */
void update_game(game_data &game)
{
    if (current_ticks() > game.next_rock_time)
    {
        add_rock(game);
    }
   
    for (int i = 0; i < game.rock_count; i++)
    {
        if (!game.rocks[i].active) continue;

        game.rocks[i].pos.y += game.rocks[i].speed;
        
        if (game.rocks[i].pos.y > SCREEN_HEIGHT)
        {
            game.score += (int)game.rocks[i].size;
            game.rocks[i].active = false;
        }
       
        else if (check_collision(game.rocks[i], game))
        {
            game.lives--;
            game.rocks[i].active = false;
        }
    }
}

/**
 * Draws the current state of the game to the screen:
 *  - Clears the screen.
 *  - Displays score and remaining lives.
 *  - Draws the player as a blue circle.
 *  - Draws all active rocks as gray circles.
 *
 * @param game passed by const reference; the current game state to be drawn.
 */
void draw_game(const game_data &game)
{
    clear_screen(COLOR_WHITE);

    draw_text("Score: " + std::to_string(game.score), COLOR_BLACK, 10, 10);
    draw_text("Lives: " + std::to_string(game.lives), COLOR_BLACK, 10, 40);

    
    fill_circle(COLOR_BLUE, game.player_pos.x, game.player_pos.y, PLAYER_RADIUS);

    
    for (int i = 0; i < game.rock_count; i++)
    {
        if (game.rocks[i].active)
            fill_circle(COLOR_GRAY, game.rocks[i].pos.x, game.rocks[i].pos.y, game.rocks[i].size / 2);
    }

    refresh_screen(60);
}

/**
 * The entry point of the program.
 * Initializes the game state, opens the window, and runs the main game loop:
 *  - Processes player input.
 *  - Updates game logic.
 *  - Draws the game.
 * The loop continues until the player runs out of lives or the program is quit.
 *
 * @return 0 when the program ends successfully.
 */
int main()
{
    open_window("Rock Dodge Game", SCREEN_WIDTH, SCREEN_HEIGHT);

    game_data game;
    game.player_pos = point_at(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);
    game.next_rock_time = current_ticks() + rnd(1000, 6000);

    while (!quit_requested() && game.lives > 0)
    {
        process_events();
        handle_input(game);
        update_game(game);
        draw_game(game);
    }

    close_window("Rock Dodge Game");
    return 0;
}
