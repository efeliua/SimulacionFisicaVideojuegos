#pragma once
#include "SpringForceGenerator.h"
class ParticleBungee: public SpringForceGenerator
{
public:
	virtual void updateForce(Object* particle, double t);
};

