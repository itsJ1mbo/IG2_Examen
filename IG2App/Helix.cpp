#include "Helix.h"
#include "Blade.h"

Helix::Helix(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, const int nB) :
	IG2Object(initPos, node, sceneMng, "column.mesh"),
	_nB(nB)
{
	setMaterialName("Examples/SphereMappedRustySteel");
	createBlades();
}

Helix::~Helix()
{
	for (auto b : _blades)
	{
		delete b;
		b = nullptr;
	}
}

void Helix::createBlades()
{
	for (int i = 0; i < _nB; ++i)
	{
		IG2Object* b = new Blade(mNode->getPosition(), mNode->createChildSceneNode(), mSM);
		b->setMaterialName("Examples/SphereMappedRustySteel");
		b->yaw(Radian(2 * M_PI / _nB * i));
		b->move(Vector3(cos(2 * M_PI / _nB * i) * 500, 250, -sin(2 * M_PI / _nB * i) * 500));
		_blades.push_back(b);
	}
}
