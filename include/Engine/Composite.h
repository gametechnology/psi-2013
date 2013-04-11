#include <vector>
#include <array>

#ifndef COMPOSITE
#define COMPOSITE

class Composite
{
public:
	Composite();
	virtual ~Composite();
	
	bool initialized;
	bool destroyed;
	bool enabled;
	
	virtual void onAdd();
	virtual void init();
	virtual void update();
	virtual void draw();

	virtual void handleMessage(unsigned int message);

	virtual void disable();
	virtual void enable();
	virtual void destroy();
};

#endif