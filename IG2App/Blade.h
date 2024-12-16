#pragma once
#include "IG2Object.h"

class Blade : public IG2Object
{
public:
	Blade(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng);
	~Blade() override;

	//void frameRendered(const Ogre::FrameEvent& evt);

private:
	void init();

	IG2Object* _head;
};

