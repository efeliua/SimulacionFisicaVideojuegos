#include "Game.h"
#include "Explosion.h"
#include "RenderUtils.hpp"


Game::Game(physx::PxScene* scene, physx::PxPhysics* p)
{
	psys = new ParticleSystem(scene, p);
	ballMngr = new BallManager(psys, scene, p);
	boloMngr = new BoloManager(this, psys, scene, p);
	gScene = scene; gPhysics = p;
	currState = START;
	level = 0;
	points = 0;
	psys->createInfoPanel();

	ballsLeft = 0;
	totalTries = 0;
	win = false;
	highscore = 0;
	fillInfo();

	timeToDie = 5; //5 segundos de margen para saber si se ha muerto
	currentTime = 0; //tiempo desde que pierde la ultima pelota
}

void Game::keyPressed(unsigned char key)
{
	if (currState == START)
	{
		currentTime = 0;
		psys->destroyInfoPanel(); 
		info_text = " ";  info_text2 = " "; info_text3 = " "; info_text4 = " "; info_text5 = " "; info_text6 = " "; info_text7 = " "; info_text8 = " ";
		currState = PLAY;
		loadLevel(level);
	}
	else if (currState == END)
	{
		psys->createInfoPanel(),
		fillInfo();
		level = 0;
		boloMngr->clearScene(); if (points > highscore) { highscore = points; }
		points = 0; currState = START; win = false;
	}
	else
	{
		switch (toupper(key))
		{
		case ' ':
		{
			if (currState != WAITG)
			{
				int balls = ballMngr->shoot();
				if (balls == 0)currState = WAITG;
			}
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
		case 'E':
		{
			explode();
			break;
		}
		case 'V':
		{
			briefwind(Vector3(-200, 0, 0));
			break;
		}
		case 'B':
			briefwind(Vector3(200, 0, 0));
			break;
		default:
			break;
		}
	}
}

void Game::update(double t)
{
	psys->update(t);

	if (currState == WAITG)
	{
		if (ballMngr->noBallsLeft() == true)
		{
			currentTime += t;
			if (currentTime > timeToDie)
			{
				currState = END;
				endOfGame();
			}
		}
	}
}

void Game::loadLevel(int n)
{
	boloMngr->loadLevel(n);
	ballMngr->loadlevel(n);
}

void Game::endOfLevel()
{
	psys->shoot();
	level++;
	if (level < constants::LEVELS)
	{
		info_text = "PRESS ANY KEY TO START NEW LEVEL";
		currState = START; 
	}
	else
	{
		currState = END;
		win = true;
		endOfGame();
	}
}

void Game::explode()
{
	if (points >= 20)
	{
		std::cout << "EXPLOSION" << std::endl;
		boloMngr->explode(ballMngr->getMainBallPos());
		points -= 20;
	}
}

void Game::briefwind(Vector3 d)
{
	if (points >= 5)
	{
		std::cout << "BRIEF WIND" << std::endl;
		ballMngr->briefwind(d);
		points -= 5;
	}
}

void Game::endOfGame()
{
	totalTries++;
	if (win)
	{
		info_text = "YOU WON! :D";
		info_text2 = "Press any key to go again. ";
		psys->shoot();
	}
	else
	{
		info_text = "YOU LOST :C";
		info_text2 = "Press any key to go again. ";
	}
}

void Game::fillInfo()
{
	info_text = "WELCOME TO BOLOS :D";
	info_text2 = " ";
	info_text3 = "THERE ARE 3 TYPES OF BALLS BY MASS";
	info_text4 = "SHOOT THE BALL: SPACEBAR";
	info_text5 = "WIND FOR YOUR BALL (5 points): V(left), B(right)";
	info_text6 = "MAKE A BIG EXPLOSION  (20 points): E";
	info_text8 = "PRESS ANY KEY TO START";
}
