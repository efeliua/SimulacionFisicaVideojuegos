#include "Ball.h"
#include <iostream>
#include "BallManager.h"

Ball::Ball( BallManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color,physx::PxTransform tr,  bool Model,float Density):RigidBody(scene, phys,color,2, tr, {0,0,0}, {0,0,0},8, Model,Density)
{
	ballMngr = b;
	state = MOVEBALL; 
	density = Density;
}

Ball::Ball(BallManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, float size, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, float timeLife, bool model, float Density, float Dam):RigidBody(scene, phys, color, size, Pos, LinearVel, AngularVel,timeLife, model,Density, SPHERE) 
{
	ballMngr = b;
	state = MOVEBALL;
	density = Density;
}

Ball::~Ball()
{
	if(!model)ballMngr->onBallDeath();
	state = MOVEBALL;
}
void Ball::integrate(double t)
{
	//disminuye tiempo por vivir solo si ya está en movimiento
	if(state!=MOVEBALL)remainingTime -= t;
}
