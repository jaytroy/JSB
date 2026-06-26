//
// Created by jay on 6/26/26.
//

#include "nCursesManager.h"

#include <ncurses.h>

NCursesManager::NCursesManager() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

int NCursesManager::getInput() {
    c = getch();
    return c;
}
