#pragma once
#include "Bolo.h"
#include "ParticleSystem.h"
#include <vector>
#include <set>
class Game;
class BoloManager
{
protected:
	ParticleSystem* psys;
	Game* g;
	std::set<Bolo*> bolosScene;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
	//vector/mapa de bolos que tenga los bolos a generar por nivel 
public:

	BoloManager(Game* g, ParticleSystem* p, physx::PxScene* gScene, physx::PxPhysics* gPhysics);
	void onBoloDeath(Bolo* b);
};


