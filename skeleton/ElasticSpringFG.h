#pragma once
#include "SpringForceGenerator.h"
class ElasticSpringFG: public SpringForceGenerator
{
public:
	ElasticSpringFG(double t, double k, double resting_length, Particle* other) : SpringForceGenerator(t, k, resting_length, other) {};
	virtual void updateForce(Particle* particle, double time);
};

