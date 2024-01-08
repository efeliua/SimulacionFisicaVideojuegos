#pragma once
#include "RigidBody.h"
#include <iostream>
class BallManager;
enum ballState { MOVEBALL, WAIT };
class Ball: public RigidBody
{
	public:
		Ball(BallManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color,physx::PxTransform tr=physx::PxTransform(Vector3(0,0,0)), bool model=false,float density=0.7 );
		Ball(BallManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, float size, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, float timeLife = 10, bool model = false, float Density = 0.15, float Dam = 0.998f);
		virtual ~Ball();
		inline ballState getState() { return state; }
		inline void setState(ballState s) { state = s; }
		virtual void integrate(double t);
		inline virtual Ball* clone() { return new Ball(ballMngr, gScene, gPhysics, color, size, rigidB->getGlobalPose(), rigidB->getLinearVelocity(), Vector3{0,0,0}, lifeTime, false, density); };
			//------------------------------get mass?
	protected:
		BallManager* ballMngr; //para poderle avisar cuando haya muerto
		ballState state;
		float rotation; //variable for a quick access to ball rotation (before shoot)
};

//rigidB->getGlobalPose().q.normalize() 