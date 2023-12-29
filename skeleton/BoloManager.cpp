#include "BoloManager.h"
#include "Game.h"

BoloManager::BoloManager(Game* game, ParticleSystem* p, physx::PxScene* scene, physx::PxPhysics* physics)
{
	g = game;
	psys = p;
	gScene = scene;
	gPhysics = physics;

	//nivel 

	Bolo* b = new Bolo(this, gScene, gPhysics, physx::PxTransform(Vector3(-10, 0, -100)), 2);
	psys->addToSystem(b);
	bolosScene.insert(b);

	Bolo* b2 = new Bolo(this, gScene, gPhysics, physx::PxTransform(Vector3(10, 0, -100)), 2);
	psys->addToSystem(b2);
	bolosScene.insert(b2);
}
//returns true if there are no bolos left
void BoloManager::onBoloDeath(Bolo* b)
{
	bolosScene.erase(b);
	g->addPoints(10); 
	if (bolosScene.empty())
	{
		g->endOfLevel();
	}
}
