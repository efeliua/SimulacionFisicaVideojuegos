#include "Ball.h"
#include <iostream>
#include "BallManager.h"

Ball::Ball( BallManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color,physx::PxTransform tr):RigidBody(scene, phys,color,2, tr, {0,0,0}, {0,0,0},10, false, 0.7)
{
	ballMngr = b;
}

Ball::~Ball()
{
	ballMngr->onBallDeath();
}
