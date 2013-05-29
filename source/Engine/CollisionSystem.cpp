#include <Engine\CollisionSystem.h>

CollisionSystem::CollisionSystem() : Composite("CollisionSystem")
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update()
{
	for (std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		for (std::list<Component*>::iterator j = components.begin(); j != components.end(); ++j)
		{
			if(*i == *j)
				continue;
			narrowPhaseDetection((GameObject*)*i, (GameObject*)*j);
		}
	}
}

void CollisionSystem::registerComponent(GameObject* object)
{
	Composite::addComponent(object);
}

void CollisionSystem::unregisterComponent(GameObject* object)
{
	Composite::addComponent(object);
}

void CollisionSystem::narrowPhaseDetection(GameObject* objectA, GameObject* objectB)
{
	if(objectA->isEnabled() && objectB->isEnabled())
	{
		float distance = objectA->getPosition()->getDistanceFrom(*objectB->getPosition());
		if (distance < (objectA->getRadius()->Z + objectB->getRadius()->Z))
		{
			if (distance < (objectA->getRadius()->X + objectB->getRadius()->X ) )
			{
				objectA->contactResolver(objectB);
				return;
			}

			irr::core::vector3df* boxA = createBoundingBox(objectA);
			irr::core::vector3df* boxB = createBoundingBox(objectB);

			for (int k = 0; k < 8; k++)
			{
				for (int l = 0; l < 8; l++)
				{
					if (boxA[k].X > boxB[l].X - objectA->getRadius()->X ||
						boxA[k].Y > boxB[l].Y - objectA->getRadius()->X ||
						boxA[k].Z > boxB[l].Z - objectA->getRadius()->X ||
						boxB[k].X > boxA[l].X - objectA->getRadius()->X ||
						boxB[k].Y > boxA[l].Y - objectA->getRadius()->X ||
						boxB[k].Z > boxA[l].Z - objectA->getRadius()->X 
					)
					{
						objectA->contactResolver(objectB);
					}
				}
			}
		}
		else
		{
			objectA->getRadius()->X = (objectA->getRadius()->Y);
		}
	}
}

irr::core::vector3df* CollisionSystem::createBoundingBox(GameObject* object)
{
	irr::core::vector3df* box = new irr::core::vector3df[8];

	box[0] = irr::core::vector3df(object->getPosition()->X - object->getRadius()->X, 
		object->getPosition()->Y + object->getRadius()->X,
		object->getPosition()->Z + object->getRadius()->X);
	box[1] = irr::core::vector3df(object->getPosition()->X + object->getRadius()->X,
		object->getPosition()->Y - object->getRadius()->X,
		object->getPosition()->Z + object->getRadius()->X);
	box[2] = irr::core::vector3df(object->getPosition()->X + object->getRadius()->X,
		object->getPosition()->Y + object->getRadius()->X,
		object->getPosition()->Z + object->getRadius()->X);
	box[3] = irr::core::vector3df(object->getPosition()->X - object->getRadius()->X,
		object->getPosition()->Y - object->getRadius()->X,
		object->getPosition()->Z + object->getRadius()->X);
	box[4] = irr::core::vector3df(object->getPosition()->X - object->getRadius()->X,
		object->getPosition()->Y + object->getRadius()->X,
		object->getPosition()->Z - object->getRadius()->X);
	box[5] = irr::core::vector3df(object->getPosition()->X + object->getRadius()->X,
		object->getPosition()->Y - object->getRadius()->X,
		object->getPosition()->Z - object->getRadius()->X);
	box[6] = irr::core::vector3df(object->getPosition()->X + object->getRadius()->X,
		object->getPosition()->Y + object->getRadius()->X,
		object->getPosition()->Z - object->getRadius()->X);
	box[7] = irr::core::vector3df(object->getPosition()->X - object->getRadius()->X,
		object->getPosition()->Y - object->getRadius()->X,
		object->getPosition()->Z - object->getRadius()->X);

	return box;
}

irr::core::vector3df CollisionSystem::componentOnto(irr::core::vector3df input, irr::core::vector3df deltavelocity)
{
	return input * (deltavelocity.dotProduct(input) / input.getLengthSQ());
}