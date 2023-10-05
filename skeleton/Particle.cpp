#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Ac, float Mass, float Dam)
{
	vel = Vel;
	pose = physx::PxTransform(Pos);
	damping = Dam;
	ac = Ac;
	mass = Mass;
	shape = CreateShape(physx::PxSphereGeometry(0.2));
	color = Vector4(120, 050, 060, 1);
	renderItem = new RenderItem(shape, &pose, color);
}

Particle::Particle(Vector3 Pos)
{
	vel = Vector3(0, 0, 0);
	ac = Vector3(0, 0, 0);
	damping = 0.998f;
	pose = physx::PxTransform(Pos);
	shape = CreateShape(physx::PxSphereGeometry(0.2));
	color = Vector4(120, 050, 060, 1);
	renderItem = new RenderItem(shape, &pose, color);
}

Particle::~Particle()
{
	renderItem->release();
}

void Particle::integrate(double t)
{
	//update position
	pose.p += vel * t;
	//update linear velocity
	vel += ac * t;
	//impose damping
	vel *= powf(damping, t);

	//si se requiere posteriormente, borrar una vez ha alcanzado x altura/ velocidad
}
