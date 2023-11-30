#include "GravityForceGenerator.h"
#include <cmath>

void GravityForceGenerator::updateForce(Particle* particle, double t)
{
	//check that a particle has finite mass
	if ((!_active) || (fabs(particle->getInvMass()) < 1e-10))
		return;
	///aply the mass scaled gravity
	particle->addForce(_grav * particle->getMass());
}
