#pragma once
#include <list>
#include "GaussianParticleGenerator.h"
#include "FireworkGenerator.h"
#include "ParticleForceRegistry.h"
#include "Projectile.h"
#include "PxPhysicsAPI.h"
#include "RigidBody.h"
struct MuellePair
{
	std::pair <Object*, Object* > pair;
	std::pair<FRPair, FRPair> fgpairs;
};
class ParticleSystem
{
protected:
	std::list <Object*> particles;
	std::list <Object*> modelParticles;
	std::list <ParticleGenerator*> particles_generators;
	std::list <ForceGenerator*> force_generators;
	FireworkGenerator* fireGen;
	FireworkGenerator* fireGen2;	FireworkGenerator* fireGen3;
	ParticleForceRegistry* pfRegistry;
	Particle* changeMassP;
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
	RigidBody* infoPanel;
	std::vector<MuellePair> connected;

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
	void addSingleForceGeneratorToSome(ForceGenerator* f, std::list <Object*>p);
	void shoot();
	void shoot(int n);
	void explode(Vector3 pos= Vector3(0, 0, 0));
	void explode(Vector3 pos, std::list <Object*> p);
	void addMuelle(Object* a, Object* b);
	void deleteMuelle(Object* a);

	void shootProjectile(type t);
	void generatespringDemo();
	void addK();
	void addMass() ;
	void activateFG(std::string name);
	void seeControls();
	void createBriefWind();
	void createBriefWind(Vector3 pos, std::list <Object*> p, Vector3 dir);
	void createFloor();
	void createGameScene();
	void createInfoPanel();
	void destroyInfoPanel() { delete(infoPanel); infoPanel = nullptr; }
	inline void addToSystem(std::list<Object*> list) { for (auto e : list) { particles.push_back(e);} addForceGenerators(list); }
	inline void addToSystem(Object* o) { particles.push_back(o); std::list<Object*> aux; aux.push_back(o); addForceGenerators(aux); };
	
};

