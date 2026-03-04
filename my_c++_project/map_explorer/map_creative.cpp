#include "splashkit.h"

using std::to_string;

const int MAX_MAP_ROWS = 20;
const int MAX_MAP_COLS = 20;

const int TILE_WIDTH = 60;
const int TILE_HEIGHT = 60;

const int MAP_WIDTH  = MAX_MAP_COLS * TILE_WIDTH;
const int MAP_HEIGHT = MAX_MAP_ROWS * TILE_HEIGHT;

enum explorer_state_kind
{
  PLAY_STATE,
  EDIT_STATE
};

/**
 * Tile types
 */
enum tile_kind
{
  WATER_TILE,
  GRASS_TILE,
  DIRT_TILE,
  SAND_TILE
};

/** struct representing a single tile
 *
 * @field kind - the type of tile (water, grass, dirt, or sand)
 * 
 */
struct tile_data
{
  tile_kind kind;
};

/** struct representing a map
 *
 * @field tiles - a 2D grid of tiles (up to MAX_MAP_COLS x MAX_MAP_ROWS)
 * 
 */
struct map_data
{
  tile_data tiles[MAX_MAP_COLS][MAX_MAP_ROWS];
};

/** struct representing the player
 *
 * @field position - the player's world position
 * @field speed - the player's movement speed
 */
struct player_data
{
  point_2d position;  // world position
  double speed;
};

/** struct representing the explorer game state
 *
 * @field map - the current map
 * @field camera_position - the position of the camera (top-left corner)
 * @field state - current state (play or edit)
 * @field editor_tile_kind - currently selected tile type in edit mode
 * @field player - the player data
 */
struct explorer_data
{
  map_data map;
  point_2d camera_position;
  explorer_state_kind state;
  tile_kind editor_tile_kind;
  player_data player;
};

/** Initialise the map with all grass tiles.
 *
 * @param map passed by reference; will be filled with grass tiles
 */
void init_map(map_data &map)
{
  for(int c = 0; c < MAX_MAP_COLS; c++)
  {
    for(int r = 0; r < MAX_MAP_ROWS; r++)
    {
      map.tiles[c][r].kind = GRASS_TILE;
    }
  }
}

/** Fill the map with random tile types.
 *
 * @param map passed by reference; will be filled with random terrain
 */
void random_map(map_data &map)
{
  for(int c = 0; c < MAX_MAP_COLS; c++)
  {
    for(int r = 0; r < MAX_MAP_ROWS; r++)
    {
      map.tiles[c][r].kind = (tile_kind)(rnd(4));
    }
  }
}

/** Add a village preset (3x3 dirt with sand border).
 *
 * @param map passed by reference; will be updated with a village area
 */
void add_village(map_data &map)
{
  int start_col = rnd(MAX_MAP_COLS - 4);
  int start_row = rnd(MAX_MAP_ROWS - 4);

  for(int c = start_col; c < start_col + 3; c++)
  {
    for(int r = start_row; r < start_row + 3; r++)
    {
      map.tiles[c][r].kind = DIRT_TILE;
    }
  }

  for(int c = start_col - 1; c < start_col + 4; c++)
  {
    if(c < 0 || c >= MAX_MAP_COLS) continue;
    for(int r = start_row - 1; r < start_row + 4; r++)
    {
      if(r < 0 || r >= MAX_MAP_ROWS) continue;
      if(map.tiles[c][r].kind != DIRT_TILE)
        map.tiles[c][r].kind = SAND_TILE;
    }
  }
}

/** Add grass terrain with a vertical river.
 *
 * @param map passed by reference; will be updated with river tiles
 */
void add_grass_with_river(map_data &map)
{
  init_map(map);

  int river_col = rnd(MAX_MAP_COLS);
  for(int r = 0; r < MAX_MAP_ROWS; r++)
  {
    if(river_col >= 0 && river_col < MAX_MAP_COLS)
      map.tiles[river_col][r].kind = WATER_TILE;
  }
}

/** Add forest patches (random dirt spots).
 *
 * @param map passed by reference; will be updated with forest tiles
 */
void add_forest(map_data &map)
{
  init_map(map);

  for(int i = 0; i < 30; i++)
  {
    int c = rnd(MAX_MAP_COLS);
    int r = rnd(MAX_MAP_ROWS);
    map.tiles[c][r].kind = DIRT_TILE;
  }
}

