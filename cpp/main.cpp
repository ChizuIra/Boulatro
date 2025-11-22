#include "../lib/raylib.h"
#include "../hpp/def.hpp"
#include "../hpp/game_screen.hpp"
#include "../hpp/shop_screen.hpp"
#include "../hpp/lose_screen.hpp"
#include "../hpp/boule.hpp"
#include <iostream>
#include <ctime>
#include <vector>
#include <memory>
#include <math.h>
#include <stdio.h>


int main(void) {
    srand(time(NULL));
    InitWindow(1200, 200, "Boulatro");

    std::vector<std::unique_ptr<Screen>> screens;
    screens.push_back(std::make_unique<GameScreen>());
    screens.push_back(std::make_unique<ShopScreen>());
	screens.push_back(std::make_unique<LoseScreen>());

    SetTargetFPS(60);

    size_t current_screen = 0;
    
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
	if(screens[current_screen]->should_change()) {
		screens[current_screen]->kill_screen();
	    current_screen =  screens[current_screen]->switch_to();
	    screens[current_screen]->reset_screen();
	}
        screens[current_screen]->draw();
        EndDrawing();
    }
}
