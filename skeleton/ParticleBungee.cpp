#include "ParticleBungee.h"

void ParticleBungee::updateForce(Object* particle, double t)
{
	Vector3 f = particle->getPos();
	f -= _other->getPos();

	//LEngth
}
