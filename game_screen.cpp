#include "./game_screen.hpp"
#include "./lib/raylib.h"
#include <math.h>

GameScreen::GameScreen() 
: _isStarted(false), _boule_adversaire(0, 180, RED) , _boule_joueur(0, 150, GREEN) , _PlayerPin(200,75,WHITE){}

void GameScreen::draw() {
    if(_isStarted){
	draw_started_game();
    }else{
	if(IsKeyPressed(KEY_SPACE)){
	    _PlayerPin.stop_pin();
	    float position = 1-fabsf((_PlayerPin.get_PosPin()/400.0)-1);
	    _boule_joueur.set_position(600*position);
	    _isStarted = true;
	}
	
	_PlayerPin.update();
	draw_pin();
    }
}

void GameScreen::draw_started_game() {
    _boule_joueur.update();
    _boule_adversaire.update();
    DrawText("Tour : ", 1, 0, 20, WHITE);
    _boule_joueur.draw_score(1, 20);
    _boule_adversaire.draw_score(1, 40);
    _boule_joueur.draw();
    _boule_adversaire.draw();
    _playerBank.draw_argent();
}

void GameScreen::draw_pin(){
    char temp_txt[] = "Appuie sur Espace";
    DrawText(temp_txt,(1200-MeasureText(temp_txt,20))/2, 150, 20, WHITE);
    DrawRectangle(200,50,800,100,Color{ 89, 18, 13 , 255});
    DrawRectangle(450,50,300,100,Color{161, 0, 0,255});
    DrawRectangle(550,50,100,100,Color{161, 102, 0,255});
    DrawRectangle(590,50,20,100,Color{97, 161, 0,255});
    DrawRectangleLines(200,50,800,100,WHITE);
    _PlayerPin.draw();

}

bool GameScreen::should_change() {
    return _boule_adversaire.get_score() >= 10;
}	

void GameScreen::reset_screen() {
    _boule_joueur = Boule(0, 150, GREEN);
    _boule_adversaire = Boule(0, 180, RED);
}

size_t GameScreen::switch_to() {
    if(is_win()){
	return SHOP_SCREEN;
    }
    return LOSE_SCREEN;
}

void GameScreen::kill_screen() {
    if(is_win()){
	// calcule Argent
	_playerBank.game_income(_boule_joueur,10);
	_playerBank.interest(5);
    }
    _isStarted = false;
    _PlayerPin.start_pin();
}

bool GameScreen::is_win() {
    if(_boule_joueur.get_score() >= _boule_adversaire.get_score()){
	return true;
    }else{
	return false;
    }
}

