#pragma once
#include "RigidBody.h"
class BoloManager;
class Bolo: public RigidBody
{
	public:
		Bolo(BoloManager* b, physx::PxScene* scene, physx::PxPhysics* phys, physx::PxTransform Pos, int size);
		Bolo(BoloManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, float size, physx::PxTransform Pos, float timeLife = 10, bool model = false);
		virtual inline bool insideBounds(){ Vector3 pose = rigidB->getGlobalPose().p; return (pose.x > constants::limIzBo && pose.x<constants::limDcBo&& pose.y>constants::limInBo && pose.y<constants::limSBo&& pose.z>constants::limCBo && pose.z < constants::limLBo); };
		virtual ~Bolo();

protected:
	BoloManager* boloMngr;
};

