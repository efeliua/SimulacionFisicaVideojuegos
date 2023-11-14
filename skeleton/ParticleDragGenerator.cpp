#include "ParticleDragGenerator.h"

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	//check that a particle has finite mass
	if (fabs(particle->getInvMass()) > 1e10)
		return;
	//checks if its in the area
	
	if (isInside(particle->getPos()))
	{
		//compute the drag force
		Vector3 v = particle->getVel();
		float drag_coef = v.normalize();
		Vector3 dragF;
		drag_coef = (_k1 * drag_coef) + (_k2 * drag_coef * drag_coef);
		dragF = -v * drag_coef;

		//Apply the drag force
		//std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << std::endl;
		particle->addForce(dragF);
	}
}
