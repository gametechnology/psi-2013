#pragma once

#include "../source/Game/Enemy.h"
#include "../source/Game/EnemyFighter.h"
#include "../source/Game/Laser.h"

static class Collision
{
public:
	Collision(void);
	~Collision(void);
	void static LaserNarrowPhase(vector<Enemy*> _enput, vector<Laser*> _laput);
	void static NarrowPhaseDetection(vector<Enemy*> _input);
};

