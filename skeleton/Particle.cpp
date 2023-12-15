#include "Particle.h"
#include "Constants.h"

Particle::Particle(Vector3 Pos, itemShape s)
{
	vel = Vector3(0, 0, 0);
	ac = Vector3(0, 0, 0); 
	damping = 0.998f;
	pose = physx::PxTransform(Pos);
	addShape(shapeType, 0.2);
	color = Vector4(120, 050, 060, 1);
	renderItem = new RenderItem(shape, &pose, color);
	lifeTime =remainingTime = 10;
	f = Vector3(0, 0, 0);
	mass = 2; massinv = 1 / mass;
	shapeType = s;

}

Particle::Particle(Vector4 Color, float Size, Vector3 pos, Vector3 Vel, Vector3 Ac, float time, bool Model, bool grav, float Mass, itemShape s, Vector3 boxSize, float Dam )
{
	model = Model;
	//render
	color = Color; 
	size = Size;
	shapeType = s;

	//tam
	if (size != 0) { recSize = Vector3(size, size, size); }
	else recSize = boxSize;

	if (!model) { 
		addShape(s, size, boxSize);
	
	renderItem = new RenderItem(shape, &pose, color); }

	//transform/movement
	pose = physx::PxTransform(pos);
	vel = Vel;
	ac = Ac;
	damping = Dam;
	//if (grav)ac.y += constants::generalGravity; //manual add gravity práctica 1/2

	mass = Mass; massinv = 1 / mass;

	//initial forces
	f = Vector3(0, 0, 0);

	//life
	lifeTime = remainingTime = time;
}

Particle::~Particle()
{
	if (!model) DeregisterRenderItem(renderItem);
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

void Particle::addShape(itemShape s, float size, Vector3 boxSize)
{
	switch (s)
	{
	case SPHERE:  shape = CreateShape(physx::PxSphereGeometry(size));  break;
	case BOX: 
		Vector3 s = Vector3(size, size, size);
		if (size == 0) s = boxSize;
		physx::PxBoxGeometry box(s/2);
		shape = CreateShape(box); break;
	}
}

