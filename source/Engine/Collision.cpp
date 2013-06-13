#include "Engine\Collision.h"
#include "Engine\Game.h"


Collision::Collision(void) : Component()
{
	
}

void Collision::onAdd()
{
	Component::onAdd();
	Game::collisionSystem->addListener(this->entity);
}

Collision::~Collision(void)
{
	Game::collisionSystem->removeListener(this->entity);
}


void Collision::NarrowPhaseDetection(vector<Entity*> _input)
{
	for(int i = 0; i < (int)(_input.size()); i++)
	{
		for(int j = 0; j < (int)(_input.size()); j++)
		{
			if(i != j && (_input[i]->enabled && _input[j]->enabled) && (!_input[i]->destroyed && !_input[j]->destroyed))
			{
				float distance = _input[i]->transform->position.getDistanceFrom(irr::core::vector3df(_input[j]->transform->position.X,_input[j]->transform->position.Y,_input[j]->transform->position.Z));
				if (distance < (_input[i]->transform->radii.Z + _input[j]->transform->radii.Z))
				{
					if (distance < (_input[i]->transform->radii.X + _input[j]->transform->radii.X ) )
					{
						_input[i]->contactResolverA(_input[j]);
						continue;
					}
					irr::core::vector3df box1[8];
					irr::core::vector3df box2[8];

					box1[0] = irr::core::vector3df(_input[i]->transform->position.X-_input[i]->transform->radii.X,_input[i]->transform->position.Y+_input[i]->transform->radii.X,_input[i]->transform->position.Z+_input[i]->transform->radii.X);
					box1[1] = irr::core::vector3df(_input[i]->transform->position.X+_input[i]->transform->radii.X,_input[i]->transform->position.Y-_input[i]->transform->radii.X,_input[i]->transform->position.Z+_input[i]->transform->radii.X);
					box1[2] = irr::core::vector3df(_input[i]->transform->position.X+_input[i]->transform->radii.X,_input[i]->transform->position.Y+_input[i]->transform->radii.X,_input[i]->transform->position.Z+_input[i]->transform->radii.X);
					box1[3] = irr::core::vector3df(_input[i]->transform->position.X-_input[i]->transform->radii.X,_input[i]->transform->position.Y-_input[i]->transform->radii.X,_input[i]->transform->position.Z+_input[i]->transform->radii.X);
					box1[4] = irr::core::vector3df(_input[i]->transform->position.X-_input[i]->transform->radii.X,_input[i]->transform->position.Y+_input[i]->transform->radii.X,_input[i]->transform->position.Z-_input[i]->transform->radii.X);
					box1[5] = irr::core::vector3df(_input[i]->transform->position.X+_input[i]->transform->radii.X,_input[i]->transform->position.Y-_input[i]->transform->radii.X,_input[i]->transform->position.Z-_input[i]->transform->radii.X);
					box1[6] = irr::core::vector3df(_input[i]->transform->position.X+_input[i]->transform->radii.X,_input[i]->transform->position.Y+_input[i]->transform->radii.X,_input[i]->transform->position.Z-_input[i]->transform->radii.X);
					box1[7] = irr::core::vector3df(_input[i]->transform->position.X-_input[i]->transform->radii.X,_input[i]->transform->position.Y-_input[i]->transform->radii.X,_input[i]->transform->position.Z-_input[i]->transform->radii.X);

					box2[0] = irr::core::vector3df(_input[j]->transform->position.X-_input[j]->transform->radii.X,_input[j]->transform->position.Y+_input[j]->transform->radii.X,_input[j]->transform->position.Z+_input[j]->transform->radii.X);
					box2[1] = irr::core::vector3df(_input[j]->transform->position.X+_input[j]->transform->radii.X,_input[j]->transform->position.Y-_input[j]->transform->radii.X,_input[j]->transform->position.Z+_input[j]->transform->radii.X);
					box2[2] = irr::core::vector3df(_input[j]->transform->position.X+_input[j]->transform->radii.X,_input[j]->transform->position.Y+_input[j]->transform->radii.X,_input[j]->transform->position.Z+_input[j]->transform->radii.X);
					box2[3] = irr::core::vector3df(_input[j]->transform->position.X-_input[j]->transform->radii.X,_input[j]->transform->position.Y-_input[j]->transform->radii.X,_input[j]->transform->position.Z+_input[j]->transform->radii.X);
					box2[4] = irr::core::vector3df(_input[j]->transform->position.X-_input[j]->transform->radii.X,_input[j]->transform->position.Y+_input[j]->transform->radii.X,_input[j]->transform->position.Z-_input[j]->transform->radii.X);
					box2[5] = irr::core::vector3df(_input[j]->transform->position.X+_input[j]->transform->radii.X,_input[j]->transform->position.Y-_input[j]->transform->radii.X,_input[j]->transform->position.Z-_input[j]->transform->radii.X);
					box2[6] = irr::core::vector3df(_input[j]->transform->position.X+_input[j]->transform->radii.X,_input[j]->transform->position.Y+_input[j]->transform->radii.X,_input[j]->transform->position.Z-_input[j]->transform->radii.X);
					box2[7] = irr::core::vector3df(_input[j]->transform->position.X-_input[j]->transform->radii.X,_input[j]->transform->position.Y-_input[j]->transform->radii.X,_input[j]->transform->position.Z-_input[j]->transform->radii.X);
					
					for (int k = 0; k < 8; k++)
					{
						for (int l = 0; l < 8; l++)
						{
							if (box1[k].X > box2[l].X - _input[i]->transform->radii.X||
								box1[k].Y > box2[l].Y - _input[i]->transform->radii.X||
								box1[k].Z > box2[l].Z - _input[i]->transform->radii.X||
								box2[k].X > box1[l].X - _input[i]->transform->radii.X||
								box2[k].Y > box1[l].Y - _input[i]->transform->radii.X||
								box2[k].Z > box1[l].Z - _input[i]->transform->radii.X 
								)
							{
								_input[i]->contactResolverA(_input[j]);
							}
						}
					}
				}
				else
				{
					_input[i]->transform->radii.X = (_input[i]->transform->radii.Y);
				}
			}
		}
	}
}

irr::core::vector3df Collision::componentOnto(irr::core::vector3df input, irr::core::vector3df deltavelocity)
{
	return input * (deltavelocity.dotProduct(input) / input.getLengthSQ());
}