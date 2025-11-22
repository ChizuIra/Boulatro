#pragma once
#include "./def.hpp"
#include "./screen.hpp"
#include "./boule.hpp"
#include "./pin.hpp"
#include "./boule.hpp"
#include "./bank.hpp"

class GameScreen : public Screen {
    private:    
	Boule _boule_adversaire;
	Boule _boule_joueur;
	Pin _PlayerPin;
	Bank _playerBank;
	bool _isStarted;

    public:
	GameScreen();
	void draw() override;
	void draw_started_game();
	void draw_pin();
	bool should_change() override;
	void reset_screen() override;
	size_t switch_to() override;
	void kill_screen() override;
        bool is_win();
};
