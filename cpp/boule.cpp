#include "../hpp/boule.hpp"
#include <sstream>

Vector2 Boule::get_next_pos() const {
    return CLITERAL(Vector2){.x=_pos.x+_vit.x*_alt_vitesse, .y=_pos.y+_vit.y*_alt_vitesse};
}

void Boule::check_collision(char* hit_x, char* hit_y) const {
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

void Boule::roll_alt() {
    _alt_vitesse = 10;
}


Boule::Boule(int pos_x, int pos_y, Color color)
: _pos({(float)pos_x, (float)pos_y}), _color(color), _radius(5), _vit({1.0f,0.0f}), _score(0) {
    roll_alt();
}

void Boule::draw() const {
    DrawCircle(_pos.x, _pos.y, _radius, _color);
}

unsigned int Boule::get_score() const {
    return _score;
}

void Boule::draw_score(unsigned int x, unsigned int y) const {
    std::stringstream st("");
    st << _score;
    DrawText(st.str().c_str(), x, y , 20, _color);
}

void Boule::update() {
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

void Boule::set_position(int pos_x){
    _pos.x = pos_x;
}

