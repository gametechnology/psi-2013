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

	virtual void init() = 0;
	virtual void handleMessage(unsigned int message, void* data) = 0;
	virtual void update() = 0;

};

#endif

