#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

typedef struct map_t
{
    int tile_size;
    int tiles[10][10];
} map_t;

typedef enum tiles_e
{
    TILE_FLOOR,
    TILE_WALL,
    TILE_WATER
} tiles_e;

void DrawMap(map_t map, int x, int y)
{
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            switch (map.tiles[y][x])
            {
            case TILE_FLOOR:
            {
                DrawRectangle(x * map.tile_size, y * map.tile_size, map.tile_size, map.tile_size, GREEN);
            }
            break;
            case TILE_WALL:
            {
                DrawRectangle(x * map.tile_size, y * map.tile_size, map.tile_size, map.tile_size, ORANGE);
            }
            break;
            case TILE_WATER:
            {
                DrawRectangle(x * map.tile_size, y * map.tile_size, map.tile_size, map.tile_size, BLUE);
            }
            }
        }
    }
}

int main()
{
    map_t main_map = (map_t){
        .tile_size = 16,
        .tiles = {
            {1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 2, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 2, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 2, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 2, 2, 2, 0, 1, 1, 1},
            {1, 0, 1, 1, 0, 2, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 2, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 2, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 2, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 2, 1, 1, 1, 1},
        }};

    InitWindow(165, 165, "Tilemap");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawMap(main_map, 0, 0);
        EndDrawing();
    }
}