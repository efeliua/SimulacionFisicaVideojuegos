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
//borramos modelos de bolos por nivel
BoloManager::~BoloManager()
{
	playing = false;
	for (int i = 0; i < bolosByLevel.size(); i++)
	{
		for (auto it = bolosByLevel[i].begin(); it != bolosByLevel[i].end();)
		{
			delete(*it);
			it = bolosByLevel[i].erase(it);
		}
	}
}
//recuenta bolos, añade puntos si se esta en juego y se avisa a game si se han derribado todos
void BoloManager::onBoloDeath(Bolo* b)
{
	bolosScene.erase(b);
	if (playing)
	{
		if (b->isMuelle()) { psys->deleteMuelle(b); } //si es muelle tendremos que borrar la fuerza de muelle del bolo complementario
		g->addPoints(10); 
		if (bolosScene.empty())
		{
			g->endOfLevel();
		}
	}
}
//se provoca una explosión en un punto que afecta a los bolos en escena 
void BoloManager::explode(Vector3 pos)
{
	std::list <Object*> aux; 
	for (auto e : bolosScene)
	{
		aux.push_back(e);
	}
	psys->explode(pos, aux);
}
//Se crean los bolos correspondientes al nivel 
void BoloManager::loadLevel(int n)
{
	playing = true;
	int i = 0;
	std::vector<Bolo*> auxM;
	for (auto b : bolosByLevel[n])
	{
		Bolo* aux = b->clone();
		if (aux->isMuelle())
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
//creacion de modelos de nivel
void BoloManager::initLevels()
{
	bolosByLevel = std::vector<std::set<Bolo*>>(constants::LEVELS);
	
	//level 0
	Bolo* b3 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(-3, 0, -100)), true);
	Bolo* b4 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(0, 0, -85)), true);
	Bolo* b5 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(3, 0, -100)), true );
	bolosByLevel[0].insert(b3); bolosByLevel[0].insert(b4); bolosByLevel[0].insert(b5);

	//level 1
	//bolos-muelle
	Bolo* b6 = new Bolo(this, gScene, gPhysics, {0.8,2,3,1}, 2, physx::PxTransform(Vector3(-4.5, 0, -60)), true);
	Bolo* b7 = new Bolo(this, gScene, gPhysics, { 0.8,2,3,1 },2, physx::PxTransform(Vector3( +4.5, 0, -60)), true);
	b6->setMuelle(true); b7->setMuelle(true);
	bolosByLevel[1].insert(b6); bolosByLevel[1].insert(b7); 
	Bolo* b = new Bolo(this, gScene, gPhysics ,2, physx::PxTransform(Vector3(-5, 0, -100)),true);
	Bolo* b2 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(5, 0, -100)), true);
	bolosByLevel[1].insert(b); bolosByLevel[1].insert(b2);

	//level 2
	/*for (int i = 0; i < 5; i++)
	{
		Bolo* b = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(-18.5+(i*10), 0, -105)), true);
		bolosByLevel[2].insert(b);
	}*/
	for (int i = 0; i < 3; i++)
	{
		Bolo* b = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(-11.5+(i * 10), 0, -105)), true);
		bolosByLevel[2].insert(b);
	}
	Bolo* b8 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(-3, 0, -95)), true);
	Bolo* b9 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(0, 0, -80)), true);
	Bolo* b10 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(3, 0, -95)), true);
	bolosByLevel[2].insert(b8); bolosByLevel[2].insert(b9); bolosByLevel[2].insert(b10);

	//level 3
	//level 2
	for (int i = 0; i < 5; i++)
	{
		Bolo* b = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(-18.5 + (i * 10), 0, -105)), true);
		bolosByLevel[3].insert(b);
	}
	for (int i = 0; i < 3; i++)
	{
		Bolo* b = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(-11.5 + (i * 10), 0, -90)), true);
		bolosByLevel[3].insert(b);
	}
	Bolo* b11 = new Bolo(this, gScene, gPhysics, { 0.8,2,3,1 }, 2, physx::PxTransform(Vector3(-3, 0, -65)), true); b11->setMuelle(true);
	Bolo* b12 = new Bolo(this, gScene, gPhysics, 2, physx::PxTransform(Vector3(0, 0, -50)), true);
	Bolo* b13 = new Bolo(this, gScene, gPhysics, { 0.8,2,3,1 }, 2, physx::PxTransform(Vector3(3, 0, -65)), true); b13->setMuelle(true);
	bolosByLevel[3].insert(b11); bolosByLevel[3].insert(b12); bolosByLevel[3].insert(b13);
	
}
//se mueren los bolos restantes en escena (el sistema los borrara)
void BoloManager::clearScene()
{
	playing = false;
	for (auto it = bolosScene.begin(); it != bolosScene.end();++it)
	{
		(*it)->die();
	}
}
