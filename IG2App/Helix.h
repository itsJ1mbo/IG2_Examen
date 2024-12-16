#pragma once
#include "IG2Object.h"

class Helix : public IG2Object
{
public:
	Helix(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, int nB);
	~Helix() override;

private:
	void createBlades();

	int _nB;

	std::vector<IG2Object*> _blades;
};

