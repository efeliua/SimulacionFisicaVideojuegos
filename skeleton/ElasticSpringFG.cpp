#include "ElasticSpringFG.h"

void ElasticSpringFG::updateForce(Particle* particle, double time)
{
	Vector3 relative_pos_vector = _other->getPos() - particle->getPos(); //oosicion relativa respecto a la otra particula
	if (relative_pos_vector.magnitude() > _resting_length) //si es menor que la resting length no se añadirá la fuerza
	{
		SpringForceGenerator::updateForce(particle, time);
	}
}
