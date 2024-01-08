#include "BallManager.h"
#include <iostream>
#include "RenderUtils.hpp"
BallManager::BallManager(ParticleSystem* p, physx::PxScene* scene, physx::PxPhysics* physics)
{
	psys = p;
	gScene = scene;
	gPhysics = physics;
	mainBall = nullptr;

	//create  balltypes
	Ball* b=new Ball(this, scene, physics, Vector4(0.4, 0.5, 3, 1), { 0, 0,0 }, true, 0.15);
	Ball* b2 = new Ball(this, scene, physics, Vector4(5, 0.5, 7, 1), { 0, 0,0 }, true,0.2);
	Ball* b3 = new Ball(this, scene, physics, Vector4(0.4, 0.8, 3, 1), { 0, 0,0 }, true,0.1);

	models.push_back(b);models.push_back(b2); models.push_back(b3);

	//balls per level
	ballsPerLevel.push_back(3); ballsPerLevel.push_back(2); ballsPerLevel.push_back(5);
}

BallManager::~BallManager()
{
	//borrar modelos 
}

void BallManager::onBallDeath()
{
	//if vector balls es 0
	//ya borra la ball el particle system tecnicamente
	//Aqui lo unico seria una nueva bola
	//create main ball
	//mainBall = new Ball(this,gScene, gPhysics, Vector4(0.4, 0.5, 3, 1), { 0, 0,0 }); //hacer clone con bolas modelo bestie
	
	if (ballsLeft > 0)
	{
		int random = rand() % models.size();
		mainBall =models[random]->clone();
		psys->addToSystem(mainBall);
		state = MOVEBALL;
	}
	else
	{
		mainBall = nullptr; //ya se borro la que habia
	}
}

int BallManager::shoot()
{

	std::cout << "SHOOOOO" << std::endl;
	std::cout << "my state is " << state << std::endl;
	if (state==MOVEBALL)
	{
		//Release ball
		mainBall->addForce({ 0,50,-50000 });
		//mainBall->addRelativeForce({ 0,500,-500000 });
		state = WAIT; //la pelota tiene que avisar de que se ha muerto a alguien en la escena con el on death? referencia en ball a ballmngr?
		mainBall->setState(state);

		ballsLeft--;
		return ballsLeft;
	}
	return -1;
}

void BallManager::loadlevel(int n)
{
	ballsLeft=ballsPerLevel[n];
	state = MOVEBALL;
	if (mainBall == nullptr)
	{
		int random = rand() % models.size();
		mainBall = models[random]->clone();
		psys->addToSystem(mainBall);
	}
}

void BallManager::briefwind()
{
	std::list <Object*> aux; aux.push_back(mainBall);
	psys->createBriefWind(mainBall->getPos(), aux);
}

