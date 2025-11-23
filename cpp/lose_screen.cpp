#include "lose_screen.hpp"
#include "../lib/raylib.h"

LoseScreen::LoseScreen() : _remaining_ticks(60*10) {}

void LoseScreen::draw() {
    DrawText("Gros Looser ta perdu", 600, 100, 10, RED);
    --_remaining_ticks;	
}

bool LoseScreen::should_change() {
    return (_remaining_ticks < 0);
}

void LoseScreen::reset_screen() {
    _remaining_ticks = 60*10;
}

size_t LoseScreen::switch_to() {
    return GAME_SCREEN;
}

void LoseScreen::kill_screen() {
    return;
}
