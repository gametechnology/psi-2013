#include "HelmSceneTest.h"
#include "HelmStation.h"
#include "Engine/Camera.h"
#include "Ship.h"
#include "ShipMover.h"
#include "Skybox.h"
#include "Engine\Camera.h"

HelmSceneTest::HelmSceneTest(void)
{
}


HelmSceneTest::~HelmSceneTest(void)
{
	Scene::~Scene();
}

void HelmSceneTest::init()
{
	char station;
	bool Isweapon = false;

	while(true)
	{
		std::cout << "helm station? y is helm, n is weapon" << std::endl;
		std::cin >> station;

		if(station == 'y')
		{
			Isweapon = false;
			break;
		}
		else if(station == 'n')
		{
			Isweapon = true;
			break;
		}
	}

	//Net::ipadress = sf::IPAddress(test);

	//Entity* cube = new Entity(this);
	//cube->createNode("../../assets/Models/Cube.3ds");
	//cube->angularVelocity = vector3df(0.01, 0,0);
	//addComponent(cube);

	Skybox* skyBox = new Skybox(this);


	//Ship* ship = new Ship(this, vector3df(0, 0.001,-0.001), vector3df(0,0,0));
	Ship* ship = new Ship(this, vector3df(0,0,-5), vector3df(0,0,0));
	ship->position = vector3df(0, 0, -5);
	addComponent(ship);
	if(Isweapon)
		ship->init(1);
	else
		ship->init(0);
	//ship->velocity = vector3df(0,0.001,0 );
	//network = Net(false, camera);
}