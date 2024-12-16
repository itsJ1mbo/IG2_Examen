#include "Blade.h"

Blade::Blade(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng) :
	IG2Object(initPos, node, sceneMng, "cube.mesh"),
	_head(nullptr)
{
	init();
}

Blade::~Blade()
{
	delete _head;
	_head = nullptr;
}

void Blade::init()
{
	setScale(Vector3(10, 0.25, 1));

	_head = new IG2Object(Vector3(0, 0, 0), createChildSceneNode(), mSM, "ogrehead.mesh");
	_head->setScale(Vector3(0.1f, 4, 0.1f));
	_head->setPosition(Vector3(45, 60, 0));
	_head->yaw(Degree(-90));
	_head->pitch(Degree(-90));
}
