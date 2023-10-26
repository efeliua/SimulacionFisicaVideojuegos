#pragma once
#include <list>
#include "GaussianParticleGenerator.h"
#include "FireworkGenerator.h"
class ParticleSystem
{
protected:
	std::list <Particle*> particles;
	std::list <ParticleGenerator*> particles_generators;
	FireworkGenerator* fireGen;
public:
	ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem();
	void shoot();
};

