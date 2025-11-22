#pragma once
#include "../lib/raylib.h"

class Pin {
    private:
	Vector2 _pos;
	Vector2 _vit;
	Color   _color;

	Vector2 get_next_pos() const;
	void check_collision(char* hit_x, char* hit_y) const;

    public:
	
	Pin(int pos_x, int pos_y, Color color);
        void draw() const;
        void update();
	void stop_pin();
	void start_pin();
	float get_PosPin() const;
    };
