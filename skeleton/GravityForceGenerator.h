#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
 //quesesto
class GravityForceGenerator: public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g) :ForceGenerator(), _grav(g) { setName("gravFG"); };

	virtual void updateForce(Object* particle, double t);

	inline void setGravity(Vector3 g) { _grav = g; }

protected:
	Vector3 _grav;
};

