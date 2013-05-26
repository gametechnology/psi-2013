#ifndef PSI_SCENE
#define PSI_SCENE

#include "Composite.h"

class Scene : public Composite
{
public:
	virtual void update() = 0;
	virtual void init() = 0;
	virtual void requestNextScene() = 0;
	virtual void notify(void* data) = 0;

	virtual void addComponent(Component*);
	virtual void removeComponent(Component*);
protected:
	Scene(const char*);
};

#endif
