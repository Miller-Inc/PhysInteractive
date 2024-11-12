// PhysInteractive.cpp : Defines the entry point for the application.
//

#include "PhysInteractive.h"
#include "MillerInc.PhysicsEngine/include/FullEngineIncludes.h"
#include "MillerInc.PhysicsEngine/GPU/GPU-Macros.h"
#include "MillerInc.PhysicsEngine/GPU/Cuda-Engine/gpuScene.h"

using namespace std;
// #define CUDA_AVAILABLE false


class Testing
{
public:
	static GPUScene* createScene(GPUScene* scene, int numOfObjs)
	{
		for (int i = 0; i < numOfObjs; i++)
		{
			scene->addCollisionObject(new Sphere(0.0, 1.0, Vector3()));
		}
		return scene;
	}
};


int main()
{

	auto* scene = Testing::createScene(new GPUScene(), 1);

	std::cout << scene->getNumCollisionObjects() << std::endl;

	Sphere* sph = new Sphere(0.0, 10.0, Vector3());

	sph->name = "Remove Sphere";

	scene->addCollisionObject(sph);

	std::cout << scene->getNumCollisionObjects() << std::endl;

	scene->removeCollisionObject(sph);

	std::cout << scene->getNumCollisionObjects() << std::endl;

	return 0;
}


// 0119949400
// 0218057200
// 0198196200
// 0119884000
// 0071591000
// 2324563456