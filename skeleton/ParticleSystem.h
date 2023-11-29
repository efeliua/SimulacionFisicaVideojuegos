#pragma once
#include <list>
#include "GaussianParticleGenerator.h"
#include "FireworkGenerator.h"
#include "ParticleForceRegistry.h"
#include "Projectile.h"

class ParticleSystem
{
protected:
	std::list <Particle*> particles;
	std::list <ParticleGenerator*> particles_generators;
	std::list <ForceGenerator*> force_generators;
	FireworkGenerator* fireGen;
	ParticleForceRegistry* pfRegistry;

public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem();
	void addForceGenerators(std::list <Particle*> p);
	void addSingleForceGeneratorToAll(ForceGenerator* f);
	void shoot();
	void explode();
	void shootProjectile(type t);
	void generatespringDemo();
	void addK();
};

