#include "BallManager.h"
#include <iostream>

BallManager::BallManager(ParticleSystem* p, physx::PxScene* scene, physx::PxPhysics* physics)
{
	psys = p;
	gScene = scene;
	gPhysics = physics;

	//create main ball
	mainBall = new Ball(this, scene, physics, Vector4(0.4, 0.5, 3, 1),{ 0, 0,0 }); //hacer clone con bolas modelo bestie
	psys->addToSystem(mainBall);
	state = MOVEBALL;
}

void BallManager::onBallDeath()
{
	//if vector balls es 0
	//ya borra la ball el particle system tecnicamente
	//Aqui lo unico seria una nueva bola
	//create main ball
	mainBall = new Ball(this,gScene, gPhysics, Vector4(0.4, 0.5, 3, 1), { 0, 0,0 }); //hacer clone con bolas modelo bestie
	psys->addToSystem(mainBall);
	state = MOVEBALL;
}


void BallManager::shoot()
{
	std::cout << "SHOOOOO" << std::endl;
	std::cout << "my state is " << state << std::endl;
	if (state==MOVEBALL)
	{
		//Release ball
		mainBall->addForce({ 0,500,-2000000 });
		state = WAIT; //la pelota tiene que avisar de que se ha muerto a alguien en la escena con el on death? referencia en ball a ballmngr?
	}
}
