#pragma once
#include "IG2Object.h"
class Airplane : public IG2Object
{
public:
	Airplane(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng);
	~Airplane() override;

	void frameRendered(const Ogre::FrameEvent& evt) override;
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

private:
	void createAirplane() const;
	void createPilot() const;
	void createRudder() const;
	void createHelix() const;

	IG2Object* _body;
	IG2Object* _wing1;
	IG2Object* _wing2;

	IG2Object* _pilot;

	IG2Object* _rudder;

	IG2Object* _helix1;
	IG2Object* _helix2;
};

