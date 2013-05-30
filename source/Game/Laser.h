#ifndef LASER_H
#define LASER_H

#include <Engine/Core.h>
#include <Engine/Scene.h>
#include <Engine/MeshComponent.h>

#include "Enemy.h"
#include "NetworkInterface.h"

class DefenceStation;

class Laser : public Enemy
{
	public:
		static int newLaserId;

		Laser();
		Laser(irr::scene::ISceneManager*);
		~Laser();

		virtual void init();
		virtual void handleMessage(unsigned int, void* data = 0) { };
		virtual void update();

		void setScene(Scene&);
		Scene* getScene();

		void fire(irr::core::vector3df* position, irr::core::vector3df* rotation, irr::core::vector3df target, irr::f32 speed);
		void contactResolverA(DefenceStation* input);

		int getId();
		void setId(int id);
	private:
		irr::u32 _timeofLife;
		irr::u32 _currentLife;
		irr::core::vector3df _direction;
		
		MeshComponent* _mesh;
		Scene* _scene;
		irr::scene::ISceneManager* _smgr;


		unsigned int _damage;
		bool _hasAnIrrlichtNode;
		int _id;
};

#endif