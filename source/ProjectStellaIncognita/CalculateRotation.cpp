#include "CalculateRotation.h"

matrix4 CalculateRotation::CreateFromQuaternion(quaternion quat)
{
	matrix4 matrix;
	float mData[16];

	float num9 = quat.X * quat.X;
	float num8 = quat.Y * quat.Y;
	float num7 = quat.Z * quat.Z;
	float num6 = quat.X * quat.Y;
	float num5 = quat.Z * quat.W;
	float num4 = quat.Z * quat.X;
	float num3 = quat.Y * quat.W;
	float num2 = quat.Y * quat.Z;
	float num = quat.X * quat.W;

	mData[0] = 1.0f - (2.0f * (num8 + num7));
	mData[1] = 2.0f * (num6 + num5);
	mData[2] = 2.0f * (num4 - num3);
	mData[3] = 0.0f;

	mData[4] = 2.0f * (num6 - num5);
	mData[5] = 1.0f - (2.0f * (num7 + num9));
	mData[6] = 2.0f * (num2 + num);
	mData[7] = 0.0f;

	mData[8] = 2.0f * (num4 + num3);
	mData[9] = 2.0f * (num2 - num);
	mData[10] = 1.0f - (2.0f * (num8 + num9));
	mData[11] = 0.0f;
	
	mData[12] = 0.0f;
	mData[13] = 0.0f;
	mData[14] = 0.0f;
	mData[15] = 1.0f;

	matrix.setM(mData);
	return matrix;
}

//creates a quaternion from the yaw pitch and roll values
quaternion CalculateRotation::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	quaternion quat;
	float num9 = roll * 0.5f;
	float num6 = (float) sin((double) num9);
	float num5 = (float) cos((double) num9);
	float num8 = pitch * 0.5f;
	float num4 = (float) sin((double) num8);
	float num3 = (float) cos((double) num8);
	float num7 = yaw * 0.5f;
	float num2 = (float) sin((double) num7);
	float num = (float) cos((double) num7);

	quat.X = ((num * num4) * num5) + ((num2 * num3) * num6);
	quat.Y = ((num2 * num3) * num5) - ((num * num4) * num6);
	quat.Z = ((num * num3) * num6) - ((num2 * num4) * num5);
	quat.W = ((num * num3) * num5) + ((num2 * num4) * num6);
	return quat;
}

//returns the acceleration of the angularMotion
vector3df CalculateRotation::calcAngularMotion(matrix4 inertiaMatrix, vector3df torque)
{
	inertiaMatrix.makeInverse();
	return vector3df(0,0,0);//(inertiaMatrix * torque);
}