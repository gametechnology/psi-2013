#ifndef Enemy_h
#define Enemy_h

#include "Engine/Entity.h"
#include "Engine/Game.h"
#include "ArrayList.h"
#include "Player.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Enemy : public Entity
{
public:
	Enemy(void);
	Enemy(ISceneManager* smgr, IMesh* mesh,				// using default parameters allows 
		vector3df position = vector3df(0,0,0),			// maximum flexibility with the constructor but everything left 
		vector3df rotation = vector3df(0,0,0),			// open or not required can still be set by using the set methods.
		unsigned int maxspeed = 1,						// 
		unsigned int agility = 1,						//
		vector3df acc = vector3df(0,0,0),			//
		unsigned int damage = 1,						//
		unsigned int los = 1,							//
		unsigned int health = 1);						//
	~Enemy(void);

	bool isWithinLoS(/*playership class*/);

	array<Entity*> inRangeList;

	void setVisual(IMesh* visual, ISceneManager* smgr);	// visuals are the only component which do not have a get method
	void setVisualWithPath(std::string);
	void setPath(vector3df destination);
	void setPosition(vector3df position);
	void setRotation(vector3df rotategoal);
	void setMaxSpeed(unsigned int maxspeed);
	void setAgility(unsigned int agility);
	void setAccelaration(vector3df acc);
	void setDamage(unsigned int damage);
	void setLoS(unsigned int los);
	void setHealth(signed int health);
	void setMaxHealth(unsigned int maxhealth);
	void setVelocity(vector3df input);
	void setRadius(unsigned int radius);
	
	vector3df getVelocity();
	vector3df getPath();
	vector3df getPosition();
	vector3df getRotation();
	unsigned int getMaxSpeed();
	unsigned int getAgility();
	vector3df getAccelaration();
	unsigned int getDamage();
	unsigned int getLoS();
	unsigned int getRadius();
	void chase(vector3df target);

	void contactGenerator(Player* input);
	void contactGenerator(Enemy* input);
	void contactResolverA();
	void contactResolverB();
	void steering();
	signed int getHealth();
	unsigned int getMaxHealth();

	virtual void update();

protected:


private:
	
	void applySpeed();

	void pathFinding();
	
	IMesh* visual_;
	vector3df destination_;

	signed int health_;
	unsigned int maxhealth_;
	unsigned int radius_;
	unsigned int maxspeed_;
	unsigned int agility_;
	unsigned int accelaration_;
	unsigned int damage_;
	unsigned int lineofsightrange_;

};
#endif
