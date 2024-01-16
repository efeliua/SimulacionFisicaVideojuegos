#pragma once
#include "ParticleSystem.h"
#include "BallManager.h"
#include "BoloManager.h"
enum gameState {START, PLAY, WAITG, END};
extern int points; //ahora main y game saben ._.
extern int highscore;
extern int level;
//extern int ballsLeft;
extern std::string info_text;
extern std::string info_text2;
extern std::string info_text3;
extern std::string info_text4;
extern std::string info_text5;
extern std::string info_text6;
extern std::string info_text7;
extern std::string info_text8;


class Game
{
protected:
	int round;
	BallManager* ballMngr;
	BoloManager* boloMngr;
	ParticleSystem* psys; 
	gameState currState;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
	bool win;
	int totalTries;
	float timeToDie, currentTime;
public:
	Game(physx::PxScene* scene, physx::PxPhysics* p);
	~Game() { ballsLeft = 0;   delete (psys); delete(ballMngr); delete(boloMngr); };
	void keyPressed(unsigned char key);
	void update(double t);
	void loadLevel(int n);
	void endOfLevel();
	void explode();
	void briefwind(Vector3 d);
	inline void addPoints(int p) { points += p; }
	inline int getPoints(){ return points; }
	void endOfGame();
	void fillInfo();
};

