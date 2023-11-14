#include "ParticleSystem.h"
#include "Constants.h"
#include "UniformParticleGenerator.h"
#include "ParticleGenerator.h"
#include "FireworkGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
//entonces tienes unos generadores de fuerzas en algun lau para reusar? en punteros o algo?

ParticleSystem::ParticleSystem()
{
	//modelos ejemplo para los generadores
	Particle *p = new Particle(Vector4(0,200,0,0), 0.2,Vector3(20,20,0),Vector3(0,30,0), Vector3(0,0,0),6, true);
	Particle* p2 = new Particle(Vector4(020, 040, 350, 708), 0.5, Vector3(-50, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0),6, true);
	Particle* p3 = new Particle(Vector4(020, 040, 350, 708), 5, Vector3(-50, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, false, 10); //para los gens

	
	//generadores
	//particles_generators.push_back(new GaussianParticleGenerator("fuente", p, 50, 4, Vector3(0.3,0.3,0.3), Vector3(1,0.5,0.5), 0.3)); 
	//particles_generators.push_back(new UniformParticleGenerator("uniforme", p2, 50, 3, Vector3(40, 10, 10), Vector3(5, 5, 5)));

	//uwu
	//fireGen = new FireworkGenerator();

	//reg fuerzas
	pfRegistry = new ParticleForceRegistry();
	//GravityForceGenerator *g=new GravityForceGenerator(Vector3(0, -9.8, 0));
	ParticleDragGenerator* dr = new ParticleDragGenerator(0.5, 0, Vector3(0,0,0), Vector3(50,50,50));
	//pfRegistry->addRegistry(g, p3);
	pfRegistry->addRegistry(dr, p3);
	particles.push_back(p3);
	
}

void ParticleSystem::update(double t)
{
	//forces update
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
	pfRegistry->updateForces(t);
}

void ParticleSystem::shoot()
{
	std::list<Particle*> ps =fireGen->generateParticles();
	particles.splice(particles.end(), ps);
}
