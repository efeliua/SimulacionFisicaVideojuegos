#include "ParticleSystem.h"
#include "Constants.h"
#include "UniformParticleGenerator.h"
#include "ParticleGenerator.h"
#include "FireworkGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "Whirlwind.h"
#include "Explosion.h"

//#define TORBELLINO
//#define WIND
//#define GRAVITY
#define PGENERATORS
#define TESTPARTICLE
#define EXPLOSION

ParticleSystem::ParticleSystem()
{
	//modelos ejemplo para los generadores
	Particle *p = new Particle(Vector4(0,200,0,0), 0.2,Vector3(20,20,0),Vector3(0,100,0), Vector3(0,0,0),60, true);
	Particle* p2 = new Particle(Vector4(020, 040, 350, 708), 0.5, Vector3(-50, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0),60, true);

	//particula de prueba
	#ifdef TESTPARTICLE
	Particle* p3 = new Particle(Vector4(020, 040, 350, 708),2, Vector3(-50, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, false, false, 10); //para los gens
	particles.push_back(p3);
	#endif
	
	//generadores
	#ifdef PGENERATORS
		particles_generators.push_back(new GaussianParticleGenerator("fuente", p, 50, 4, Vector3(0.3,0.3,0.3), Vector3(1,0.5,0.5), 0.3)); 
		particles_generators.push_back(new UniformParticleGenerator("uniforme", p2, 50, 3, Vector3(40, 10, 10), Vector3(5, 5, 5)));
		fireGen = new FireworkGenerator();
	#endif

	//reg fuerzas
	pfRegistry = new ParticleForceRegistry();

	#ifdef GRAVITY
		GravityForceGenerator *g=new GravityForceGenerator(Vector3(0, -9.8, 0));
		pfRegistry->addRegistry(g, p3);
		force_generators.push_back(g);
	#endif
	#ifdef WIND
		ParticleDragGenerator* dr = new ParticleDragGenerator(0.5, 0, Vector3(0,0,0), Vector3(350,350,350), Vector3(20,0,0));
		pfRegistry->addRegistry(dr, p3);
		force_generators.push_back(dr);
	#endif
	#ifdef TORBELLINO
	Whirlwind* w = new Whirlwind(1,0,Vector3(20, 20, 0), Vector3(350, 500, 350), Vector3(0,0,0), 0.5);
	pfRegistry->addRegistry(dr, p3);
	force_generators.push_back(w);
	#endif

	#ifdef EXPLOSION
	Particle* p4 = new Particle(Vector4(020, 040, 350, 708), 2, Vector3(-25, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, false, 10); //para los gens
	Particle* p5 = new Particle(Vector4(020, 040, 350, 708), 2, Vector3(25, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, false, 1000); //para los gens
	Particle* p6 = new Particle(Vector4(020, 040, 350, 708), 2, Vector3(0, 25, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, false, 1); //para los gens
	Particle* p7 = new Particle(Vector4(020, 040, 350, 708), 2, Vector3(0, -25, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, false, 100); //para los gens
	particles.push_back(p7);
	particles.push_back(p4);
	particles.push_back(p5);
	particles.push_back(p6);
	#endif 
}

ParticleSystem::~ParticleSystem()
{
	for (auto it = particles.begin(); it != particles.end();)
	{
		delete(*it);
	}
	for (auto it = particles_generators.begin(); it != particles_generators.end();)
	{
		delete(*it);
	}
	for (auto it = force_generators.begin(); it != force_generators.end();)
	{
		delete(*it);
	}
	delete(fireGen); delete(pfRegistry);

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
			particles.remove(p); pfRegistry->deleteParticleRegistry(p); delete(p);
		}
	}
	for (ParticleGenerator* g : particles_generators)
	{
		//integra las nuevas particulas a la lista 
		std::list<Particle*> ps=g->generateParticles();
		addForceGenerators(ps);
		particles.splice(particles.end(), ps);
	}
	
	for (auto it = force_generators.begin(); it != force_generators.end();)
	{
		if (!(*it)->updateTime(t))
		{
			pfRegistry->deleteForceRegistry(*it); ForceGenerator* aux = (*it);
			it = force_generators.erase(it); delete(aux);
		}
		else
		{	
			++it;
		}
	}
	
	pfRegistry->updateForces(t);
}

void ParticleSystem::shoot()
{
	std::list<Particle*> ps =fireGen->generateParticles();
	particles.splice(particles.end(), ps);
}
void ParticleSystem::addForceGenerators(std::list <Particle*> p )
{
	for (auto it = p.begin(); it != p.end();)
	{
		for (auto ot = force_generators.begin(); ot != force_generators.end();)
		{
			pfRegistry->addRegistry(*ot, *it); ++ot;
		}
		++it; 
	}
}
void ParticleSystem::explode()
{
	Explosion* e = new Explosion(2, Vector3(0, 0, 0), 10000, 10000, 1);
	force_generators.push_back(e);
	addSingleForceGeneratorToAll(e);
}
void ParticleSystem::addSingleForceGeneratorToAll(ForceGenerator* f)
{
	for (auto it = particles.begin(); it != particles.end();++it)
	{
		pfRegistry->addRegistry(f, *it);
	}
}

