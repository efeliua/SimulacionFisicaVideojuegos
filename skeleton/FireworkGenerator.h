#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"
#include <vector>
class FireworkGenerator: public ParticleGenerator
{
protected:
	std::vector<Firework*> firework_pool;
	public: 
		FireworkGenerator(std::string name, Particle* model, double _genprob, int maxpart);
		virtual std::list<Particle*> generateParticles();
		Firework* getModel(int i) { return firework_pool[i]; }
};


