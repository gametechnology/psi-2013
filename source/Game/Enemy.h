#ifndef Enemy_h
#define Enemy_h

#include "Engine/Entity.h"
#include "Engine/Game.h"

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
		vector3df maxacc = vector3df(0,0,0),			//
		unsigned int damage = 1,						//
		unsigned int los = 1,							//
		unsigned int health = 1);						//
	~Enemy(void);

	bool isWithinLoS(/*playership class*/);

	void setState();
	void getState();

	void setVelocity(vector3df input);

	void setVisual(IMesh* visual, ISceneManager* smgr);	// visuals are the only component which do not have a get method
	void setVisualWithPath(std::string);
	void setPath(vector3df destination);
	void setPosition(vector3df position);
	void setRotation(vector3df rotategoal);
	void setMaxSpeed(unsigned int maxspeed);
	void setAgility(unsigned int agility);
	void setAccelaration(vector3df maxacc);
	void setDamage(unsigned int damage);
	void setLoS(unsigned int los);
	void setHealth(signed int health);
	void setVelocity(vector3df input);
	void setRadius(unsigned int radius);
	
	vector3df getVelocity();
	vector3df getPath();
	vector3df getPosition();
	vector3df getRotation();
	unsigned int getMaxSpeed();
	unsigned int getAgility();
	unsigned int getAccelaration();
	unsigned int getDamage();
	unsigned int getLoS();
	unsigned int getRadius();
	void chase(vector3df target);

	void contactGenerator(Enemy* input);
	void contactResolverA(Enemy input);
	void contactResolverB();

	signed int getHealth();

	virtual void update();
protected:
private:
	
	void applySpeed();
	void steeRing();

	void pathFinding();
	
	IMesh* visual_;
	vector3df destination_;

	signed int health_;
	unsigned int radius_;
	unsigned int maxspeed_;
	unsigned int agility_;
	unsigned int damage_;
	unsigned int lineofsightrange_;

};
#endif