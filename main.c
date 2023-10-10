#include <ncurses.h>

int main(void)
{
    initscr(); //Startar upp nscurses systemet och låter en kalla på alla andra funktioner i vår terminal.
    noecho(); //Förhindrar initscr från att rita ut allting på direkten
    curs_set(0); //Gör cursorn osynlig

    while(getch() != 'q')
    {
        mvaddch(10,20,'@');
    }

    endwin();

    return 0;
}