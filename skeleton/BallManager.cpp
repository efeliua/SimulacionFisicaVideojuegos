#include "BallManager.h"
#include <iostream>
#include "RenderUtils.hpp"
BallManager::BallManager(ParticleSystem* p, physx::PxScene* scene, physx::PxPhysics* physics)
{
	psys = p;
	gScene = scene;
	gPhysics = physics;
	mainBall = nullptr;

	//create  balltypes models
	Ball* b=new Ball(this, scene, physics, Vector4(0.81, 0.06,0.12,1), { 0, 0,0 }, true, 0.15);
	Ball* b2 = new Ball(this, scene, physics, Vector4(1,1,0,1), { 0, 0,0 }, true,0.17);
	Ball* b3 = new Ball(this, scene, physics, Vector4(0.4, 0.8, 3, 1), { 0, 0,0 }, true,0.1);

	models.push_back(b);models.push_back(b2); models.push_back(b3);

	//balls per level
	ballsPerLevel.push_back(3); ballsPerLevel.push_back(3); ballsPerLevel.push_back(5); ballsPerLevel.push_back(4);

	playing = true;
}

BallManager::~BallManager()
{
	playing = false;
	//borrar modelos 
	for (auto it = balls.begin(); it != balls.end();)
	{
		delete(*it);
		it = balls.erase(it);
	}

}
//si no quedan bolas disponibles la ponemos a nula, sino la regeneramos
void BallManager::onBallDeath()
{
	if (playing&&ballsLeft > 0)
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

//disparo de la mainBall en escena
int BallManager::shoot()
{
	if (state==MOVEBALL)
	{
		std::cout << "SHOOT" << std::endl;
		//Release ball
		float forward;
		float bMass = mainBall->getMass();
		//el jugador tirara con mas fuerza una pelota que pese mas para que llegue mas lejos
		if (bMass > 5.5)forward = -80000;
		else if (bMass > 4)forward = -70000;
		else forward = -60000;
		mainBall->addForce({ 0,50,forward});
		state = WAIT; 
		mainBall->setState(state);

		ballsLeft--;
		return ballsLeft;
	}
	return -1;
}

//se cargará una nueva ball si no queda una escena y se recargarán las bolas por nivel
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

//se inflinge un viento que afectará a la pelota en escena (hacia la derecha o izquierda dep del input)
void BallManager::briefwind(Vector3 d)
{
	std::list <Object*> aux; aux.push_back(mainBall);
	psys->createBriefWind(mainBall->getPos(), aux, d);
}

