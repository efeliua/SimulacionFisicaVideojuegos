#pragma once
#include "ParticleSystem.h"
#include "BallManager.h"
#include "BoloManager.h"
enum gameState {START, PLAY, END};
class Game
{
protected:
	int points;
	int round;
	BallManager* ballMngr;
	BoloManager* boloMngr;
	ParticleSystem* psys; //lo creo o lo recibo? supongo que lo creo
	gameState currState;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;

public:
	Game(physx::PxScene* scene, physx::PxPhysics* p);
	~Game() { delete (psys); };
	void keyPressed(unsigned char key);
	void update(double t);
	void createLevel();
	void endOfLevel();
	inline void addPoints(int p) { points += p; }
	inline int getPoints(){ return points; }
};

