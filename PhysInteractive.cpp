// PhysInteractive.cpp : Defines the entry point for the application.
//

#include "PhysInteractive.h"
#include "MillerInc.PhysicsEngine/include/FullEngineIncludes.h"
#include "MillerInc.PhysicsEngine/GPU/GPU-Macros.h"

using namespace std;
// #define CUDA_AVAILABLE false

int main()
{

#if CUDA_AVAILABLE
	kernel_main();
	std::string kernel = "GPU Used";
#else
	std::string kernel = "No GPU Used";
#endif

	std::vector<Vector3> vectors, vectors2, result;

	// Create vectors
	vectors.emplace_back(1.0f, 2.0f, 3.0f);
	vectors.emplace_back(4.0f, 5.0f, 6.0f);
	vectors.emplace_back(7.0f, 8.0f, 9.0f);
	vectors.emplace_back(1.0f, 2.0f, 3.0f);
	vectors.emplace_back(4.0f, 5.0f, 6.0f);
	vectors.emplace_back(7.0f, 8.0f, 9.0f);
	vectors.emplace_back(1.0f, 2.0f, 3.0f);
	vectors.emplace_back(4.0f, 5.0f, 6.0f);
	vectors.emplace_back(7.0f, 8.0f, 9.0f);
	vectors2.emplace_back(1.0f, 2.0f, 3.0f);
	vectors2.emplace_back(4.0f, 5.0f, 6.0f);
	vectors2.emplace_back(7.0f, 8.0f, 9.0f);
	vectors2.emplace_back(1.0f, 2.0f, 3.0f);
	vectors2.emplace_back(4.0f, 5.0f, 6.0f);
	vectors2.emplace_back(7.0f, 8.0f, 9.0f);
	vectors2.emplace_back(1.0f, 2.0f, 3.0f);
	vectors2.emplace_back(4.0f, 5.0f, 6.0f);
	vectors2.emplace_back(7.0f, 8.0f, 9.0f);


	Vector3Math::multiplyVectors(vectors, vectors2, result);

	for (auto & i : result) {
		cout << i.x << " " << i.y << " " << i.z << endl;
	}

	cout << kernel << endl;
	return 0;
}

// 0119949400
// 0218057200
// 0198196200
// 0119884000
// 0071591000
// 2324563456