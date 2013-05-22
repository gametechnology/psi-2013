#ifndef ENTITY_DUMMYSHIP
#define ENTITY_DUMMYSHIP
#include "Irrlicht\irrlicht.h"

#include "Engine/Entity.h"
#include "Engine/IrrlichtNode.h"
#include "Player.h"
#include "Engine/Input.h"
#include "ShipMover.h"
#include "Enemy.h"


class DummyShip : public Enemy
{
public:
	DummyShip(vector3df position);
	virtual ~DummyShip(void);
	
	void onAdd();
	void init();
	void update();
	void draw();

	vector3df startPosition;
	vector3df startRotation;

	irr::gui::IGUIEnvironment *env;
	void contactResolverA(Entity* input);

	irr::gui::IGUIStaticText *shipHealth;
private:
	matrix4				*_inertiaMatrix;

	stringw varToString(stringw str1, float var, stringw str2);
	stringw varToString(stringw str1, float var);

	void setInertiaMatrix(float h, float w, float d, float m);
};
#endif