// PhysInteractive.cpp : Defines the entry point for the application

#include "PhysInteractive.h"
#include "MillerInc.PhysicsEngine/include/FullEngineIncludes.h"

using namespace MillerPhysics;

void EulerTest();
void SimpleObjectTest();

int main()
{
	SimpleObjectTest();
	EulerTest(); 

	return 0;
}

void SimpleObjectTest()
{
	MObject obj;
	obj.BeginPlay();
	obj.SetPosition(MVector(1.0f, 2.0f, 3.0f));
	obj.SetRotation(fromEuler(MVector(0.1f, 0.2f, 0.3f)));
	obj.SetScale(MVector(2.0f, 2.0f, 2.0f));
	obj.SetSimulatePhysics(true);
	obj.SetupPhysics([](MillerPhysics::MObject* obj, const float secondsElapsed) {
		std::cout << "Physics function called with " << secondsElapsed << " seconds elapsed\n";
		std::cout << "Pos: " << obj->GetPosition().ToString() << "\n";
		std::cout << "Rot: " << obj->GetRotation().ToString() << "\n";
		std::cout << "Scale: " << obj->GetScale().ToString() << "\n";
	});
	obj.EventTick(0.1f);
	obj.Pause();
	obj.Resume();
	obj.Restart();
	obj.EndPlay(EndPlayEvent(NormalExit, 0));
}

void EulerTest()
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
}
