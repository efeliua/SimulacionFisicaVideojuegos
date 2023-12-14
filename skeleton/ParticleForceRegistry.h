#pragma once
#include <map>
#include "ForceGenerator.h"
typedef std::pair< Object*,ForceGenerator*> FRPair;
class ParticleForceRegistry : public std::multimap<Object*,ForceGenerator* >
{
public:
	ParticleForceRegistry() {};
	void updateForces(double duration)
	{
		for (auto it = begin(); it != end(); ++it) //begin de que del map? no se que es un map
		{ 
			it->second->updateForce(it->first, duration);
		}
	}
	inline void addRegistry(ForceGenerator* fg, Object* p) { FRPair fp = { p,fg }; insert(fp); } //inserta sin orden
	void deleteParticleRegistry(Object* p) { this->erase(p); } 
	void deleteForceRegistry(ForceGenerator* f);

};

