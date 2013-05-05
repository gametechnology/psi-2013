#ifndef COLLISION
#define COLLISION
/*
#include "../source/Game/Enemy.h"
#include "../source/Game/EnemyFighter.h"
#include "../source/Game/Laser.h"
*/
#include "Irrlicht\irrlicht.h"
#include "Engine\Entity.h"

class Collision
{
public:
	Collision(void);
	~Collision(void);
/*	void static LaserNarrowPhase(vector<Enemy*> _enput, vector<Laser*> _laput);
	void static NarrowPhaseDetection(vector<Enemy*> _input); */
	void static NarrowPhaseDetection(vector<Entity*> _input);
	irr::core::vector3df static componentOnto(irr::core::vector3df input, irr::core::vector3df deltavelocity);
};

#endif