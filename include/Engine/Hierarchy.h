#ifndef HIERARCHY
#define HIERARCHY

#include <Engine\Entity.h>

//Hierarchy class that can visualize the inner hierarchy of an entity by Simon Karman
class Hierarchy
{
public:
	static void Visualize(Entity* entity);
private:
	static void Visualize(Entity* entity, std::string prefix);
};

#endif