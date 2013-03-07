#ifndef COMPONENT
#define COMPONENT

using namespace std;

class Composite;

class Component
{
public:
	Component();
	Component(Composite* parent);
	~Component();

	Composite* parent;

	virtual void Init();
	virtual void HandleMessage(unsigned int message, void* data );
	virtual void Update();


};

#endif

