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

	timeToDie = 10; //5 segundos de margen para saber si se ha muerto
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
		points = 0; currState = START;
	}
	else
	{
		switch (toupper(key))
		{
		case ' ':
		{
			int balls=ballMngr->shoot();
			if (balls == 0)currState = WAITG;
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
			briefwind();
			break;
		}
		case 'B':
			ballMngr->rotateMainBall(10);
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
	if (points >= 10)
	{
		boloMngr->explode(ballMngr->getMainBallPos());
		points -= 10;
	}
}

void Game::briefwind()
{
	if (points >= 5)
	{
		ballMngr->briefwind();
		points -= 5;
	}
}

void Game::endOfGame()
{
	totalTries++;
	if (win)
	{
		info_text = "YOU WON! \n Press any key to go again. ";
		psys->shoot(2);
		psys->shoot();
	}
	else
	{
		info_text = "YOU LOST :C. \n Press any key to try again!";
	}
}

void Game::fillInfo()
{
	info_text = "WELCOME TO BOLOS :D";
	info_text2 = " ";
	info_text3 = "PRESS THE SPACE BAR TO SHOOT THE BALL";
	info_text4 = "THERE ARE 3 TYPES OF BALLS BY MASS";
	info_text5 = "BRIEF WIND FOR YOUR BALL 2S: 5 points";
	info_text6 = "MAKE A BIG EXPLOSION: 30 points";
	info_text8 = "PRESS ANY KEY TO START";
}
