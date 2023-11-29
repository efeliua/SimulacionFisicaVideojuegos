#include "ParticleBungee.h"

void ParticleBungee::updateForce(Particle* particle, double t)
{
	Vector3 f = particle->getPos();
	f -= _other->getPos();

	//LEngth
}
