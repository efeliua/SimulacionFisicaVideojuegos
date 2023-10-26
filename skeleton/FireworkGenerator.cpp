#include "FireworkGenerator.h"

FireworkGenerator::FireworkGenerator(Vector3 pos)
{
	firework_pool.push_back(new Firework(Vector4(0, 300, 0, 0),0.7,pos, Vector3(0,30,0), Vector3(0, 0, 0), 2, true, 0, this));
	firework_pool.push_back(new Firework(Vector4(0, 190, 0, 0),0.6,pos, Vector3(0, 40, 0), Vector3(0, 0, 0), 0.6,true, 1, this));
	firework_pool.push_back(new Firework(Vector4(120, 0, 0, 0),0.5,pos, Vector3(0,30,0), Vector3(0, 0, 0),0.3, true, 2, this));
	firework_pool.push_back(new Firework(Vector4(0, 0, 060, 0), 0.25,pos, Vector3(0, 20, 0), Vector3(0, 0, 0),0.15, true, 3, this));
	firework_pool.push_back(new Firework(Vector4(120, 0, 050,0),0.1,pos, Vector3(0, 10, 0), Vector3(0, 0, 0), 0.075,true, 4, this));
}

std::list<Particle*> FireworkGenerator::generateParticles()
{
	std::list<Particle*> ps;
	ps.push_back(firework_pool[0]->clone()); //you gotta clone this probs pues si 
	return ps;
}
