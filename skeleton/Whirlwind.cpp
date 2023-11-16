#include "Whirlwind.h"
void Whirlwind::updateForce(Particle* particle, double t)
{
	//check that a particle has finite mass
	if (fabs(particle->getInvMass()) < 1e-10)
		return;
	//checks if its in the area
	Vector3 p = particle->getPos();

	if (isInside(p))
	{
		//compute the wind velocity in that point 
		windvel = _k*Vector3((-(p.z-origin.z)), (-(p.y-origin.y)), (p.x-origin.x));
		ParticleDragGenerator::updateForce(particle, t); 
	}
}
