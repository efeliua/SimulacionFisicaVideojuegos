#pragma once
#include "RigidBody.h"
class BallManager;
class Ball: public RigidBody
{
	public:
		Ball(BallManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color,physx::PxTransform tr=physx::PxTransform(Vector3(0,0,0)) );
		Ball(BallManager* b,physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, float size, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, float timeLife = 10, bool model = false, float Density = 0.15, float Dam = 0.998f): RigidBody(scene, phys, color, size, Pos, timeLife, model, SPHERE){}
		virtual ~Ball();
	protected:
		BallManager* ballMngr; //para poderle avisar cuando haya muerto
};

