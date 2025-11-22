#pragma once
#include "./boule.hpp"

class Bank {
	private :
		int _argent = 10;
	public :
	void draw_argent();
	/*
	Calcule l'argent gagner suite au score du round
	+1 $ par tour bonus

	@param Boule Boule du joueur
	@param int le nombre de tour minimum pour gagner le round
	*/
	void game_income(Boule boule_joueur, int minLap);

	/*
	Calcule l'argent gagner grace l'intérêt (en fin de round)

	@param int L'intérêt max autorisé par le jeu
	*/
	void interest(int maxInterest);
};