/** Add a mountain preset (dirt interior, sand border).
 *
 * @param map passed by reference; will be updated with mountain terrain
 */
void add_mountain(map_data &map)
{
  for(int c = 0; c < MAX_MAP_COLS; c++)
  {
    for(int r = 0; r < MAX_MAP_ROWS; r++)
    {
      if(c == 0 || r == 0 || c == MAX_MAP_COLS-1 || r == MAX_MAP_ROWS-1)
        map.tiles[c][r].kind = SAND_TILE;
      else
        map.tiles[c][r].kind = DIRT_TILE;
    }
  }
}

/** Initialise the explorer state and player.
 *
 * @param data passed by reference; will be initialised
 */
void init_explorer_data(explorer_data &data)
{
  data.camera_position = point_at(0, 0);
  data.state = PLAY_STATE;
  data.editor_tile_kind = GRASS_TILE;

  init_map(data.map);

  // Player start in middle of map
  data.player.position = point_at(MAP_WIDTH / 2, MAP_HEIGHT / 2);
  data.player.speed = 1;
}

/** Get the display color for a tile type.
 *
 * @param kind the tile type
 * @return the color associated with the tile type
 */
color color_for_tile_kind(tile_kind kind)
{
  switch(kind)
  {
    case WATER_TILE: return color_blue();
    case GRASS_TILE: return color_lawn_green();
    case SAND_TILE: return color_blanched_almond();
    case DIRT_TILE: return color_rosy_brown();
    default: return  color_white();
  }
}

/** Draw a single tile on the screen.
 *
 * @param tile the tile to draw
 * @param x screen x-coordinate
 * @param y screen y-coordinate
 */
void draw_tile(const tile_data &tile, double x, double y)
{
  color tile_color = color_for_tile_kind(tile.kind);
  fill_rectangle(tile_color, x, y, TILE_WIDTH, TILE_HEIGHT);
  draw_rectangle(color_black(), x, y, TILE_WIDTH, TILE_HEIGHT);
}

/**
 * Draw the visible portion of the map.
 *
 * @param map the map to draw
 * @param camera the camera’s top-left position
 */
void draw_map(const map_data &map, const point_2d &camera)
{
  int start_col = camera.x / TILE_WIDTH;
  int start_row = camera.y / TILE_HEIGHT;

  int end_col = (camera.x + screen_width()) / TILE_WIDTH + 1;
  int end_row = (camera.y + screen_height()) / TILE_HEIGHT + 1;

  if (start_col < 0) start_col = 0;
  if (start_row < 0) start_row = 0;

  for(int c = start_col; c < end_col && c < MAX_MAP_COLS; c++)
  {
    for(int r = start_row; r < end_row && r < MAX_MAP_ROWS; r++)
    {
      draw_tile(map.tiles[c][r], c * TILE_WIDTH, r * TILE_HEIGHT);
    }
  }
}

/** Draw the player.
 *
 * @param player - the player to draw
 */

void draw_player(const player_data &player)
{
  fill_circle(color_red(), player.position.x, player.position.y, 15);
  draw_circle(color_black(), player.position.x, player.position.y, 15);
}

/** Draw the explorer scene (map, player, UI).
 *
 * @param data - the explorer state
 */
void draw_explorer(const explorer_data &data)
{
  set_camera_position(data.camera_position);

  clear_screen(color_white());
  draw_map(data.map, data.camera_position);
  draw_player(data.player);

  if(data.state == EDIT_STATE)
  {
    fill_rectangle(color_white(), 0, 0, 500, 70, option_to_screen());

    fill_rectangle(color_for_tile_kind(data.editor_tile_kind), 5, 13, TILE_WIDTH, TILE_HEIGHT, option_to_screen());

    draw_text("Editor", color_black(), 0, 0, option_to_screen());
    draw_text("Kind: " + to_string(((int)data.editor_tile_kind) + 1),color_black(), 7, 18, option_to_screen());

    draw_text("Press V: Village | B: Grass+River | N: Forest | M: Mountain",color_black(), 0, 50, option_to_screen());
  }
  else
  {
    draw_text("Playing - Shift+E to edit", color_black(), 0, 0, option_to_screen());
  }

  refresh_screen();
}

/** Clamp a value between min and max.
 *
 * @param val the value to clamp
 * @param min_val minimum allowed value
 * @param max_val maximum allowed value
 * @return clamped value
 */
