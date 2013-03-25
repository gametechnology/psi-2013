#ifndef GAME
#define GAME

#include "Team.h"

class Game {
private:
	Team team1;
	Team team2;

public:
	Game();
	~Game();
	Team GetTeam1() { return team1; }
	Team GetTeam2() { return team2; }

};

#endif
