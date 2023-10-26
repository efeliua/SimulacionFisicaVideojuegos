#include "ParticleSystem.h"
#include "Constants.h"
#include "UniformParticleGenerator.h"
#include "ParticleGenerator.h"
#include "FireworkGenerator.h"
ParticleSystem::ParticleSystem()
{
	Particle *p = new Particle(Vector3(0,0,0),Vector3(0,30,0), Vector3(0,0,0), true);
	Particle* p2 = new Particle(Vector3(-50, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), true);

	//particles_generators.push_back(new GaussianParticleGenerator("fuente", p, 50, 4, Vector3(0.3,0.3,0.3), Vector3(0.5,0.5,0.5), 10)); //O.O
	//particles_generators.push_back(new UniformParticleGenerator("aaa", p2, 50, 3, Vector3(40, 10, 10), Vector3(5, 5, 5)));

	fireGen = new FireworkGenerator("no", p, 100,1);
}

void ParticleSystem::update(double t)
{
	//time update
	//for every particle lifetime, inside of bounds -> delete particles
	
	for (auto it = particles.begin(); it != particles.end();)
	{
		Particle* p = static_cast<Particle*>(*it); ++it;
		if (p->timeLeft()&& p->insideBounds())
		{
			p->integrate(t);
		}
		else { 
			std::list <Particle*> newP=p->onDeath();
			if (newP.size() != 0) { particles.splice(particles.end(), newP); }
			particles.remove(p); delete(p);
		}//
		
	}
	for (ParticleGenerator* g : particles_generators)
	{
		//integra las nuevas particulas a la lista 
		std::list<Particle*> ps=g->generateParticles();
		particles.splice(particles.end(), ps);
	}

	//generar nuevas particulas desde 1 o mas generadores
	//add to list 
}

void ParticleSystem::shoot()
{
	std::list<Particle*> ps =fireGen->generateParticles();
	particles.splice(particles.end(), ps);
}
