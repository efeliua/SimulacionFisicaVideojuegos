#include "Particle.h"
#include "Constants.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Ac, bool model,bool grav, float Mass, float Dam) //color, radio y shape 
{
	vel = Vel;
	pose = physx::PxTransform(Pos);
	damping = Dam;
	ac = Ac; //poner ac gravedad de base para luego si hay que sumar ac 
	if (grav)ac.y += constants::generalGravity;
	mass = Mass;
	if (!model) //solo se renderiza si no es una particula modelo
	{
		shape = CreateShape(physx::PxSphereGeometry(0.2));
		color = Vector4(120, 050, 060, 1);
		renderItem = new RenderItem(shape, &pose, color);
	}

	lifeTime = remainingTime = 2; //startear elsewhere
}

Particle::Particle(Vector3 Pos)
{
	vel = Vector3(0, 0, 0);
	ac = Vector3(0, 0, 0); //w/o 
	damping = 0.998f;
	pose = physx::PxTransform(Pos);
	shape = CreateShape(physx::PxSphereGeometry(0.2));
	color = Vector4(120, 050, 060, 1);
	renderItem = new RenderItem(shape, &pose, color);
	lifeTime = remainingTime = 10;

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
	//remainingTime--;
	remainingTime -= t;
}
