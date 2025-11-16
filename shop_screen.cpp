#include "./shop_screen.hpp"
#include "./lib/raylib.h"

ShopScreen::ShopScreen() : _remaining_ticks(60*10) {}

void ShopScreen::draw() {
    DrawText("OMG LE SHOP", 600, 100, 10, GREEN);
    --_remaining_ticks;	
}

bool ShopScreen::should_change() {
    return (_remaining_ticks < 0);
}

void ShopScreen::reset_screen() {
    _remaining_ticks = 60*10;
}

size_t ShopScreen::switch_to() {
    return GAME_SCREEN;
}

void ShopScreen::kill_screen() {
    return;
}

