#ifndef ENEMY_FIGHTER_H
#define ENEMY_FIGHTER_H

#include "Enemy.h"
#include "StateSwitchFighter.h"
#include "Laser.h"

class EnemyFighter : public Enemy
{
public:
	EnemyFighter(irr::core::vector3df position);
	~EnemyFighter(void);

	virtual void update();
private:
	void		loadLaser();
	void		fireLaserAt(vector3df target);
	int			_curLaser;
	int			_nrLasers;
	int			_fireTime;
	Laser*		_laser;
	vector3df	_target;
	vector3df	_endPosition;
	StateSwitchFighter* stateSwitch;
};

#endif