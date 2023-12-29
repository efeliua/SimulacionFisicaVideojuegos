//Eva Feliu Ar�jola
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Game.h"
#include <iostream>

std::string display_text = "PRACTICA5 5: S�LIDO R�GIDO";
std::string points_text = "POINTS: ";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

//particles system-> crear si se quiere 
ParticleSystem* psys;

//juego 
Game* game;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, 0.0f, 0.0f); //grav def (a 0 para que no se duplique con la fuerza de gravedad definida en ParticleSystem)
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	//crear si se quieren ver cosas
	//psys = new ParticleSystem(gScene, gPhysics);
	game = new Game(gScene, gPhysics);

	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	if(psys!=nullptr)psys->update(t); //si existiera un sistema manual de pruebas a�adido (ahora mismo no existe)
	if (game != nullptr)game->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	//delete(psys);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	if (game == nullptr)  //show de generadores/fuerzas sin juego etc (p1-p5)
	{
		switch(toupper(key))
		{
			case 'F':
			{
				psys->shoot(); //fireworks
				break;
			}
			case 'E':
			{
				psys->explode(); //explosion force generator 
				break;
			}
			case 'K':
			{
				psys->addK();
				break;
			}
			case 'G':
			{
				psys->activateFG("gravFG");
				break;
			}
			case 'H':
			{
				psys->activateFG("whirlwindFG"); break;
			}
			case 'V':
			{
				psys->activateFG("dragFG"); break;
			}
			case 'I':
			{
				psys->seeControls(); break;
					break;
			}
			case 'B':
			{
				psys->createBriefWind(); break;
			}
			case 'M':
			{
				psys->addMass();
			}
			case ' ':
			{
				psys->shootProjectile(CANON);
			}
			default:
				break;
		}
	}
	else
	{
		game->keyPressed(key);
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}