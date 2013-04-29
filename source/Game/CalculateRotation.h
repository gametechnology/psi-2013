#ifndef CALC_ROTATION_H
#define CALC_ROTATION_H

#include "Irrlicht\irrlicht.h"
#include <math.h>

using namespace irr;
using namespace core;

class CalculateRotation
{
public:

	static quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);

	static matrix4 CreateFromQuaternion(quaternion quat);

	vector3df calcAngularMotion(matrix4 inertiaMatrix, vector3df torque);

};

#endif