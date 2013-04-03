#pragma once
#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"
#include "WeaponCameraMover.h"
#include "Bullet.h"

class WeaponStation : public Entity
{
public:
	WeaponStation(Composite* parent);
	~WeaponStation();
	WeaponCameraMover* cameramover;
	void update();
	void draw();
private:
	video::ITexture* _stationTexture;
	void shoot();
	
	int _nrOfBullets;
	Bullet *_ammo;
	int _bulletNr;
	int _shootingInterval;
};