#ifndef COMPOSITE
#define COMPOSITE
#pragma once

#include <string>
#include <vector>

using namespace std;

class Composite {
public:
	Composite();
	~Composite();
	
	bool initialized;
	bool destroyed;
	bool enabled;
	
	virtual void onAdd();
	virtual void init();

	virtual void update();
	virtual void lateUpdate();
	virtual void draw();

	virtual void handleMessage(unsigned int message);

	virtual void disable();
	virtual void enable();
	virtual void destroy();
};

#endif
