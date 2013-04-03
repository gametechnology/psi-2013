#include "Engine\Entity.h"
#include "Engine\Game.h"


Entity::Entity(Composite* parent):Composite(parent)
{
	this->mass = 1;
	node = NULL;
}

void Entity::update()
{
	Composite::update();

	this->angularVelocity += this->angularAccelaration;
	this->orientation += this->angularVelocity;

	this->accelaration = (1 / this->mass) * this->force;
	this->velocity += this->accelaration;
	this->position += this->velocity;
	if (node != NULL)
	{
		this->node->setPosition(this->position);
		this->node->setRotation(this->orientation);
	}
}

void Entity::draw()
{
	Composite::draw();

	if (node == NULL) return;
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
	//Entity* tempModel = new Entity(parent);
	this->node = Game::getSceneManager()->addMeshSceneNode( mesh );
	//Game::getCurrentScene()->addComponent(tempModel);
}

Entity::~Entity()
{
	Composite::~Composite();
	if (node != NULL)
	{
		node->drop();
	}
}