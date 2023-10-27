#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Namnge saker så jag slipper skriva de om och om igen
#define MAP_SIZE 20
#define PLAYER '@'
#define EMPTY '.'
#define WALL '#'
#define DOOR '+'

// Kartans struktur
typedef struct Map
{
    char tiles[MAP_SIZE][MAP_SIZE]; // Ha koll på läge
    struct Map *north;
    struct Map *south;
    struct Map *east;
    struct Map *west;
} Map;

Map *currentMap;

// Starta upp mappen
void initializeMap(Map *map, int doorCount)
{
    for (int y = 0; y < MAP_SIZE; y++)
    {
        for (int x = 0; x < MAP_SIZE; x++)
        {
            // Placera väggar längs kanterna
            if (x == 0 || x == MAP_SIZE - 1 || y == 0 || y == MAP_SIZE - 1)
            {
                map->tiles[y][x] = WALL;
            }
            else
            {
                if (rand() % 5 == 0)
                {
                    map->tiles[y][x] = WALL; // Slumpmässiga väggar i mitten
                }
                else
                {
                    map->tiles[y][x] = EMPTY;
                }
            }
        }
    }

    // Placera dörrar intill väggar
    for (int i = 0; i < doorCount; i++)
    {
        int x, y;
        do
        {
            x = 2 + rand() % (MAP_SIZE - 4);
            y = 2 + rand() % (MAP_SIZE - 4);
        } while (map->tiles[y][x] != WALL);

        map->tiles[y][x] = DOOR;
    }
}

// Gör dörren funktionerande
void createDoor(Map *map, int x, int y)
{
    map->tiles[y][x] = DOOR;
}

// Skriv ut kartan i terminalen
void printMap(Map *map)
{
    for (int y = 0; y < MAP_SIZE; y++)
    {
        for (int x = 0; x < MAP_SIZE; x++)
        {
            printf("%c ", map->tiles[y][x]);
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    Map *startMap = (Map *)malloc(sizeof(Map));
    initializeMap(startMap, 2); // Max 2 dörrar per karta
    currentMap = startMap;

    int playerX = MAP_SIZE / 2;
    int playerY = MAP_SIZE / 2;
    currentMap->tiles[playerY][playerX] = PLAYER;

    while (1)
    {
        system("clear"); // Ta bort allt innan, så att man faktiskt kan se kartan
        printMap(currentMap);

        char move;
        printf("Ange rörelse (w/a/s/d, q för att avsluta): ");
        scanf(" %c", &move);

        // Stäng ner spelet om man skriver in "q", så att det inte kör för evigt
        if (move == 'q')
        {
            break;
        }

        int moveX = playerX;
        int moveY = playerY;

        switch (move) // Spelarens rörelse
        {
        case 'w':
            moveY--;
            break;
        case 'a':
            moveX--;
            break;
        case 's':
            moveY++;
            break;
        case 'd':
            moveX++;
            break;
        }

        if (currentMap->tiles[moveY][moveX] == DOOR) // Kolla om spelaren "overlaps" med en dörr
        {
            createDoor(currentMap, moveX, moveY);

            Map *newMap = (Map *)malloc(sizeof(Map));
            initializeMap(newMap, 2); // 2 dörrar igen
            newMap->west = currentMap;
            currentMap->east = newMap;

            currentMap = newMap;
        }

        // Kontrollera att spelaren inte rör sig igenom väggar, stoppa den isf
        if (currentMap->tiles[moveY][moveX] != WALL)
        {
            currentMap->tiles[playerY][playerX] = EMPTY;
            playerX = moveX;
            playerY = moveY;
            currentMap->tiles[playerY][playerX] = PLAYER;
        }
    }

    return 0;
}