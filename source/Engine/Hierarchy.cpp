#include "../include/Engine/Hierarchy.h"
#include "../include/Engine/Entity.h"

#include <iostream>
using namespace std;

//Hierarchy class that can visualize the inner hierarchy of an entity by Simon Karman
void Hierarchy::Visualize(Entity* entity)
{
	cout << "\n\n-----------------------------------------------------\n\n" << endl;
	cout << "Visualized Entity:\n" << endl;
	Visualize(entity, "");
}

void Hierarchy::Visualize(Entity* entity, string prefix)
{
	cout << prefix << "--" << typeid(*entity).name() << endl;
	//Components
	cout << prefix << "  | [";
	bool first = true;
	for (unsigned int i = 0; i < entity->components.size(); i++) {
		if (!first)
			cout << ", ";
		cout << typeid(*(entity->components[i])).name();
		first = false;
	}
	cout <<"]" << endl;
	//Children
	for (unsigned int i = 0; i < entity->children.size(); i++)
		Hierarchy::Visualize(entity->children[i], prefix + "  |");
}