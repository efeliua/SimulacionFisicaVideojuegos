#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel)
{
	vel = Vel;
	pose = physx::PxTransform(Pos);

	shape = CreateShape(physx::PxSphereGeometry(5));
	color = Vector4(120, 050, 060, 0);
	renderItem = new RenderItem(shape, &pose, color);
}

Particle::~Particle()
{
	renderItem->release();
}

void Particle::integrate(double t)
{
	//damping, blablabla
	pose.p+= vel*t;
}
