#include "Firework.h"
#include "GaussianParticleGenerator.h"
#include "FireworkGenerator.h"
std::list <Particle*> Firework::onDeath()
{
	std::list<Particle*> newP{};
	if (gen < constants::maxGen) 
	{
		int maxp = 0;
		switch (gen)
		{
			case 0:maxp = 2; break;
			case 1:maxp = 3; break;
			case 2:maxp = 4; break;
			case 3:maxp = 5; break;
		}
		FireworkGenerator* f = static_cast<FireworkGenerator*> (g);
		f->getModel(gen + 1)->setPos(pose.p);
		GaussianParticleGenerator* p = new GaussianParticleGenerator("temp", f->getModel(gen + 1),0,maxp, Vector3(0.3, 0.3, 0.3), Vector3(0.7, 0.7, 0.7), 10);
		newP=p->generateParticles();
		delete(p);
	}
		return newP;
}
