#include "./lib/raylib.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <ctime>
#include <vector>
#include <memory>

constexpr unsigned int MODIF_MAX = 9;

class Boule {
    private:
	Vector2 _pos;
	Vector2 _vit;
        int     _alt_vitesse;
        int     _radius;
        Color   _color;
        int     _score;

	Vector2 get_next_pos() const {
	    return CLITERAL(Vector2){.x=_pos.x+_vit.x*_alt_vitesse, .y=_pos.y+_vit.y*_alt_vitesse};
	}

	void check_collision(char* hit_x, char* hit_y) const {
	    Vector2 fut = get_next_pos();
            if(fut.x >= GetScreenWidth()) {
                *hit_x = 1;
            }
	    if(fut.x < 0) {
		*hit_x = -1;
	    }
	    if(fut.y >= GetScreenHeight()) {
		*hit_y = 1;
	    }
	    if(fut.x < 0) {
		*hit_y = -1;
	    }
	}

	void roll_alt() {
	    _alt_vitesse = (rand()%MODIF_MAX)+1;
	}

    public:
        Boule(int pos_x, int pos_y, Color color)
        : _pos({(float)pos_x, (float)pos_y}), _color(color), _radius(5), _vit({1.0f,0.0f}), _score(0) {
  	    roll_alt();
	}

        void draw() const {
            DrawCircle(_pos.x, _pos.y, _radius, _color);
        }

        unsigned int get_score() const {
            return _score;
        }

	void drawScore(unsigned int x, unsigned int y) const {
	    std::stringstream st("");
	    st << _score;
	    DrawText(st.str().c_str(), x, y , 20, _color);
	}

        void update() {
	    char x = 0, y = 0;
            check_collision(&x, &y);
	    if (x == -1) {
		++_score;
		roll_alt();
	    }
	    if (x) _vit.x *= -1;
	    if (y) _vit.y *= -1;
	    _pos = get_next_pos();
        }
};

class Bank {
	private :
		int _argent = 10;
	public :
	void drawArgent(){
		std::stringstream st("");
	    st << _argent;
		DrawText("Argent :", 200, 0, 20, YELLOW);
		DrawText(st.str().c_str(), 300, 0, 20, YELLOW);
	}
	/*
	Calcule l'argent gagner suite au score du round
	+1 $ par tour bonus

	@param Boule Boule du joueur
	@param int le nombre de tour minimum pour gagner le round
	*/
	void gameIncome(Boule boule_joueur, int minLap){
		_argent += boule_joueur.get_score() - minLap;
	}
	/*
	Calcule l'argent gagner grace l'intérêt (en fin de round)

	@param int L'intérêt max autorisé par le jeu
	*/
	void interest(int maxInterest){
		int interest = _argent/10;
		if(interest > maxInterest){
			_argent += maxInterest;
		}else{
			_argent += interest;
		}
	};
};

Bank playerBank;
Boule boule_joueur(0, 150, GREEN);
Boule boule_adversaire(0, 180, RED);

//Index des Screens
const size_t GAME_SCREEN 	= 0;
const size_t SHOP_SCREEN 	= 1;
const size_t LOOSE_SCREEN	= 2;

class Screen {
    public:
	virtual void 	draw() = 0;
	virtual bool 	should_change() = 0;
	virtual void 	reset_screen() = 0;
	virtual void 	kill_screen() = 0;
	virtual	size_t	switch_to() = 0 ;
};

class GameScreen : public Screen {
    private:

    public:
	GameScreen() {}

	void draw() override {
        boule_joueur.update();
        boule_adversaire.update();
	    DrawText("Tour : ", 1, 0, 20, WHITE);
	    boule_joueur.drawScore(1, 20);
	    boule_adversaire.drawScore(1, 40);
        boule_joueur.draw();
        boule_adversaire.draw();

		playerBank.drawArgent();
	}

	bool should_change() override {
	    return boule_adversaire.get_score() >= 10;
	}	

	void reset_screen() override {
	    boule_joueur = Boule(0, 150, GREEN);
	    boule_adversaire = Boule(0, 180, RED);
	}
	size_t switch_to(){
		if(isWin()){
			return SHOP_SCREEN;
		}
		return LOOSE_SCREEN;
	}
	void kill_screen() override {
		if(isWin()){
			// calcule Argent
			playerBank.gameIncome(boule_joueur,10);
			playerBank.interest(5);
		}
	}
	bool isWin(){
		if(boule_joueur.get_score() >= boule_adversaire.get_score()){
			return true;
		}else{
			return false;
		}
	}

};

class ShopScreen : public Screen {
    private:
	int _remaining_ticks;
    public:
        ShopScreen() : _remaining_ticks(60*10) {}
	void draw() override {
	    DrawText("OMG LE SHOP", 600, 100, 10, GREEN);
	    --_remaining_ticks;	
	}
	bool should_change() override {
	    return (_remaining_ticks < 0);
	}
	void reset_screen() override {
	    _remaining_ticks = 60*10;
	}
	size_t switch_to(){
		return GAME_SCREEN;
	}	
	void kill_screen() override {
		return;
	}
};

class LooseScreen : public Screen {
    private:
	int _remaining_ticks;
    public:
        LooseScreen() : _remaining_ticks(60*10) {}
	void draw() override {
	    DrawText("Gros Looser ta perdu", 600, 100, 10, RED);
	    --_remaining_ticks;	
	}
	bool should_change() override {
	    return (_remaining_ticks < 0);
	}
	void reset_screen() override {
	    _remaining_ticks = 60*10;
	}
	size_t switch_to(){
		return GAME_SCREEN;
	}	
	void kill_screen() override {
		return;
	}
};

int main(void) {
    srand(time(NULL));
    InitWindow(1200, 200, "Boulatro");

    std::vector<std::unique_ptr<Screen>> screens;
    screens.push_back(std::make_unique<GameScreen>());
    screens.push_back(std::make_unique<ShopScreen>());
	screens.push_back(std::make_unique<LooseScreen>());

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
