#ifndef Enemy_h
#define Enemy_h

#include "Engine/Entity.h"
#include "Engine/Game.h"
#include "ArrayList.h"
#include "Player.h"
#include "NetworkInterface.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Enemy : public Entity, public INetworkListener
{
public:
	static int newEnemyId;

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

	typedef enum {
		ASTROID = 0,

		DRONE = 1,

		FIGHTER = 2
	} EnemyType;

	bool isWithinLoS(/*playership class*/);

	array<Entity*> inRangeList;
	virtual void destroy();
	void HandleNetworkMessage(NetworkPacket packet);

	void setVisual(IMesh* visual, ISceneManager* smgr);	// visuals are the only component which do not have a get method
	void setVisualWithPath(const irr::io::path& path);
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
	void setRadius(float radius);
	void setOriginalRadius(float origradius);
	void setOuterRadius(float outerradius);
	void setOriginalVelocity(vector3df origvelocity);
	void setType(EnemyType type);

	//it can only be set as a client, the server makes their own id.
	void setId(int id);
	
	vector3df getVelocity();
	vector3df getPath();
	vector3df getPosition();
	vector3df getRotation();
	unsigned int getMaxSpeed();
	unsigned int getAgility();
	vector3df getAccelaration();
	unsigned int getDamage();
	unsigned int getLoS();
	float getRadius();
	float getOriginalRadius();
	float getOuterRadius();
	vector3df getTarget();
	vector3df getOriginalVelocity();
	void chase(vector3df target);
	void flee(vector3df target);
	void setTarget(vector3df target);
	void receiveDamage(int damage);

	/*void contactGenerator(Player* input);*/
	void contactGenerator(Enemy* input);
	void contactResolverA(Enemy* _input);
	void contactResolverB();
	void steering(irr::core::vector3df rotational, irr::core::vector3df playerPos);
	void wander();
	int getHealth();
	int getMaxHealth();
	int getId();
	bool isAlive();
	EnemyType getType();

	void updateHealth();
	virtual void update();

	

protected:
	EnemyType _type;

private:
	
	void applySpeed();

	void pathFinding();
	
	IMesh* visual_;
	vector3df destination_;
	vector3df originalvelocity_;
	signed int _health;
	unsigned int _maxHealth;
	float radius_;
	float originalradius_;
	float outerradius_;
	unsigned int maxspeed_;
	unsigned int agility_;
	unsigned int accelaration_;
	unsigned int damage_;
	unsigned int lineofsightrange_;
	vector3df _target;
	int _wanderTime;
	bool _isAlive;

	int _id;

	int healthTimer;
	vector3df componentOnto(vector3df input, vector3df deltavelocity);
};
#endif
