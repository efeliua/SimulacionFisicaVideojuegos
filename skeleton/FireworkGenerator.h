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
		virtual ~FireworkGenerator(){
			for (auto it = firework_pool.begin(); it != firework_pool.end();)
			{
				delete(*it);
				it = firework_pool.erase(it);
			}
		}
		virtual std::list<Object*> generateParticles();
		Firework* getModel(int i) { return firework_pool[i]; }
};


