#ifndef COMPONENT
#define COMPONENT

using namespace std;

class Composite;

class Component
{
public:
	Component();
	Component(Composite* parent);
	virtual ~Component() = 0;

	Composite* parent;

	virtual void Init() = 0;
	virtual void HandleMessage(unsigned int message, void* data) = 0;
	virtual void Update() = 0;

};

#endif

