#pragma once
#include "RenderUtils.hpp"
#include <vector>
#include <list>
//#include "core.hpp"
#include <PxPhysicsAPI.h>
class ParticleGenerator;
class Particle
{
	public: 
		Particle(Vector3 Pos, Vector3 Vel, Vector3 Ac,bool model=false,bool gravity=true, float Mass=0,float Dam = 0.998f);
		Particle(Vector3 Pos=Vector3{0,0,0});
		virtual ~Particle(); // deregistrar el objeto RenderItem 
		virtual void integrate(double t);
		inline bool timeLeft() { return remainingTime > 0; }; //or set in system when creating 
		inline bool insideBounds() { return (pose.p.x > -100 && pose.p.x<100 && pose.p.y>-100 && pose.p.y<100 && pose.p.z>-100 && pose.p.z < 100); };//create bounding box
		//virtual Particle* clone();
		inline Vector3 getPos() { return pose.p; }
		inline Vector3 getVel() { return vel; } //para la inicializacion desde particulas modelo
		virtual std::list<Particle*> onDeath() { std::list<Particle*> listavacia{};  return listavacia; };
		inline void setPos(Vector3 v) { pose.p = v; }
		ParticleGenerator* getGen() { return g; }
	protected:
		RenderItem *renderItem;
		physx::PxShape* shape;
		Vector4 color;
		physx::PxTransform pose; 
		Vector3 vel;
		float damping;
		Vector3 ac;
		float mass;
		float lifeTime, remainingTime;
		bool model;
		ParticleGenerator* g;
};

