#ifndef PSI_PRIM_COMP
#define PSI_PRIM_COMP

#include <Engine/Component.h>

class PrimitiveComponent : public Component
{
private:
	irr::scene::ISceneManager* smgr;
	irr::scene::ISceneNode* node;

	void createCubePrimitive(irr::f32, irr::core::vector3df);
	void createSpherePrimitive(irr::f32, irr::core::vector3df);
public:
	enum PrimitiveType
	{
		PRIM_CUBE,
		PRIM_SPHERE
	};

	/*!
	* @function 
	*	PrimitiveComponent default constructor to construct a stand-alone primitive 3D cube or sphere.
	* @param ISceneManager* 
	*	Pass in the pointer to your Irrlicht scene manager.
	* @param PrimitiveType
	*	Type of the primitive to create. It can be a Cube (PRIM_CUBE) or Sphere (PRIM_SPHERE).
	* @param Size
	*	The size of the primitive. For a sphere it is the radius, for a cube it is the halfsize.
	* @param Position
	*	The position in the game world. It is described using an Irrlicht vector3df taking floats.
	*/
	PrimitiveComponent(irr::scene::ISceneManager*, PrimitiveType, irr::f32, irr::core::vector3df = irr::core::vector3df(10.0f, 0, 0));

	/*!
	* @function
	*	PrimitiveComponent constructor to construct a primitive 3D cube or sphere attached to a parent node.
	* @param ISceneManager* 
	*	Pass in the pointer to your Irrlicht scene manager.
	* @param PrimitiveType
	*	Type of the primitive to create. It can be a Cube (PRIM_CUBE) or Sphere (PRIM_SPHERE).
	* @param Size
	*	The size of the primitive. For a sphere it is the radius, for a cube it is the halfsize.
	* @param ISceneNode*
	*	Pointer to the parent node.
	* @param RelativePosition
	*	The position in the game world. It is described using an Irrlicht vector3df taking floats.
	*/
	PrimitiveComponent(irr::scene::ISceneManager*, PrimitiveType, irr::f32, irr::scene::ISceneNode*, irr::core::vector3df = irr::core::vector3df(0, 0, 0));
	~PrimitiveComponent();

	virtual void handleMessage(unsigned int, void* data = 0) { };

	irr::scene::ISceneNode* getNode() { return node; };
};

#endif