#ifndef CALC_ROTATION_H
#define CALC_ROTATION_H

#include <Irrlicht\irrlicht.h>
#include <math.h>

class CalculateRotation
{
public:
	static irr::core::quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);

	static irr::core::matrix4 CreateFromQuaternion(irr::core::quaternion quat);

	vector3df calcAngularMotion(irr::core::matrix4 inertiaMatrix, irr::core::vector3df torque);

};

#endif