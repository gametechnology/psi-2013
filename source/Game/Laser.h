#ifndef LASER_H
#define LASER_H

#include <Engine/GameObject.h>
#include <Engine/Core.h>
#include <Engine/Scene.h>
#include <Engine/MeshComponent.h>

#include "Enemy.h"
#include "Stations\DefenceStation.h"
#include "NetworkInterface.h"

class Laser : public GameObject
{
	public:
		static int newLaserId;

		Laser(irr::scene::ISceneManager*);
		~Laser();

		virtual void init();
		virtual void onAdd();

		void fire(irr::core::vector3df* position, irr::core::vector3df* rotation, irr::core::vector3df target, irr::f32 speed);
		void update();
		void contactResolverA(Enemy* input);
		void contactResolverA(DefenceStation* input);

		int getId();
		void setId(int id);
	private:
		irr::u32 _timeofLife;
		irr::u32 _currentLife;
		irr::core::vector3df _direction;
		
		MeshComponent* _mesh;
		irr::scene::ISceneManager* _smgr;

		unsigned int _damage;
		bool _hasAnIrrlichtNode;
		int _id;
};

#endif