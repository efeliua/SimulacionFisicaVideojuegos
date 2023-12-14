#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"
#include <vector>
class FireworkGenerator: public ParticleGenerator
{
protected:
	std::vector<Firework*> firework_pool;
	public: 
		FireworkGenerator(Vector3 pos = Vector3{ 0,0,0 });
		virtual std::list<Object*> generateParticles();
		Firework* getModel(int i) { return firework_pool[i]; }
};


