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
	virtual ~Object() {};
	virtual void integrate(double t) {};
	virtual inline bool timeLeft() { return remainingTime > 0; }; 
	virtual inline bool insideBounds()=0;
	virtual Object* clone()=0;
	virtual inline Vector3 getPos()=0;
	virtual inline Vector3 getVel()=0;
	virtual inline float getMass()=0;
	virtual inline void addMass(float m) {}
	virtual inline physx::PxShape* getShape() { return shape; }
	virtual inline float getInvMass() = 0;
	virtual std::list<Object*> onDeath()=0;
	virtual inline void setPos(Vector3 v) {}
	virtual inline void setVel(Vector3 v) {}
	virtual inline void setTimeLife(float t) { remainingTime = lifeTime = t; }
	virtual inline float getTimeLife() { return lifeTime; }
	virtual inline float getHeight()=0;
	virtual inline float getRecVolume() = 0;
	virtual inline void clearForce()  { };
	virtual inline void addForce(const Vector3& force) {};
	virtual void addShape(itemShape s, float size, Vector3 boxSize = Vector3{ 0,0,0 }) {};
protected:
	RenderItem* renderItem=nullptr;
	physx::PxShape* shape;
	Vector4 color;
	float lifeTime, remainingTime;
	bool model;
	ParticleGenerator* g; 
	itemShape shapeType;
};



