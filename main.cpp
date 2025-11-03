#include "./lib/raylib.h"
#include <cstdlib>
#include <sstream>

class Boule {
    private:
        int _pos_x;
        int _pos_y;
        int _vit_x;
        int _vit_y;
        int          _alt_vitesse;
        const int    _radius;
        Color        _color;
        int _score;

    public:
        Boule(int pos_x, int pos_y, Color color)
        : _pos_x(pos_x), _pos_y(pos_y), _color(color), _radius(5) {
            _vit_x = 1;
            _vit_y = 0;
            _alt_vitesse = 0;
            _score = 0;
        }

        void check_colision() {
            if(_pos_x+_vit_x*_alt_vitesse >= GetScreenWidth()) {
                _vit_x *= -1;
            }

            if(_pos_x+_vit_x*_alt_vitesse <= 0) {
                ++_score;
                _vit_x *= -1;
            }

            if(_pos_y*_vit_y*_alt_vitesse >= GetScreenHeight()
            || _pos_y+_vit_y*_alt_vitesse) {
                _vit_y *= -1;
            }
        }

        void draw() {
            DrawCircle(_pos_x, _pos_y, _radius, _color);
        }

        unsigned int get_score() {
            return _score;
        }

        void move() {
            _alt_vitesse = (rand()%10) + _score;
            check_colision();
            _pos_x += _vit_x * _alt_vitesse;
            _pos_y += _vit_y;
        }
};

int main(void) {
    srand(time(NULL));
    InitWindow(1200, 200, "Boulatro");

    Boule boule_1 = Boule(10, 150, GREEN);
    Boule boule_2 = Boule(10, 160, YELLOW);
    Boule boule_3 = Boule(10, 170, RED);
    std::stringstream st1;
    std::stringstream st2;
    std::stringstream st3;
    SetTargetFPS(60);
    
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Lap : ", 1, 0, 20, WHITE);
        
        st1.str("");
        st2.str("");
        st3.str("");
        st1 << boule_1.get_score();
        st2 << boule_2.get_score();
        st3 << boule_3.get_score();
        
        DrawText(st1.str().c_str(), 1, 20, 20, GREEN);
        DrawText(st2.str().c_str(), 1, 40, 20, YELLOW);        
        DrawText(st3.str().c_str(), 1, 60, 20, RED);
        boule_1.draw();
        boule_3.draw();

        boule_1.move();
        boule_3.move();
        
        EndDrawing();
    }
}
