// PhysInteractive.cpp : Defines the entry point for the application

#include "PhysInteractive.h"
#include "MillerInc.PhysicsEngine/include/FullEngineIncludes.h"

using namespace MillerPhysics;



int main()
{
	// Test 1: Euler to Quaternion and back
	MVector euler(0.1f, 0.2f, 0.3f);
	MQuaternion quatFromEuler = fromEuler(euler);
	MVector eulerFromQuat = toEuler(quatFromEuler);

	std::cout << "Original Euler angles: (" << euler.x << ", " << euler.y << ", " << euler.z << ")\n";
	std::cout << "Quaternion from Euler: (" << quatFromEuler.w << ", " << quatFromEuler.x << ", " << quatFromEuler.y << ", " << quatFromEuler.z << ")\n";
	std::cout << "Euler angles from Quaternion: (" << eulerFromQuat.x << ", " << eulerFromQuat.y << ", " << eulerFromQuat.z << ")\n";

	// Test 2: Axis-Angle to Quaternion and back
	MVector axis(1.0f, 0.0f, 0.0f);
	float angle = M_PI / 4; // 45 degrees
	MQuaternion quatFromAxisAngle = fromAxisAngle(axis, angle);
	auto [axisFromQuat, angleFromQuat] = toAxisAngle(quatFromAxisAngle);

	std::cout << "Original Axis: (" << axis.x << ", " << axis.y << ", " << axis.z << "), Angle: " << angle << "\n";
	std::cout << "Quaternion from Axis-Angle: (" << quatFromAxisAngle.w << ", " << quatFromAxisAngle.x << ", " << quatFromAxisAngle.y << ", " << quatFromAxisAngle.z << ")\n";
	std::cout << "Axis from Quaternion: (" << axisFromQuat.x << ", " << axisFromQuat.y << ", " << axisFromQuat.z << "), Angle: " << angleFromQuat << "\n";



	return 0;
}