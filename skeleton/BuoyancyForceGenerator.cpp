#include "BuoyancyForceGenerator.h"



BuoyancyForceGenerator::BuoyancyForceGenerator(float d, Vector3 pos) : _liquid_density(d)
{
	_liquid_particle = new Particle(Vector4(0, 0, 060, 0), 0,pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 6000, false, false, 1, BOX, Vector3(20,0.5,5));
	setName("buoyancySFG");
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t)
{
	float h = particle->getPos().y;
	float h0 = _liquid_particle->getPos().y;
	float _height = particle->getHeight(); //height of the particle
	float v = particle->getRecVolume();

	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > _height * 0.5)
	{
		immersed = 0.0;
	}
	else if (h0 - h < _height * 0.5)
	{ //totally immersed
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / _height + 0.5;

	}
	f.y = _liquid_density *v* immersed * _gravity;
	particle->addForce(f);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
	delete _liquid_particle;
}
