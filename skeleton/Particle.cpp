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
	f = Vector3(0, 0, 0);
	mass = 2; massinv = 1 / mass;
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
	//if (grav)ac.y += constants::generalGravity; //manual add gravity 

	mass = Mass; massinv = 1 / mass;

	//initial forces
	f = Vector3(0, 0, 0);

	//life
	lifeTime = remainingTime = time;
}

Particle::~Particle()
{
	renderItem->release();
}

void Particle::integrate(double t)
{
	//Fuerzas
	// Get the accel considering the force accum
	
	Vector3 resulting_accel = f * massinv;
	vel += resulting_accel * t; // Ex. 1.3 --> add acceleration
	vel *= powf(damping, t); // Exercise 1.3 --> add damping
	pose.p += vel * t;
	// Clear accum
	clearForce();

	//disminuye tiempo por vivir
	remainingTime -= t;
}

