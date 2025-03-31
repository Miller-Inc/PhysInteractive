// PhysInteractive.cpp : Defines the entry point for the application

#include "PhysInteractive.h"
#include "MillerInc.PhysicsEngine/include/FullEngineIncludes.h"
#include <cstring>
#include <thread>

using namespace MillerPhysics;

void EulerTest();
void SimpleObjectTest();
void SimpleObj();
void DevFunc();

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		if (strcmp(argv[1], "euler") == 0)
		{
			EulerTest();
		}
		else if (strcmp(argv[1], "simple") == 0)
		{
			SimpleObjectTest();
		}
	}

	else
	{
		DevFunc();
	}

	return 0;
}

void DevFunc()
{
	MScene scene;
	MObject object1({0.0f, 0.0f, 1000.0f}, MQuaternion(), 1000);
	MObject object2({0.0f, 0.0f, 1000.0f}, MQuaternion(), 1000);
	MObject object3({0.0f, 0.0f, 1000.0f}, MQuaternion(), 1000);
	object1.SetupPhysics(PhysicsSim::SimplePhysicsSimulation);
	object2.SetupPhysics(PhysicsSim::SimplePhysicsSimulation);
	object3.SetupPhysics(PhysicsSim::SimplePhysicsSimulation);
	object1.SetSimulatePhysics(true);
	object2.SetSimulatePhysics(true);
	object3.SetSimulatePhysics(true);
	scene.addObject(&object1);
	scene.addObject(&object2);
	scene.addObject(&object3);
	scene.BeginPlay();
	bool* running = new bool(true);
	std::thread thread([&scene, running]()
	{
		scene.BeginPlay();
		std::chrono::time_point<std::chrono::system_clock> curr, prev;
		prev = std::chrono::system_clock::now();
		float secondsDiff;
		long millisecs;

		while (*running)
		{
			curr = std::chrono::system_clock::now();
			millisecs = std::chrono::duration_cast<std::chrono::milliseconds>(curr - prev).count();
			secondsDiff = (float)millisecs / 1000.0f;

			scene.EventTick(secondsDiff);

			prev = curr;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		scene.EndPlay(EndPlayEvent(EndPlayReason::NormalExit, 0));
	});

	std::string input;
	while (*running)
	{
		std::cout << "Enter \"quit\" to quit\n";
		std::cin >> input;
		if (input == "quit")
		{
			*running = false;
		}
	}

	thread.join();

	free(running);

}


void SimpleObj()
{
	MObject obj;
	obj.SetPosition({0.0f, 0.0f, 1000.0f});
	obj.SetSimulatePhysics(true);
	obj.SetupPhysics(PhysicsSim::SimplePhysicsSimulation);
	obj.BeginPlay();
	float secondsElapsed = 0.016f; // Simulate 60 FPS
	float totalTime = 0.0f;
	for (int i = 0; i < 63; ++i)
	{
		obj.EventTick(secondsElapsed);
		std::cout << "Tick " << i << ": Position: " << obj.GetPosition().ToString() << "\n";
		totalTime += secondsElapsed;
	}
	obj.EndPlay(EndPlayEvent(NormalExit, 0));
	std::cout << "Final Position: " << obj.GetPosition().ToString() << "\n";
	std::cout << "Final Rotation: " << obj.GetRotation().ToString() << "\n";
	std::cout << "Final Scale: " << obj.GetScale().ToString() << "\n";
	std::cout << "Total Time: " << totalTime << "\n";
}

void SimpleObjectTest()
{
	MObject obj;
	obj.BeginPlay();
	obj.SetPosition(MVector(1.0f, 2.0f, 3.0f));
	obj.SetRotation(fromEuler(MVector(0.1f, 0.2f, 0.3f)));
	obj.SetScale(MVector(2.0f, 2.0f, 2.0f));
	obj.SetSimulatePhysics(true);
	obj.SetupPhysics([](MillerPhysics::MObject& obj, const float secondsElapsed) {
		std::cout << "Physics function called with " << secondsElapsed << " seconds elapsed\n";
		std::cout << "Pos: " << obj.GetPosition().ToString() << "\n";
		std::cout << "Rot: " << obj.GetRotation().ToString() << "\n";
		std::cout << "Scale: " << obj.GetScale().ToString() << "\n";
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
