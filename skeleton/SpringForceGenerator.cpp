#include "SpringForceGenerator.h"
SpringForceGenerator::SpringForceGenerator(double t,double k, double resting_length, Particle* other):ForceGenerator(t)
{
	_k = k;
	_resting_length = resting_length;
	_other = other;
	setName("springFG");
}
void SpringForceGenerator::updateForce(Particle* particle, double t)
{
	//Particle is the particle to apply the force
	Vector3 relative_pos_vector = _other->getPos() - particle->getPos(); //oosicion relativa respecto a la otra particula
	Vector3 force;

	//normalize: Normalize the relative_pos_vector and return its length
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;

	force = relative_pos_vector * delta_x * _k;
	particle->addForce(force);
}