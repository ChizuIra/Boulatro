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

class Screen {
    public:
	virtual void draw() = 0;
	virtual bool should_change() = 0;
	virtual void reset_screen() = 0;
};

class GameScreen : public Screen {
    private:
	Boule _boule_joueur;
	Boule _boule_adversaire;

    public:
	GameScreen(): _boule_joueur(0, 150, GREEN), _boule_adversaire(0, 180, RED)
	{}

	void draw() override {
            _boule_joueur.update();
            _boule_adversaire.update();
	    DrawText("Tour : ", 1, 0, 20, WHITE);
	    _boule_joueur.drawScore(1, 20);
	    _boule_adversaire.drawScore(1, 40);
            _boule_joueur.draw();
            _boule_adversaire.draw();
	}

	bool should_change() override {
	    return _boule_joueur.get_score() >= 10;
	}

	void reset_screen() override {
	    _boule_joueur = Boule(0, 150, GREEN);
	    _boule_adversaire = Boule(0, 180, RED);
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
};

int main(void) {
    srand(time(NULL));
    InitWindow(1200, 200, "Boulatro");

    std::vector<std::unique_ptr<Screen>> screens;
    screens.push_back(std::make_unique<GameScreen>());
    screens.push_back(std::make_unique<ShopScreen>());

    SetTargetFPS(60);

    size_t current_screen = 0;
    
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
	if(screens[current_screen]->should_change()) {
	    current_screen = (current_screen+1)%2;
	    screens[current_screen]->reset_screen();
	}
        screens[current_screen]->draw();
        EndDrawing();
    }
}
