//
// Created by jay on 6/26/26.
//

#include "NCursesManager.h"

#include <ncurses.h>

NCursesManager::NCursesManager() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

bool NCursesManager::pollEvent(InputEvent &outEvent) {
    c = getch();
    if (c == ERR) return false;
    outEvent.code = ch;
    outEvent.pressed = true;
    return true;
}