double clamp(double val, double min_val, double max_val)
{
  if(val < min_val) return min_val;
  if(val > max_val) return max_val;
  return val;
}

/** Handle input in edit mode (mouse + keyboard).
 *
 * @param data - passed by reference; explorer state is updated
 */
void handle_edit_input(explorer_data &data)
{
  if(key_typed(ESCAPE_KEY))
  {
    data.state = PLAY_STATE;
  }

  if(key_typed(R_KEY))
  {
    random_map(data.map);
  }

  if(mouse_down(LEFT_BUTTON))
  {
    point_2d mouse_pos = mouse_position();
    int c = (mouse_pos.x + data.camera_position.x) / TILE_WIDTH;
    int r = (mouse_pos.y + data.camera_position.y) / TILE_HEIGHT;

    if(c >= 0 && c < MAX_MAP_COLS && r >= 0 && r < MAX_MAP_ROWS)
    {
      data.map.tiles[c][r].kind = data.editor_tile_kind;
    }
  }

  if (key_typed(NUM_1_KEY)) data.editor_tile_kind = WATER_TILE;
  if (key_typed(NUM_2_KEY)) data.editor_tile_kind = GRASS_TILE;
  if (key_typed(NUM_3_KEY)) data.editor_tile_kind = DIRT_TILE;
  if (key_typed(NUM_4_KEY)) data.editor_tile_kind = SAND_TILE;

  if(key_typed(V_KEY)) add_village(data.map);
  if(key_typed(B_KEY)) add_grass_with_river(data.map);
  if(key_typed(N_KEY)) add_forest(data.map);
  if(key_typed(M_KEY)) add_mountain(data.map);

  // Move camera with arrows in edit mode
  if(key_down(LEFT_KEY))  data.camera_position.x -= 5;
  if(key_down(RIGHT_KEY)) data.camera_position.x += 5;
  if(key_down(UP_KEY))    data.camera_position.y -= 5;
  if(key_down(DOWN_KEY))  data.camera_position.y += 5;

  // Clamp camera
  double min_cam_x = -screen_width() / 2;
  double min_cam_y = -screen_height() / 2;
  double max_cam_x = MAP_WIDTH - screen_width() / 2;
  double max_cam_y = MAP_HEIGHT - screen_height() / 2;

  data.camera_position.x = clamp(data.camera_position.x, min_cam_x, max_cam_x);
  data.camera_position.y = clamp(data.camera_position.y, min_cam_y, max_cam_y);
}

/** Handle input depending on current explorer state.
 *
 * @param data - passed by reference; player, map, and camera may update
 */
void handle_input(explorer_data &data)
{
  if(key_down(LEFT_SHIFT_KEY) && key_typed(E_KEY))
  {
    data.state = EDIT_STATE;
  }

  if(data.state == EDIT_STATE)
  {
    handle_edit_input(data);
  }
  else if(data.state == PLAY_STATE)
  {
    // Player movement with WASD
    if(key_down(W_KEY)) data.player.position.y -= data.player.speed;
    if(key_down(S_KEY)) data.player.position.y += data.player.speed;
    if(key_down(A_KEY)) data.player.position.x -= data.player.speed;
    if(key_down(D_KEY)) data.player.position.x += data.player.speed;

    // Constrain player to map bounds
    data.player.position.x = clamp(data.player.position.x, 0, MAP_WIDTH);
    data.player.position.y = clamp(data.player.position.y, 0, MAP_HEIGHT);

    // Camera follows player in play mode
    data.camera_position.x = data.player.position.x - screen_width()/2;
    data.camera_position.y = data.player.position.y - screen_height()/2;

    // Clamp camera
    double min_cam_x = -screen_width() / 2;
    double min_cam_y = -screen_height() / 2;
    double max_cam_x = MAP_WIDTH - screen_width() / 2;
    double max_cam_y = MAP_HEIGHT - screen_height() / 2;

    data.camera_position.x = clamp(data.camera_position.x, min_cam_x, max_cam_x);
    data.camera_position.y = clamp(data.camera_position.y, min_cam_y, max_cam_y);
  }
}

int main()
{
  open_window("Map Explorer", 800, 600);

  explorer_data data;
  init_explorer_data(data);

  while( ! quit_requested() )
  {
    draw_explorer(data);

    process_events();
    handle_input(data);
  }
}
