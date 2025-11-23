#include "bank.hpp"
#include <sstream>

void Bank::draw_argent(){
    std::stringstream st("");
    st << _argent;
    DrawText("Argent :", 200, 0, 20, YELLOW);
    DrawText(st.str().c_str(), 300, 0, 20, YELLOW);
}

void Bank::game_income(Boule boule_joueur, int minLap){
    _argent += boule_joueur.get_score() - minLap;
}

void Bank::interest(int maxInterest){
    int interest = _argent/10;
    if(interest > maxInterest){
	_argent += maxInterest;
    }else{
	_argent += interest;
    }
};

