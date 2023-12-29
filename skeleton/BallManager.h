#pragma once
#include "Ball.h"
#include "ParticleSystem.h"
#include <vector>
enum ballState {MOVEBALL, WAIT};

class BallManager
{
protected:
	ParticleSystem* psys;
	Ball* mainBall;
	std::vector<Ball> balls;
	ballState state;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
public:

	BallManager(ParticleSystem* p,physx::PxScene* gScene, physx::PxPhysics* gPhysics);
	void onBallDeath();
	void shoot();
	inline void moveBall(int dirx, int diry) { if (state==MOVEBALL) { mainBall->setPos(mainBall->getPos()+Vector3(dirx,diry,0)); } }
};

