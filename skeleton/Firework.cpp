#include "Firework.h"
#include "GaussianParticleGenerator.h"
#include "FireworkGenerator.h"
std::list <Object*> Firework::onDeath()
{
	std::list<Object*> newP{};
	if (gen < constants::maxGen)
	{
		int maxp = 0;
		switch (gen) //dependiendo de la generación generará un max de particulas
		{
		case 0:maxp = 2; break;
		case 1:maxp = 4; break;
		case 2:maxp = 6; break;
		case 3:maxp = 8; break;
		}
		FireworkGenerator* f = static_cast<FireworkGenerator*> (g);
		f->getModel(gen + 1)->setPos(pose.p);
		GaussianParticleGenerator* p = new GaussianParticleGenerator("temp", f->getModel(gen + 1), 100, maxp, Vector3(0.5, 0.5, 0.5), Vector3(7, 7, 7), 0.1);
		newP = p->generateParticles();
		delete(p);
	}
		return newP;
}
