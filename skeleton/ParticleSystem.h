#pragma once
#include <list>
#include "GaussianParticleGenerator.h"
#include "FireworkGenerator.h"
#include "ParticleForceRegistry.h"
#include "Projectile.h"
#include "PxPhysicsAPI.h"
class ParticleSystem
{
protected:
	std::list <Object*> particles;
	std::list <Object*> modelParticles;
	std::list <ParticleGenerator*> particles_generators;
	std::list <ForceGenerator*> force_generators;
	FireworkGenerator* fireGen;
	ParticleForceRegistry* pfRegistry;
	Particle* changeMassP;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;

public:
	ParticleSystem(physx::PxScene*, physx::PxPhysics*);
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem();
	void generateFG();
	void generateGS();
	void generateSolidScene();
	void generateTestStaticParticles();
	void generateTestDynamicParticles();
	void addForceGenerators(std::list <Object*> p);
	void addSingleForceGeneratorToAll(ForceGenerator* f);
	void shoot();
	void explode();
	void shootProjectile(type t);
	void generatespringDemo();
	void addK();
	void addMass() ;
	void activateFG(std::string name);
	void seeControls();
	void createBriefWind();
	void createFloor();
	void createGameFloor();
	inline void addToSystem(std::list<Object*> list) { for (auto e : list) { particles.push_back(e);} addForceGenerators(list); }
	inline void addToSystem(Object* o) { particles.push_back(o); std::list<Object*> aux; aux.push_back(o); addForceGenerators(aux); };
};

