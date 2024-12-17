#include "Airplane.h"

#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreParticleSystem.h>

#include "Helix.h"

Airplane::Airplane(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng) :
	IG2Object(initPos, node, sceneMng),
	_body(new IG2Object(initPos, createChildSceneNode(), sceneMng, "uv_sphere.mesh")),
	_wing1(new IG2Object(initPos, _body->createChildSceneNode(), sceneMng, "cube.mesh")),
	_wing2(new IG2Object(initPos, _body->createChildSceneNode(), sceneMng, "cube.mesh")),
	_pilot(new IG2Object(initPos, _body->createChildSceneNode(), sceneMng, "ninja.mesh")),
	_rudder(new IG2Object(initPos, _body->createChildSceneNode(), sceneMng, "cube.mesh")),
	_helix1(new Helix(initPos, _wing1->createChildSceneNode(), sceneMng, 10)),
	_helix2(new Helix(initPos, _wing2->createChildSceneNode(), sceneMng, 10)),
	_engine1(mSM->createParticleSystem("Engine1", "Examples/smokeParticle")),
	_engine2(mSM->createParticleSystem("Engine2", "Examples/smokeParticle")),
	_animState(nullptr),
	_move(false)
{
	createAirplane();
	createPilot();
	createRudder();
	createHelix();

	createEngineParticle();

	createAnim(10.0f, 100.0f, 500);
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
	if (_move)
	{
		_helix1->rotate(Quaternion(Degree(5), Vector3(0, 1, 0)));
		_helix2->rotate(Quaternion(Degree(5), Vector3(0, 1, 0)));

		_animState->addTime(evt.timeSinceLastFrame);
	}
}

bool Airplane::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_w)
	{
		_move = !_move;

		_engine1->setEmitting(_move);
		_engine2->setEmitting(_move);
	}

	return true;
}

void Airplane::createAirplane() const
{
	_body->setMaterialName("Examples/shaderOrange");
	_body->setScale(Vector3(10, 2, 2));

	_wing1->setScale(Vector3(0.5, 0.25, 1));
	_wing1->yaw(Degree(90));
	_wing1->setPosition(Vector3(0, 0, 200));
	_wing1->setMaterialName("Examples/Checker");

	_wing2->setScale(Vector3(0.5, 0.25, 1));
	_wing2->yaw(Degree(-90));
	_wing2->setPosition(Vector3(0, 0, -200));
	_wing2->setMaterialName("Examples/Checker");
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

void Airplane::createEngineParticle() const
{
	SceneNode* node1 = _helix1->createChildSceneNode();
	node1->pitch(Degree(180));
	node1->setPosition(0, -800, 0);
	node1->attachObject(_engine1);

	SceneNode* node2 = _helix2->createChildSceneNode();
	node2->pitch(Degree(180));
	node2->setPosition(0, -800, 0);
	node2->attachObject(_engine2);

	_engine1->setEmitting(false);
	_engine2->setEmitting(false);
}

void Airplane::createAnim(const float t, const float keyFrames, const int r)
{
	Animation* anim = mSM->createAnimation("AirplaneAnim", t);
	anim->setInterpolationMode(Ogre::Animation::IM_SPLINE);

	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	TransformKeyFrame* key;

	mNode->setInitialState();

	for (int i = 0; i < keyFrames; ++i)
	{
		key = track->createNodeKeyFrame(i * (t / keyFrames));

		const float angle = Math::TWO_PI / keyFrames * i;

		key->setTranslate(Vector3(1, 0, 0) * r * cos(angle) + Vector3(0, 1, 0) * r * sin(angle));

		const float tangent = angle - Math::HALF_PI;
		Quaternion rotation = Quaternion(Radian(tangent), Vector3::UNIT_Z);
		key->setRotation(rotation);
	}

	_animState = mSM->createAnimationState("AirplaneAnim");
	_animState->setEnabled(true);
}
