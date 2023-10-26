#include "FireworkGenerator.h"

FireworkGenerator::FireworkGenerator(std::string name, Particle* model, double _genprob, int maxpart):ParticleGenerator(name, model, _genprob, maxpart)
{
	firework_pool.push_back(new Firework(_model->getPos(), _model->getVel(), Vector3(0, 0, 0), true, 0, this));
	firework_pool.push_back(new Firework(model->getPos(), Vector3(10, 10, 10), Vector3(0, 0, 0), true, 1, this));
	firework_pool.push_back(new Firework(model->getPos(), Vector3(8,8,8), Vector3(0, 0, 0), true, 2, this));
	firework_pool.push_back(new Firework(model->getPos(), Vector3(6, 6, 6), Vector3(0, 0, 0), true, 3, this));
	firework_pool.push_back(new Firework(model->getPos(), Vector3(5, 5, 5), Vector3(0, 0, 0), true, 4, this));
}

std::list<Particle*> FireworkGenerator::generateParticles()
{
	std::list<Particle*> ps;
	ps.push_back(new Firework(_model->getPos(), _model->getVel(), Vector3(0, 0, 0), false, 0, this)); //you gotta clone this probs pues si 
	return ps;
}
