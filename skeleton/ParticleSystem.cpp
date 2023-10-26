#include "ParticleSystem.h"
#include "Constants.h"
#include "UniformParticleGenerator.h"
#include "ParticleGenerator.h"
#include "FireworkGenerator.h"
ParticleSystem::ParticleSystem()
{
	//modelos ejemplo para los generadores
	Particle *p = new Particle(Vector4(0,200,0,0), 0.2,Vector3(20,20,0),Vector3(0,30,0), Vector3(0,0,0),6, true);
	Particle* p2 = new Particle(Vector4(020, 040, 350, 708), 0.5, Vector3(-50, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0),6, true);
	
	//generadores
	particles_generators.push_back(new GaussianParticleGenerator("fuente", p, 50, 4, Vector3(0.3,0.3,0.3), Vector3(1,0.5,0.5), 0.3)); 
	particles_generators.push_back(new UniformParticleGenerator("uniforme", p2, 50, 3, Vector3(40, 10, 10), Vector3(5, 5, 5)));

	fireGen = new FireworkGenerator();
}

void ParticleSystem::update(double t)
{
	//time update
	//for every particle lifetime, inside of bounds -> delete particles
	for (auto it = particles.begin(); it != particles.end();)
	{
		Particle* p = static_cast<Particle*>(*it); ++it;
		//comprueba que esté viva (dentro de límites y tiempo de vida)
		if (p->timeLeft()&& p->insideBounds())
		{
			p->integrate(t);
		}
		else { 
			std::list <Particle*> newP=p->onDeath(); //si es firework generará nuevas partículas a añadir
			if (newP.size() != 0) { particles.splice(particles.end(), newP); }
			particles.remove(p); delete(p);
		}
	}
	for (ParticleGenerator* g : particles_generators)
	{
		//integra las nuevas particulas a la lista 
		std::list<Particle*> ps=g->generateParticles();
		particles.splice(particles.end(), ps);
	}
}

void ParticleSystem::shoot()
{
	std::list<Particle*> ps =fireGen->generateParticles();
	particles.splice(particles.end(), ps);
}
