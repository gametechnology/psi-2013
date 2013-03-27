#ifndef Enemy_h
#define Enemy_h

#include "irrlicht.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Enemy
{
public:
	Enemy(void);
	Enemy(ISceneManager* smgr, IMesh* mesh,				// using default parameters allows 
		vector3df position = vector3df(0,0,0),			// maximum flexibility with the constructor but everything left 
		vector3df rotation = vector3df(0,0,0),			// open or not required can still be set by using the set methods.
		unsigned int maxspeed = 1,						// 
		unsigned int agility = 1,						//
		unsigned int maxacc = 1,						//
		unsigned int damage = 1,						//
		unsigned int los = 1,							//
		unsigned int health = 1);						//
	~Enemy(void);

	bool isWithinLoS(/*playership class*/);

	void setState();
	void getState();

	void setVisual(IMesh* visual, ISceneManager* smgr);	// visuals are the only component which do not have a get method

	void setPath(vector3df destination);
	void setPosition(vector3df position);
	void setRotation(vector3df rotategoal);
	void setMaxSpeed(unsigned int maxspeed);
	void setAgility(unsigned int agility);
	void setMaxAccelaration(unsigned int maxacc);
	void setDamage(unsigned int damage);
	void setLoS(unsigned int los);

	void setHealth(signed int health);

	vector3df getPath();
	vector3df getPosition();
	vector3df getRotation();
	unsigned int getMaxSpeed();
	unsigned int getAgility();
	unsigned int getMaxAccelaration();
	unsigned int getDamage();
	unsigned int getLoS();

	signed int getHealth();

	void update();
protected:
private:
	
	void applySpeed();
	void steeRing();
	void contactResolverB();
	void contactResolverA();
	void contactGenerator();
	void pathFinding();
	
	IMesh* visual_;
	vector3df position_;
	vector3df rotation_;
	vector3df destination_;
	vector3df velocity_;
	vector3df accelaration_;

	signed int health_;
	unsigned int maxspeed_;
	unsigned int agility_;
	unsigned int maxaccelaration_;
	unsigned int damage_;
	unsigned int lineofsightrange_;

};
#endif Enemy_h
