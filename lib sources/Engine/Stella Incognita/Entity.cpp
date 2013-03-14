#include "Entity.h"
#include "Game.h"


Entity::Entity(Composite* parent):Composite(parent)
{
	this->mass = 1;
}

void Entity::update()
{
	Composite::update();

	//this->angularAccelaration = ();
	this->angularVelocity += this->angularAccelaration;
	this->orientation += this->angularVelocity;

	this->accelaration = (1 / this->mass) * this->force;
	this->velocity += this->accelaration;
	this->position += this->velocity;

	//this->node->setPosition(this->position);
	//this->node->setRotation(this->orientation);
}

void Entity::draw()
{
	if (!this->visible)
	{
		this->node->setVisible(false);
		return;
	}
	this->node->setVisible(true);

	this->node->render();
}

void Entity::createNode(std::string modelPath)
{
	// Get the mesh
	irr::scene::IAnimatedMesh* mesh = Game::getSceneManager()->getMesh(modelPath.c_str());

	// Create model entity
	Entity* tempModel = new Entity(parent);
	tempModel->node =  Game::getSceneManager()->addMeshSceneNode( mesh );
	Game::getCurrentScene()->addComponent(tempModel);
}

Entity::~Entity()
{
	delete node;
}