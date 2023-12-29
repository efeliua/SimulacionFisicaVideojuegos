#include "Game.h"

Game::Game(physx::PxScene* scene, physx::PxPhysics* p)
{
	psys = new ParticleSystem(scene, p);
	ballMngr = new BallManager(psys, scene, p);
	boloMngr = new BoloManager(this, psys, scene, p);
	gScene = scene; gPhysics = p;
	currState = START;
	points = 0;
}

void Game::keyPressed(unsigned char key)
{
	switch (toupper(key))
	{
	case ' ':
	{
		ballMngr->shoot();
		break;
	}
	case 'K':
	{
		ballMngr->moveBall(-1, 0);
		break;
	}
	case 'L':
	{
		ballMngr->moveBall(1, 0);
		break;
	}
	default:
		break;
	}
}

void Game::update(double t)
{
	psys->update(t);
}

void Game::createLevel()
{
}

void Game::endOfLevel()
{
	//puntos bla
	psys->shoot();
}
