#pragma once
#include "SpringForceGenerator.h"
class ParticleBungee: public SpringForceGenerator
{
public:
	virtual void updateForce(Particle* particle, double t);
};

