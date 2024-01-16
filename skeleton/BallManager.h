#pragma once
#include "Ball.h"
#include "ParticleSystem.h"
#include <vector>

extern int ballsLeft;

class BallManager
{
protected:
	ParticleSystem* psys;
	Ball* mainBall;
	std::vector<Ball*> balls;
	std::vector <Ball*> models;
	ballState state;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
	std::vector<int> ballsPerLevel;
	bool playing;
public:

	BallManager(ParticleSystem* p,physx::PxScene* gScene, physx::PxPhysics* gPhysics);
	~BallManager();
	void onBallDeath();
	int shoot();
	void loadlevel(int n);
	inline Vector3 getMainBallPos() { return mainBall->getPos(); }
	inline bool noBallsLeft() { return mainBall == nullptr; }
	void briefwind(Vector3 d);
	inline void moveBall(int dirx, int diry) { if (state==MOVEBALL) { mainBall->setPos(mainBall->getPos()+Vector3(dirx,diry,0)); } }
};

