#include "Particle.h"
#include "Constants.h"

Particle::Particle(Vector3 Pos)
{
	vel = Vector3(0, 0, 0);
	ac = Vector3(0, 0, 0); 
	damping = 0.998f;
	pose = physx::PxTransform(Pos);
	shape = CreateShape(physx::PxSphereGeometry(0.2));
	color = Vector4(120, 050, 060, 1);
	renderItem = new RenderItem(shape, &pose, color);
	lifeTime =remainingTime = 10;
}

Particle::Particle(Vector4 Color, float Size, Vector3 pos, Vector3 Vel, Vector3 Ac, float time, bool model, bool grav, float Mass, float Dam )
{
	//render
	color = Color; 
	size = Size;
	if (!model) { shape = CreateShape(physx::PxSphereGeometry(size)); renderItem = new RenderItem(shape, &pose, color); }

	//transform/movement
	pose = physx::PxTransform(pos);
	vel = Vel;
	ac = Ac;
	damping = Dam;
	if (grav)ac.y += constants::generalGravity;

	mass = Mass;

	//life
	lifeTime = remainingTime = time;
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

	//disminuye tiempo por vivir
	remainingTime -= t;
}

