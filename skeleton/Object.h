#pragma once
#pragma once
#include "RenderUtils.hpp"
#include <vector>
#include <list>
//#include "core.hpp"
#include <PxPhysicsAPI.h>
#include "Constants.h"
enum itemShape { SPHERE, BOX };
class ParticleGenerator;
class Object
{
public:
	Object() {};
	Object(Vector4 color, float size, Vector3 Pos = Vector3{ 0,0,0 }, Vector3 Vel = Vector3{ 0,0,0 }, Vector3 Ac = Vector3{ 0,0,0 }, float timeLife = 10, bool model = false, bool gravity = true, float Mass = 1, itemShape s = SPHERE, Vector3 boxSize = Vector3{ 0,0,0 }, float Dam = 0.998f);

	virtual ~Object() {};
	virtual void integrate(double t) {};
	virtual inline bool timeLeft() { return remainingTime > 0; }; //same
	virtual inline bool insideBounds()=0;
	virtual Object* clone()=0;
	virtual inline Vector3 getPos()=0;
	virtual inline Vector3 getVel()=0;
	virtual inline float getMass()=0;
	virtual inline void addMass(float m) {}
	virtual inline float getInvMass() = 0;
	virtual std::list<Object*> onDeath()=0;
	virtual inline void setPos(Vector3 v) {}
	virtual inline void setVel(Vector3 v) {}
	virtual inline void setTimeLife(float t) { remainingTime = lifeTime = t; }
	virtual inline float getTimeLife() { return lifeTime; }
	virtual inline float getHeight()=0;
	virtual inline float getRecVolume() = 0;
	//Fuerzas
	virtual inline void clearForce()  { };
	virtual inline void addForce(const Vector3& force) {};
	virtual void addShape(itemShape s, float size, Vector3 boxSize = Vector3{ 0,0,0 }) {};
protected:
	RenderItem* renderItem;
	physx::PxShape* shape;
	Vector4 color;
	float lifeTime, remainingTime;
	bool model;
	ParticleGenerator* g; 
	itemShape shapeType;
};



