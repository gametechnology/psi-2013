#include "Engine\Collision.h"


Collision::Collision(void)
{
}


Collision::~Collision(void)
{
}
/*
void Collision::LaserNarrowPhase(vector<Enemy*> _enput, vector<Laser*> _laput)
{
	for (int i = 0; i < (int)(_laput.size()); i++)
	{
		for(int j = 0; j < (int)(_enput.size()); j++)
		{
			float distance = _laput[i]->transform->position->getDistanceFrom(vector3df(_enput[j]->transform->position->X,_enput[j]->transform->position->Y,_enput[j]->transform->position->Z));
			if (distance < (_enput[j]->getRadius()))
			{
				_laput[i]->contactResolverA(_enput[j]);
			}
		}
	}
}

void Collision::NarrowPhaseDetection(vector<Enemy*> _input)
{
	vector<Laser*> laserlist;
	for(int i = 0; i < (int)(_input.size()); i++)
	{
		for(int j = i; j < (int)(_input.size()); j++)
		{
			if(i != j)
			{
				float distance = _input[i]->transform->position->getDistanceFrom(vector3df(_input[j]->transform->position->X,_input[j]->transform->position->Y,_input[j]->transform->position->Z));
				if (distance < (_input[i]->getOuterRadius() + _input[j]->getOuterRadius()))
				{
					if (distance < (_input[i]->getRadius() + _input[j]->getRadius() ) )
					{
						_input[i]->contactResolverA(_input[j]);
						continue;
					}
					irr::core::vector3df box1[8];
					irr::core::vector3df box2[8];

					box1[0] = vector3df(_input[i]->getPosition().X-_input[i]->getRadius(),_input[i]->getPosition().Y+_input[i]->getRadius(),_input[i]->getPosition().Z+_input[i]->getRadius());
					box1[1] = vector3df(_input[i]->getPosition().X+_input[i]->getRadius(),_input[i]->getPosition().Y-_input[i]->getRadius(),_input[i]->getPosition().Z+_input[i]->getRadius());
					box1[2] = vector3df(_input[i]->getPosition().X+_input[i]->getRadius(),_input[i]->getPosition().Y+_input[i]->getRadius(),_input[i]->getPosition().Z+_input[i]->getRadius());
					box1[3] = vector3df(_input[i]->getPosition().X-_input[i]->getRadius(),_input[i]->getPosition().Y-_input[i]->getRadius(),_input[i]->getPosition().Z+_input[i]->getRadius());
					box1[4] = vector3df(_input[i]->getPosition().X-_input[i]->getRadius(),_input[i]->getPosition().Y+_input[i]->getRadius(),_input[i]->getPosition().Z-_input[i]->getRadius());
					box1[5] = vector3df(_input[i]->getPosition().X+_input[i]->getRadius(),_input[i]->getPosition().Y-_input[i]->getRadius(),_input[i]->getPosition().Z-_input[i]->getRadius());
					box1[6] = vector3df(_input[i]->getPosition().X+_input[i]->getRadius(),_input[i]->getPosition().Y+_input[i]->getRadius(),_input[i]->getPosition().Z-_input[i]->getRadius());
					box1[7] = vector3df(_input[i]->getPosition().X-_input[i]->getRadius(),_input[i]->getPosition().Y-_input[i]->getRadius(),_input[i]->getPosition().Z-_input[i]->getRadius());

					box2[0] = vector3df(_input[j]->getPosition().X-_input[j]->getRadius(),_input[j]->getPosition().Y+_input[j]->getRadius(),_input[j]->getPosition().Z+_input[j]->getRadius());
					box2[1] = vector3df(_input[j]->getPosition().X+_input[j]->getRadius(),_input[j]->getPosition().Y-_input[j]->getRadius(),_input[j]->getPosition().Z+_input[j]->getRadius());
					box2[2] = vector3df(_input[j]->getPosition().X+_input[j]->getRadius(),_input[j]->getPosition().Y+_input[j]->getRadius(),_input[j]->getPosition().Z+_input[j]->getRadius());
					box2[3] = vector3df(_input[j]->getPosition().X-_input[j]->getRadius(),_input[j]->getPosition().Y-_input[j]->getRadius(),_input[j]->getPosition().Z+_input[j]->getRadius());
					box2[4] = vector3df(_input[j]->getPosition().X-_input[j]->getRadius(),_input[j]->getPosition().Y+_input[j]->getRadius(),_input[j]->getPosition().Z-_input[j]->getRadius());
					box2[5] = vector3df(_input[j]->getPosition().X+_input[j]->getRadius(),_input[j]->getPosition().Y-_input[j]->getRadius(),_input[j]->getPosition().Z-_input[j]->getRadius());
					box2[6] = vector3df(_input[j]->getPosition().X+_input[j]->getRadius(),_input[j]->getPosition().Y+_input[j]->getRadius(),_input[j]->getPosition().Z-_input[j]->getRadius());
					box2[7] = vector3df(_input[j]->getPosition().X-_input[j]->getRadius(),_input[j]->getPosition().Y-_input[j]->getRadius(),_input[j]->getPosition().Z-_input[j]->getRadius());
					
					for (int k = 0; k < 8; k++)
					{
						for (int l = 0; l < 8; l++)
						{
							if (box1[k].X > box2[l].X - _input[i]->getRadius()||
								box1[k].Y > box2[l].Y - _input[i]->getRadius()||
								box1[k].Z > box2[l].Z - _input[i]->getRadius()||
								box2[k].X > box1[l].X - _input[i]->getRadius()||
								box2[k].Y > box1[l].Y - _input[i]->getRadius()||
								box2[k].Z > box1[l].Z - _input[i]->getRadius() 
								)
							{
								_input[i]->contactResolverA(_input[j]);
							}
						}
					}
				}
				else
				{
					_input[i]->setRadius(_input[i]->getOriginalRadius());
				}
			}
		}
		if(dynamic_cast<EnemyFighter*>(_input[i]))
		{
			EnemyFighter* temp = (EnemyFighter*) _input[i];
			if (!temp->GetLasers().empty())
			{
				for (int k = 0; k < temp->GetLasers().size(); k++)
				{
					laserlist.push_back(temp->GetLasers()[k]);
				}
			}
		}
	}
	if (!laserlist.empty())
	{
		LaserNarrowPhase(_input, laserlist);
	}
 //float distance = position.getDistanceFrom(input->getPosition());
 //float radii = input->getRadius() + radius_;
 //if (distance < radii)
 //{
 // contactResolverB();
 //}
}
*/
void Collision::NarrowPhaseDetection(vector<Entity*> _input)
{
	for(int i = 0; i < (int)(_input.size()); i++)
	{
		for(int j = i; j < (int)(_input.size()); j++)
		{
			if(i != j)
			{
				float distance = _input[i]->transform->position->getDistanceFrom(irr::core::vector3df(_input[j]->transform->position->X,_input[j]->transform->position->Y,_input[j]->transform->position->Z));
				if (distance < (_input[i]->transform->radii->Z + _input[j]->transform->radii->Z))
				{
					if (distance < (_input[i]->transform->radii->X + _input[j]->transform->radii->X ) )
					{
						_input[i]->contactResolverA(_input[j]);
						continue;
					}
					irr::core::vector3df box1[8];
					irr::core::vector3df box2[8];

					box1[0] = irr::core::vector3df(_input[i]->transform->position->X-_input[i]->transform->radii->X,_input[i]->transform->position->Y+_input[i]->transform->radii->X,_input[i]->transform->position->Z+_input[i]->transform->radii->X);
					box1[1] = irr::core::vector3df(_input[i]->transform->position->X+_input[i]->transform->radii->X,_input[i]->transform->position->Y-_input[i]->transform->radii->X,_input[i]->transform->position->Z+_input[i]->transform->radii->X);
					box1[2] = irr::core::vector3df(_input[i]->transform->position->X+_input[i]->transform->radii->X,_input[i]->transform->position->Y+_input[i]->transform->radii->X,_input[i]->transform->position->Z+_input[i]->transform->radii->X);
					box1[3] = irr::core::vector3df(_input[i]->transform->position->X-_input[i]->transform->radii->X,_input[i]->transform->position->Y-_input[i]->transform->radii->X,_input[i]->transform->position->Z+_input[i]->transform->radii->X);
					box1[4] = irr::core::vector3df(_input[i]->transform->position->X-_input[i]->transform->radii->X,_input[i]->transform->position->Y+_input[i]->transform->radii->X,_input[i]->transform->position->Z-_input[i]->transform->radii->X);
					box1[5] = irr::core::vector3df(_input[i]->transform->position->X+_input[i]->transform->radii->X,_input[i]->transform->position->Y-_input[i]->transform->radii->X,_input[i]->transform->position->Z-_input[i]->transform->radii->X);
					box1[6] = irr::core::vector3df(_input[i]->transform->position->X+_input[i]->transform->radii->X,_input[i]->transform->position->Y+_input[i]->transform->radii->X,_input[i]->transform->position->Z-_input[i]->transform->radii->X);
					box1[7] = irr::core::vector3df(_input[i]->transform->position->X-_input[i]->transform->radii->X,_input[i]->transform->position->Y-_input[i]->transform->radii->X,_input[i]->transform->position->Z-_input[i]->transform->radii->X);

					box2[0] = irr::core::vector3df(_input[j]->transform->position->X-_input[j]->transform->radii->X,_input[j]->transform->position->Y+_input[j]->transform->radii->X,_input[j]->transform->position->Z+_input[j]->transform->radii->X);
					box2[1] = irr::core::vector3df(_input[j]->transform->position->X+_input[j]->transform->radii->X,_input[j]->transform->position->Y-_input[j]->transform->radii->X,_input[j]->transform->position->Z+_input[j]->transform->radii->X);
					box2[2] = irr::core::vector3df(_input[j]->transform->position->X+_input[j]->transform->radii->X,_input[j]->transform->position->Y+_input[j]->transform->radii->X,_input[j]->transform->position->Z+_input[j]->transform->radii->X);
					box2[3] = irr::core::vector3df(_input[j]->transform->position->X-_input[j]->transform->radii->X,_input[j]->transform->position->Y-_input[j]->transform->radii->X,_input[j]->transform->position->Z+_input[j]->transform->radii->X);
					box2[4] = irr::core::vector3df(_input[j]->transform->position->X-_input[j]->transform->radii->X,_input[j]->transform->position->Y+_input[j]->transform->radii->X,_input[j]->transform->position->Z-_input[j]->transform->radii->X);
					box2[5] = irr::core::vector3df(_input[j]->transform->position->X+_input[j]->transform->radii->X,_input[j]->transform->position->Y-_input[j]->transform->radii->X,_input[j]->transform->position->Z-_input[j]->transform->radii->X);
					box2[6] = irr::core::vector3df(_input[j]->transform->position->X+_input[j]->transform->radii->X,_input[j]->transform->position->Y+_input[j]->transform->radii->X,_input[j]->transform->position->Z-_input[j]->transform->radii->X);
					box2[7] = irr::core::vector3df(_input[j]->transform->position->X-_input[j]->transform->radii->X,_input[j]->transform->position->Y-_input[j]->transform->radii->X,_input[j]->transform->position->Z-_input[j]->transform->radii->X);
					
					for (int k = 0; k < 8; k++)
					{
						for (int l = 0; l < 8; l++)
						{
							if (box1[k].X > box2[l].X - _input[i]->transform->radii->X||
								box1[k].Y > box2[l].Y - _input[i]->transform->radii->X||
								box1[k].Z > box2[l].Z - _input[i]->transform->radii->X||
								box2[k].X > box1[l].X - _input[i]->transform->radii->X||
								box2[k].Y > box1[l].Y - _input[i]->transform->radii->X||
								box2[k].Z > box1[l].Z - _input[i]->transform->radii->X 
								)
							{
								_input[i]->contactResolverA(_input[j]);
							}
						}
					}
				}
				else
				{
					_input[i]->transform->radii->X = (_input[i]->transform->radii->Y);
				}
			}
		}
	}
}

irr::core::vector3df Collision::componentOnto(irr::core::vector3df input, irr::core::vector3df deltavelocity)
{
	return input * (deltavelocity.dotProduct(input) / input.getLengthSQ());
}