#include "Airplane.h"

#include "Helix.h"

Airplane::Airplane(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng) :
	IG2Object(initPos, node, sceneMng),
	_body(new IG2Object(initPos, createChildSceneNode(), sceneMng, "sphere.mesh")),
	_wing1(new IG2Object(initPos, _body->createChildSceneNode(), sceneMng, "cube.mesh")),
	_wing2(new IG2Object(initPos, _body->createChildSceneNode(), sceneMng, "cube.mesh")),
	_pilot(new IG2Object(initPos, _body->createChildSceneNode(), sceneMng, "ninja.mesh")),
	_rudder(new IG2Object(initPos, _body->createChildSceneNode(), sceneMng, "cube.mesh")),
	_helix1(new Helix(initPos, _wing1->createChildSceneNode(), sceneMng, 10)),
	_helix2(new Helix(initPos, _wing2->createChildSceneNode(), sceneMng, 10))
{
	createAirplane();
	createPilot();
	createRudder();
	createHelix();
}

Airplane::~Airplane()
{
	delete _body;
	_body = nullptr;

	delete _wing1;
	_wing1 = nullptr;
	delete _wing2;
	_wing2 = nullptr;

	delete _pilot;
	_pilot = nullptr;
	delete _rudder;
	_rudder = nullptr;

	delete _helix1;
	_helix1 = nullptr;
	delete _helix2;
	_helix2 = nullptr;
}

void Airplane::frameRendered(const Ogre::FrameEvent& evt)
{
	/*_helix1->yaw(Radian(25));
	_helix2->yaw(Radian(25));*/
}

bool Airplane::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_w) 
	{
		_helix1->rotate(Quaternion(Degree(5), Vector3(0, 1, 0)));
		_helix2->rotate(Quaternion(Degree(5), Vector3(0, 1, 0)));
	}

	return true;
}

void Airplane::createAirplane() const
{
	_body->setScale(Vector3(10, 2, 2));

	_wing1->setScale(Vector3(0.5, 0.25, 1));
	_wing1->yaw(Degree(90));
	_wing1->setPosition(Vector3(0, 0, 200));

	_wing2->setScale(Vector3(0.5, 0.25, 1));
	_wing2->yaw(Degree(-90));
	_wing2->setPosition(Vector3(0, 0, -200));
}

void Airplane::createPilot() const
{
	_pilot->setScale(Vector3(0.1, 0.5, 0.5));
	_pilot->setPosition(Vector3(-50, 30, 0));
	_pilot->yaw(Degree(90));
}

void Airplane::createRudder() const
{
	_rudder->setScale(Vector3(0.25, 0.5, 0.1));
	_rudder->setPosition(Vector3(90, 50, 0));
	_rudder->roll(Degree(45));
}

void Airplane::createHelix() const
{
	_helix1->setScale(Vector3(0.04, 0.4, 0.1));
	_helix1->setPosition(Vector3(-40, 0, -30));
	_helix1->pitch(Degree(-90));

	_helix2->setScale(Vector3(0.04, 0.4, 0.1));
	_helix2->setPosition(Vector3(-40, 0, 30));
	_helix2->pitch(Degree(90));
}
