#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class BuoyancyForceGenerator: public ForceGenerator
{
public:
	BuoyancyForceGenerator(float d, Vector3 pos); //pos para el agua render sin mas
	virtual void updateForce(Object* particle, double t);
	virtual ~BuoyancyForceGenerator();
	void addMass(float m);
protected:
	float _liquid_density;
	float _gravity = 9.8;

	//falta meterle esa particle de referencia a renderizar y mierdas
	Object* _liquid_particle; //for representation
};

