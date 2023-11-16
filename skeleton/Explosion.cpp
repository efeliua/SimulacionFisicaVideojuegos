#include "Explosion.h"
#include <cmath>
void Explosion::updateForce(Particle* particle, double time)
{
	//check that a particle has finite mass
	if (fabs(particle->getInvMass()) < 1e-10)
		return;

	//checks if its in the area
	Vector3 p = particle->getPos();
	Vector3 dif = p - origin;
	
	if (dif.magnitude() <= radius)
	{
		Vector3 dragF = (k / (powf(dif.magnitude(), 2)) * dif * (exp(-_t / tau)));
		particle->addForce(dragF);
	}
	
}
