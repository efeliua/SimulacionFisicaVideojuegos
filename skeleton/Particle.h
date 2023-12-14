#pragma once
#include "RenderUtils.hpp"
#include <vector>
#include <list>
//#include "core.hpp"
#include <PxPhysicsAPI.h>
#include "Constants.h"
#include "Object.h"
class ParticleGenerator;
//enum itemShape{SPHERE, BOX};
class Particle: public Object
{
	public: 
		Particle(Vector3 Pos=Vector3{0,0,0}, itemShape s=SPHERE);
		Particle(Vector4 color, float size, Vector3 Pos = Vector3{ 0,0,0 }, Vector3 Vel = Vector3{ 0,0,0 }, Vector3 Ac = Vector3{ 0,0,0 }, float timeLife = 10, bool model = false, bool gravity = true, float Mass = 1, itemShape s = SPHERE, Vector3 boxSize = Vector3{ 0,0,0 },float Dam = 0.998f);
		virtual ~Particle(); // deregistrar el objeto RenderItem 
		virtual void integrate(double t);
		//inline bool timeLeft() { return remainingTime > 0; }; 
		virtual inline bool insideBounds() { return (pose.p.x > constants::limIz && pose.p.x<constants::limDc && pose.p.y>constants::limIn && pose.p.y<constants::limS && pose.p.z>constants::limC && pose.p.z < constants::limL); };//create bounding box
		virtual Particle* clone() { return new Particle(color, size, pose.p, vel, ac, lifeTime, false, true, mass, shapeType); };
		virtual inline Vector3 getPos() { return pose.p; }
		virtual inline Vector3 getVel() { return vel; } 
		virtual inline float getMass() { return mass; };
		virtual inline void addMass(float m) { mass += m; }
		virtual inline float getInvMass() { return massinv; }
		virtual std::list<Object*> onDeath() { std::list<Object*> listavacia{};  return listavacia; };// object -----------------
		virtual inline void setPos(Vector3 v) { pose.p = v; }
		virtual inline void setVel(Vector3 v) { vel = v; }
		//inline void setTimeLife(float t) { remainingTime =lifeTime=t; }
		//inline float getTimeLife() { return lifeTime; }
		virtual inline float getHeight() { return recSize.y; }
		virtual inline float getRecVolume() { return (recSize.x * recSize.y * recSize.z); }
		//Fuerzas
		virtual inline void clearForce() { f *= 0; };
		virtual inline void addForce(const Vector3& force) { f += force; };
		virtual void addShape(itemShape s, float size, Vector3 boxSize=Vector3{0,0,0});
	protected:
		//RenderItem *renderItem;
		//physx::PxShape* shape;
		//Vector4 color;
		physx::PxTransform pose; 
		float size;
		Vector3 vel;
		float damping;
		Vector3 ac;
		float mass;
		//float lifeTime, remainingTime;
		//bool model;
		//ParticleGenerator* g;
		//Fuerzas
		float massinv;
		Vector3 f; //acumulador de fuerzas
		//itemShape shapeType;
		Vector3 recSize;
};

