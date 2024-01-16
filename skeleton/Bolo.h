#pragma once
#include "RigidBody.h"
#include <iostream>
class BoloManager;
class Bolo: public RigidBody
{
	public:
		Bolo(BoloManager* b, physx::PxScene* scene, physx::PxPhysics* phys, float size, physx::PxTransform Pos, bool model=false, bool muelle=false);
		Bolo(BoloManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, float size, physx::PxTransform Pos,  bool model = false, float timeLife = 10, bool muelle=false);
		virtual inline bool insideBounds(){ Vector3 pose = rigidB->getGlobalPose().p; return (pose.x > constants::limIzBo && pose.x<constants::limDcBo&& pose.y>constants::limInBo && pose.y<constants::limSBo&& pose.z>constants::limCBo && pose.z < constants::limLBo); };
		virtual Bolo* clone(){ return new Bolo(boloMngr, gScene, gPhysics, color, size, rigidB->getGlobalPose(), false, lifeTime, muelle); }
		virtual ~Bolo();
		void die() {remainingTime = 0; }
		void virtual integrate(double t) {}; //no lifetime
		bool muelle;
		inline bool isMuelle() { return muelle; }
		inline void setMuelle(bool b) { muelle = b; }
protected:
	BoloManager* boloMngr;
};

