#pragma once
#include <map>
#include "ForceGenerator.h"
typedef std::pair<ForceGenerator*, Particle*> FRPair;
class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*>
{
public:
	ParticleForceRegistry() {};
	void updateForces(double duration)
	{
		for (auto it = begin(); it != end(); ++it) //begin de que del map? no se que es un map
		{ 
			it->first->updateForce(it->second, duration);
		}
	}
	inline void addRegistry(ForceGenerator* fg, Particle* p) { FRPair fp = { fg,p }; insert(fp); } //inserta sin orden
	void deleteParticleRegistry(Particle* p); //buscarlo con un iterador :D
	
};

