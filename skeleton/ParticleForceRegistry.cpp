#include "ParticleForceRegistry.h"



void ParticleForceRegistry::deleteForceRegistry(ForceGenerator* f)
{
	for (auto it = begin(); it != end();) 
	{
		if (it->second == f)
		{
			it=erase(it); ///te devuelve el sig
		}
		else
		{
			++it;
		}
	}
}

void ParticleForceRegistry::deletePair(Object* o, ForceGenerator* f)
{
	for (auto it = begin(); it != end();)
	{
		if (it->first==o&&it->second == f)
		{
			it = erase(it); ///te devuelve el sig
			break;
		}
		else
		{
			++it;
		}
	}
}
