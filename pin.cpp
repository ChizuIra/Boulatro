#include "./pin.hpp"
#include "./boule.hpp"
#include "./lib/raylib.h"

Vector2 Pin::get_next_pos() const {
    return CLITERAL(Vector2){_pos.x+_vit.x, _pos.y+_vit.y};
}

void Pin::check_collision(char* hit_x, char* hit_y) const {
    Vector2 fut = get_next_pos();
    if(fut.x >= 1000) {
        *hit_x = 1;
    }
    if(fut.x < 200) {
	*hit_x = -1;
    }
}

Pin::Pin(int pos_x, int pos_y, Color color)
: _pos({(float)pos_x, (float)pos_y}), _color(color), _vit({7,0}) {}

void Pin::draw() const {
    DrawRectangle(_pos.x, _pos.y, 5, 50, _color);    
}

void Pin::update() {
    char x = 0, y = 0;
    check_collision(&x, &y);
    if (x) _vit.x *= -1;
    if (y) _vit.y *= -1;
    _pos = get_next_pos();
}
void Pin::stop_pin(){
    _vit = {0,0};
}
void Pin::start_pin(){
    _vit = {7,0};
}

float Pin::get_PosPin() const {
    return _pos.x-200;
}

