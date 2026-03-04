#include "splashkit.h"
#include <stdio.h>

enum tile_kind{
    WATER_TILE,
    GRASS_TILE,
    DIRT_TILE,
    SAND_TILE
};

struct tile_data{
    tile_kind kind;
};


const int MAX_MAP_ROWS = 20;
const int MAX_MAP_COLS = 20;

const int TILE_WIDTH = 60;
const int TILE_HEIGHT = 60;

struct map_data{
    tile_data tiles[MAX_MAP_COLS][MAX_MAP_ROWS];
};

color color_for_tile_kind(tile_kind kind){
    switch (kind)
    {
    case WATER_TILE:
        return color_blue();
    case GRASS_TILE:
        return color_lawn_green();
    case SAND_TILE:
        return color_blanched_almond();
    case DIRT_TILE:
        return color_rosy_brown();
    default:
        return color_white();
    }
}

void init_map(map_data &map){
    for (int i = 0; i < MAX_MAP_COLS; i++){
        for (int j = 0; j < MAX_MAP_ROWS; j++){
            map.tiles[i][j].kind = GRASS_TILE;
        }
    }
}

void draw_tile(const tile_data &tile, double x, double y){
    color tile_color = color_for_tile_kind(tile.kind);
    fill_rectangle(tile_color, x, y, TILE_WIDTH, TILE_HEIGHT);
}

void draw_map(const map_data &map){
    for (int i = 0; i < MAX_MAP_COLS; i++){
        for (int j = 0; j < MAX_MAP_ROWS; j++){
            draw_tile(map.tiles[i][j], i * TILE_WIDTH, j * TILE_HEIGHT);
        }
    }
}

int main()
{
    map_data map;
    init_map(map);

    open_window("Map explorer", 800, 600);

    while (!quit_requested())
    {
        clear_screen(color_white());
        draw_map(map);
        refresh_screen();

        process_events();
    }
}
