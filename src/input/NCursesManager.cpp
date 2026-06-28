//
// Created by jay on 6/26/26.
//

#include "NCursesManager.h"

#include <ncurses.h>

/**
 * Sets up the basic stuff required for NCurses to work.
 */
NCursesManager::NCursesManager() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

/**
 * Polls an event (keystroke) from keyboard.
 * @param outEvent The caller's InputEvent object.
 * @return True if poll is successful, otherwise false.
 */
bool NCursesManager::pollEvent(InputEvent &outEvent) {
    c = getch();
    if (c == ERR) return false;
    outEvent.code = c;
    outEvent.pressed = true;
    return true;
}
