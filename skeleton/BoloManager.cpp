#include "BoloManager.h"
#include "Game.h"
#include "Constants.h"
BoloManager::BoloManager(Game* game, ParticleSystem* p, physx::PxScene* scene, physx::PxPhysics* physics)
{
	g = game;
	psys = p;
	gScene = scene;
	gPhysics = physics;

	//nivel 
	initLevels();
}
//returns true if there are no bolos left
void BoloManager::onBoloDeath(Bolo* b)
{
	bolosScene.erase(b);
	if (playing)
	{
		g->addPoints(10); 
		if (bolosScene.empty())
		{
			g->endOfLevel();
		}
	}
}

void BoloManager::explode(Vector3 pos)
{
	std::list <Object*> aux; //--------------que cojones porqeu no me deja pasarle bolos directamente? racismo
	for (auto e : bolosScene)
	{
		aux.push_back(e);
	}
	psys->explode(pos, aux);
}

void BoloManager::loadLevel(int n)
{
	playing = true;
	int i = 0;
	std::vector<Bolo*> auxM;
	for (auto b : bolosByLevel[n])
	{
		Bolo* aux = b->clone();
		if (i < bolosByLevelConnected[n])
		{
			auxM.push_back(aux);
		}
		psys->addToSystem(aux);
		bolosScene.insert(aux);
		i++;
	}

	for (auto it = auxM.begin(); it != auxM.end();)
	{
		Bolo* b1 = (*it);
		it++; 
		Bolo* b2 = (*it);
		psys->addMuelle(b1, b2);
		it++;
	}
}

void BoloManager::initLevels()
{
	
	bolosByLevel = std::vector<std::set<Bolo*>>(constants::LEVELS);
	bolosByLevelConnected = std::vector<int>(constants::LEVELS);
	
	//level 0
	//bolos-muelle
	Bolo* b6 = new Bolo(this, gScene, gPhysics, {0.8,2,3,1}, 2, physx::PxTransform(Vector3(-10, 0, -60)), true);
	Bolo* b7 = new Bolo(this, gScene, gPhysics, { 0.8,2,3,1 },2, physx::PxTransform(Vector3( +10, 0, -60)), true);
	bolosByLevel[0].insert(b6); bolosByLevel[0].insert(b7); 
	bolosByLevelConnected[0] = 2; //hay dos muelles, siempre estarán al principio
	Bolo* b = new Bolo(this, gScene, gPhysics ,2, physx::PxTransform(Vector3(-10, 0, -100)),true);
	Bolo* b2 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(10, 0, -100)), true);
	bolosByLevel[0].insert(b); bolosByLevel[0].insert(b2);

	//level 1
	Bolo* b3 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(-10, 0, -100)), true);
	Bolo* b4 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(10, 0, -100)), true);
	Bolo* b5 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(20, 0, -100)), true );
	bolosByLevel[1].insert(b3); bolosByLevel[1].insert(b4); bolosByLevel[1].insert(b5);

	//level 2
	for (int i = 0; i < 5; i++)
	{
		Bolo* b = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(-24+(i*10), 0, -100)), true);
		bolosByLevel[2].insert(b);
	}
	for (int i = 0; i < 3; i++)
	{
		Bolo* b = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(-9+(i * 10), 0, -80)), true);
		bolosByLevel[2].insert(b);
	}
	
}

void BoloManager::clearScene()
{
	playing = false;
	for (auto it = bolosScene.begin(); it != bolosScene.end();++it)
	{
		(*it)->die();
	}
}
