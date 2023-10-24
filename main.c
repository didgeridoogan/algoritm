#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SIZE 20
#define PLAYER '@'
#define EMPTY '.'
#define WALL '#'

char map[MAP_SIZE][MAP_SIZE];

void initializeMap()
{
    for (int y = 0; y < MAP_SIZE; y++)
    {
        for (int x = 0; x < MAP_SIZE; x++)
        {
            if (x == 0 || x == MAP_SIZE - 1 || y == 0 || y == MAP_SIZE - 1)
            {
                map[y][x] = WALL;
            }
            else
            {
                if (rand() % 5 == 0)
                {
                    map[y][x] = WALL; // Randomly placera väggar
                }
                else
                {
                    map[y][x] = EMPTY;
                }
            }
        }
    }
}

void printMap()
{
    for (int y = 0; y < MAP_SIZE; y++)
    {
        for (int x = 0; x < MAP_SIZE; x++)
        {
            printf("%c ", map[y][x]);
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    initializeMap();
    int playerX = MAP_SIZE / 2;
    int playerY = MAP_SIZE / 2;

    map[playerY][playerX] = PLAYER;

    while (1)
    {
        system("clear");
        printMap();

        char move;
        printf("Enter a move (w/a/s/d, q to quit): ");
        scanf(" %c", &move);
        if (move == 'q')
        {
            break; // Stäng spelet om "q" är nedtryckt
        }

        map[playerY][playerX] = EMPTY;

        switch (move)
        {
        case 'w':
            if (map[playerY - 1][playerX] != WALL)
            {
                playerY--;
            }
            break;

        case 'a':
            if (map[playerY][playerX - 1] != WALL)
            {
                playerX--;
            }
            break;

        case 's':
            if (map[playerY + 1][playerX] != WALL)
            {
                playerY++;
            }
            break;
            
        case 'd':
            if (map[playerY][playerX + 1] != WALL)
            {
                playerX++;
            }
            break;
        }

        map[playerY][playerX] = PLAYER;
    }

    return 0;
}