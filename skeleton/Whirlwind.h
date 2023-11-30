#pragma once
#include "ParticleDragGenerator.h"
class Whirlwind: public ParticleDragGenerator
{
protected:
	float _k;
public:
	Whirlwind(const float k1, const float k2, Vector3 og, Vector3 area, Vector3 wvel,const float  k,double t= -1e10) :ParticleDragGenerator(k1, k2, og, area, wvel,t), _k(k) { setName("whirlwindFG"); };
	virtual void updateForce(Particle* particle, double t);

};

