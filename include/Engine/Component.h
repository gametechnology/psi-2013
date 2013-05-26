#ifndef PSI_COMPONENT
#define PSI_COMPONENT

#include <Irrlicht/irrlicht.h>

class Component {
public:
	virtual ~Component() { };

	const char* getName() { return _name; }

	virtual void init();
	virtual void update();
	virtual void handleMessage(unsigned int, void* data = 0) { };
protected:
	Component(const char*) { };
private:
	const char* _name;
};


#endif
