#pragma once
#include "../lib/raylib.h"

class Boule {
    private:
	Vector2 _pos;
	Vector2 _vit;
        int     _alt_vitesse;
        int     _radius;
        Color   _color;
        int     _score;

	Vector2 get_next_pos() const;


	void check_collision(char* hit_x, char* hit_y) const;
        
	void roll_alt();

    public:
        Boule(int pos_x, int pos_y, Color color);
        
        void draw() const;
        unsigned int get_score() const;
	void draw_score(unsigned int x, unsigned int y) const;
        void update();
	void set_position(int pos_x);
};

