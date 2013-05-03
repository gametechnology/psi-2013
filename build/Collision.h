#pragma once

#include "../source/Game/Enemy.h"
#include "../source/Game/EnemyFighter.h"
#include "../source/Game/Laser.h"

static class Collision
{
public:
	Collision(void);
	~Collision(void);
	void static LaserNarrowPhase(array<Enemy*> _enput, array<Laser*> _laput);
	void static NarrowPhaseDetection(array<Enemy*> _input);
};

