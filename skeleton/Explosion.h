#pragma once
#include "ForceGenerator.h"
class Explosion: public ForceGenerator
{
public:
	Explosion(double t, Vector3 og, float r, float k, float tau) : ForceGenerator(t), origin(og), radius(r), k(k), tau(tau) {};
	virtual void updateForce(Object* particle, double time = 0);
protected:
	Vector3 origin;
	float k;
	float tau;
	float radius;

};

