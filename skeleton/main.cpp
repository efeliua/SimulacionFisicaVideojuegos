//Eva Feliu Aréjola
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "ParticleSystem.h"
#include <iostream>

std::string display_text = "PRACTICA5 5: SÓLIDO RÍGIDO";


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

//vector de particulas
std::vector<Particle*> particles;
//a parametrizar para cada particula

//particles system
ParticleSystem* psys;


//vector de objetos en escena (no se si physx lo tiene ya)
//std::vector <PxRigidDynamic> dinSolids; //A los que quiero que afecten fuerzas

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
	psys = new ParticleSystem(gScene, gPhysics);

	//suelo
		//generar
	PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
		//pintar
	RenderItem* item;
	item = new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 });
	
	//ejemplo de actor dinamico 
	/*
	PxRigidDynamic* new_solid;
	new_solid = gPhysics->createRigidDynamic({ -70,200,70 });
	new_solid->setLinearVelocity({ 0,5, 0 });
	new_solid->setAngularVelocity({ 0,0,0 });
	PxShape* shape_ad = CreateShape(PxBoxGeometry(5, 5, 5));
	new_solid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
	gScene->addActor(*new_solid);
	RenderItem* dynamic_item;
	dynamic_item = new RenderItem(shape_ad, new_solid, { 0.8,0.8,0.8,1 });
	*/
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	psys->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	//for (int i = 0; i < particles.size(); ++i){delete(particles[i]);}

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	delete(psys);
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'C':
	{
		psys->shootProjectile(CANON);
		break;
	}
	case 'T': 
	{
		psys->shootProjectile(TANQUE);
		break;
	}
	case ' ':
	{
		psys->shootProjectile(BALA);
		break;
	}
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
	default:
		break;
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