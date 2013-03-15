#ifndef COMPONENT
#define COMPONENT


class Composite;

class Component
{
public:
	Component(Composite* parent);
	virtual ~Component() = 0;

	virtual void init() {};
	virtual void update() = 0;
	virtual void handleMessage(unsigned int message, void* data) = 0;
protected:
	Composite* parent;
};


#endif

