#pragma once
#include "SpringForceGenerator.h"
class ElasticSpringFG: public SpringForceGenerator
{
public:
	ElasticSpringFG(double t, double k, double resting_length, Object* other) : SpringForceGenerator(t, k, resting_length, other) {};
	virtual void updateForce(Object* particle, double time);
};

