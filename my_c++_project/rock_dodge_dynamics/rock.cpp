#include "splashkit.h"
#include "d_arr_v2.hpp"
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int PLAYER_RADIUS = 20;
const int PLAYER_SPEED = 3;

/**
 * The rock_data structure stores the information for a single falling rock.
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
 */
struct game_data
{
    dynamic_array<rock_data> rocks;
    point_2d player_pos;
    int score = 0;
    int lives = 3;
    unsigned int next_rock_time = 0;

    game_data() : rocks(10, rock_data()) {} // start with capacity 10
};

/**
 * @brief Creates and returns a new rock with random size, position, and speed.
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

/**
 * @brief Adds a new rock to the game.
 *
 * Increments the score and sets the timer for the next rock spawn.
 *
 * @param game The game state to update
 */
void add_rock(game_data &game)
{
    game.rocks.add(new_rock());
    game.score++;
    game.next_rock_time = current_ticks() + rnd(1000, 6000);
}

/**
 * @brief Handles keyboard input for moving the player.
 *
 * Left/right arrow keys or A/D keys move the player horizontally.
 *
 * @param game The game state to update
 */
void handle_input(game_data &game)
{
    if (key_down(LEFT_KEY) || key_down(A_KEY))
    {
        game.player_pos.x -= PLAYER_SPEED;
        if (game.player_pos.x < PLAYER_RADIUS)
            game.player_pos.x = PLAYER_RADIUS;
    }
    if (key_down(RIGHT_KEY) || key_down(D_KEY))
    {
        game.player_pos.x += PLAYER_SPEED;
        if (game.player_pos.x > SCREEN_WIDTH - PLAYER_RADIUS)
            game.player_pos.x = SCREEN_WIDTH - PLAYER_RADIUS;
    }
}

/**
 * @brief Checks collision between a rock and the player.
 *
 * Uses circle-to-circle intersection.
 *
 * @param r The rock to check
 * @param game The current game state (player position)
 * @return true if the rock collides with the player, false otherwise
 */
bool check_collision(const rock_data &r, const game_data &game)
{
    circle rock_circle = circle_at(r.pos.x + r.size / 2, r.pos.y + r.size / 2, r.size / 2);
    circle player_circle = circle_at(game.player_pos.x, game.player_pos.y, PLAYER_RADIUS);
    return circles_intersect(rock_circle, player_circle);
}

/**
 * @brief Updates the game state.
 *
 * Spawns rocks at random intervals, moves rocks downward,
 * checks collisions, and adjusts score/lives accordingly.
 *
 * @param game The game state to update
 */
void update_game(game_data &game)
{
    if (current_ticks() > game.next_rock_time)
    {
        add_rock(game);
    }

    for (unsigned int i = 0; i < game.rocks.size; i++)
    {
        rock_data &r = game.rocks[i];
        if (!r.active) continue;

        r.pos.y += r.speed;

        if (r.pos.y > SCREEN_HEIGHT)
        {
            game.score += (int)r.size;
            r.active = false;
        }
        else if (check_collision(r, game))
        {
            game.lives--;
            r.active = false;
        }
    }
}


/**
 * @brief Draws the game state.
 *
 * Clears the screen, draws the score and lives,
 * renders the player, and all active rocks.
 *
 * @param game The game state to render
 */
void draw_game(const game_data &game)
{
    clear_screen(COLOR_WHITE);

    draw_text("Score: " + std::to_string(game.score), COLOR_BLACK, 10, 10);
    draw_text("Lives: " + std::to_string(game.lives), COLOR_BLACK, 10, 40);

    fill_circle(COLOR_BLUE, game.player_pos.x, game.player_pos.y, PLAYER_RADIUS);

    for (unsigned int i = 0; i < game.rocks.size; i++)
    {
        const rock_data &r = game.rocks[i];
        if (r.active)
            fill_circle(COLOR_GRAY, r.pos.x, r.pos.y, r.size / 2);
    }

    refresh_screen(60);
}


/**
 * @brief Program entry point.
 *
 * Initializes the game, runs the game loop until
 * player loses all lives or quits.
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
