#pragma once
#include "Bolo.h"
#include "ParticleSystem.h"
#include <vector>
#include <set>
#include <list>
class Game;
class BoloManager
{
protected:
	ParticleSystem* psys;
	Game* g;
	std::set<Bolo*> bolosScene;
	std::vector<std::set<Bolo*>>bolosByLevel; 
	std::vector<int>bolosByLevelConnected;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
	bool playing;
	//vector/mapa de bolos que tenga los bolos a generar por nivel 
public:

	BoloManager(Game* g, ParticleSystem* p, physx::PxScene* gScene, physx::PxPhysics* gPhysics);
	void onBoloDeath(Bolo* b);
	void explode(Vector3 pos);
	void loadLevel(int n);
	void initLevels();
	void clearScene();
};


