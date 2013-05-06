#include "Engine\CollisionSystem.h"
#include "Engine\Collision.h"

CollisionSystem::CollisionSystem()
{
	listeners = vector<Entity*>();
}

void CollisionSystem::update()
{
	handleCollision();
}

bool CollisionSystem::isNotAdded(Entity* entity)
{
	for(int i = 0; i < listeners.size(); i++)
	{
		if(listeners[i] == entity)
		{
			return false;
		}
	}
	return true;
}

void CollisionSystem::addListener(Entity* entity)
{
	if(isNotAdded(entity))
	{
		listeners.push_back(entity);
	}
}

void CollisionSystem::removeListener(Entity* entity)
{
	for(int i = 0; i < listeners.size(); i++)
	{
		if(listeners[i] == entity)
		{
			listeners.erase(listeners.begin() + i);
		}
	}
}

void CollisionSystem::handleCollision()
{
	if(listeners.size() > 1)
	{
		Collision::NarrowPhaseDetection(listeners);
	}
}

CollisionSystem::~CollisionSystem()
{

}