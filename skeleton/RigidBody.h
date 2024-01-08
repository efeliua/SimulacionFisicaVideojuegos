#pragma once
#include "Object.h"
#include <PxPhysicsAPI.h>
#include <math.h>
class RigidBody: public Object
{
public:
	RigidBody() {};
	RigidBody(physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, float size,physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, float timeLife = 10, bool model = false, float Density = 0.15, itemShape s = SPHERE, Vector3 boxSize = Vector3{ 0,0,0 }, float Dam = 0.998f);
	RigidBody(physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, float size, physx::PxTransform Pos, float timeLife = 10, bool model = false,  itemShape s = SPHERE, Vector3 boxSize = Vector3{ 0,0,0 });
	virtual ~RigidBody();
	virtual void integrate(double t);
	virtual inline bool insideBounds() { Vector3 pose = rigidB->getGlobalPose().p; return (pose.x > constants::limIz && pose.x<constants::limDc&& pose.y>constants::limIn && pose.y<constants::limS&& pose.z>constants::limC && pose.z < constants::limL); };//create bounding box
	virtual RigidBody* clone() { return new RigidBody(gScene, gPhysics, color, size, rigidB->getGlobalPose(), rigidB->getLinearVelocity(), Vector3{0,0,0}, lifeTime, false, rigidB->getMass(), shapeType); };
	virtual inline Vector3 getPos() { if (rigidBstatic != NULL) return rigidBstatic->getGlobalPose().p;  return rigidB->getGlobalPose().p; }
	virtual inline Vector3 getVel() { return rigidB->getLinearVelocity(); }
	virtual inline float getMass() {return rigidB->getMass(); };
	virtual inline float getInvMass() { return rigidB->getInvMass(); }
	virtual std::list<Object*> onDeath() { std::list<Object*> listavacia{};  return listavacia; };
	virtual void setPos(Vector3 v);
	virtual inline void setVel(Vector3 v) { rigidB->setLinearVelocity(v); }
	virtual inline float getHeight() { return (rigidB->getWorldBounds().maximum.y - rigidB->getWorldBounds().minimum.y); }
	virtual inline float getRecVolume() { Vector3 rec = rigidB->getWorldBounds().getDimensions(); return rec.x * rec.y * rec.z; }
	virtual inline void addForce(const Vector3& force) { if (rigidB != NULL) rigidB->addForce(force); };
	virtual void addShape(itemShape s, float size, Vector3 boxSize = Vector3{ 0,0,0 });
	void rotateXAxis(float degToRot);
protected:
	physx::PxRigidDynamic* rigidB;
	physx::PxRigidStatic* rigidBstatic; 
	physx::PxScene* gScene;
	physx::PxPhysics* gPhysics;
	float size;
	Vector3 recSize;
	float density;
};

