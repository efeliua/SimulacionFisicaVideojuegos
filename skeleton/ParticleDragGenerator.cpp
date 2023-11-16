#include "ParticleDragGenerator.h"

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	//check that a particle has finite mass
	if (fabs(particle->getInvMass()) < 1e-10)
		return;
	//checks if its in the area
	
	if (isInside(particle->getPos()))
	{
		//compute the drag force
		Vector3 v = particle->getVel();
		Vector3 dif = windvel-v;
		Vector3 dragF = (_k1 * dif) + (_k2 * dif.magnitude() * dif);

		//Apply the drag force
		particle->addForce(dragF);
	}
}
