#include "ParticleSystem.h"
#include "Constants.h"
#include "UniformParticleGenerator.h"
#include "ParticleGenerator.h"
#include "FireworkGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "Whirlwind.h"
#include "Explosion.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "ElasticSpringFG.h"
#include "BuoyancyForceGenerator.h"
#include <iostream>
#define TORBELLINO
#define WIND
//#define GRAVITY
//#define PGENERATORS
//#define TESTPARTICLE
//#define TESTPARTICLESTATIC

ParticleSystem::ParticleSystem()
{
	std::cout << "Press i to see controls" << std::endl;
	//reg fuerzas
	pfRegistry = new ParticleForceRegistry();
	
	generateGS();
	//particulas ya en pantalla
	generatespringDemo();
	//generateTestDynamicParticles();
	//generateTestStaticParticles();
	//fuerzas que actuarán
	generateFG();
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
	pfRegistry->updateForces(t); 
	//for every particle lifetime, inside of bounds -> delete particles
	//time update (forces), force update
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
			if (newP.size() != 0) { addForceGenerators(newP);  particles.splice(particles.end(), newP); }
			particles.remove(p); pfRegistry->deleteParticleRegistry(p); delete(p); //borra la particula del mapa de fuerzas
		}
	}
	for (ParticleGenerator* g : particles_generators)
	{
		//integra las nuevas particulas a la lista, les añade fuerzas presentes en el sistema
		std::list<Particle*> ps=g->generateParticles();
		addForceGenerators(ps);
		particles.splice(particles.end(), ps);
	}
	
	for (auto it = force_generators.begin(); it != force_generators.end();)
	{
		if (!(*it)->updateTime(t)) //si se le acaba el tiempo a alguno de los generadores de fuerzas, se borra y sus parejas con partículas del registro
		{
			pfRegistry->deleteForceRegistry(*it); ForceGenerator* aux = (*it);
			it = force_generators.erase(it); delete(aux);
		}
		else
		{	
			++it;
		}
	}
}
void ParticleSystem::addMass()
{
	changeMassP->addMass(100);
	std::cout << "The pink box new mass is " << changeMassP->getMass() << std::endl;
}
void ParticleSystem::shoot() //(fireworks)
{
	std::list<Particle*> ps =fireGen->generateParticles();
	particles.splice(particles.end(), ps);
}
void ParticleSystem::generateFG() //de tiempo infinito, aplicadas a todas las particulas que vayan a existir
{
	//fuerzas
	#ifdef GRAVITY
		GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, -9.8, 0));
		force_generators.push_back(g);
		addSingleForceGeneratorToAll(g);
	#endif
	#ifdef WIND
		ParticleDragGenerator* dr = new ParticleDragGenerator(0.5, 0, Vector3(0, 0, 0), Vector3(350, 350, 350), Vector3(20, 0, 0));
		force_generators.push_back(dr);
		addSingleForceGeneratorToAll(dr);
	#endif
	#ifdef TORBELLINO
		Whirlwind* w = new Whirlwind(1, 0, Vector3(20, 20, 0), Vector3(350, 500, 350), Vector3(0, 0, 0), 0.5);
		force_generators.push_back(w);
		addSingleForceGeneratorToAll(w);
	#endif

	fireGen = new FireworkGenerator(); //único generador de fireworks por sistema
}
void ParticleSystem::generateGS()
{
	//modelos ejemplo para los generadores (el último valor de estos constructor es la masa)
	Particle* p = new Particle(Vector4(0, 200, 0, 0), 0.2, Vector3(20, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, true, 1);
	Particle* p2 = new Particle(Vector4(020, 040, 350, 708), 0.5, Vector3(-50, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, true, 1);
	//generadores 
#ifdef PGENERATORS
	particles_generators.push_back(new GaussianParticleGenerator("fuente", p, 50, 4, Vector3(0.3, 0.3, 0.3), Vector3(1, 0.5, 0.5), 0.3));
	particles_generators.push_back(new UniformParticleGenerator("uniforme", p2, 50, 3, Vector3(40, 10, 10), Vector3(5, 5, 5)));
#endif
}
void ParticleSystem::generateTestStaticParticles()
{
#ifdef TESTPARTICLESTATIC
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
void ParticleSystem::generateTestDynamicParticles()
{
	//particulas de prueba (dos hacia arriba, distinta masa), (cuatro sin velocidad inicial de distinta masa)
#ifdef TESTPARTICLE
	Particle* p3 = new Particle(Vector4(020, 040, 350, 708), 2, Vector3(-50, 20, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, false, false, 10); //para los gens
	Particle* p8 = new Particle(Vector4(020, 040, 350, 708), 2, Vector3(20, 20, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, false, false, 5); //para los gens
	particles.push_back(p3);
	particles.push_back(p8);
#endif
}
void ParticleSystem::addForceGenerators(std::list <Particle*> p )
{
	for (auto it = p.begin(); it != p.end();)
	{
		for (auto ot = force_generators.begin(); ot != force_generators.end();)
		{
			std::string name = (*ot)->getName();
			if ( name!= "springFG"&&name!="buoyancySFG") //comentar si se quisiera que afectara a todo dios
			{
				pfRegistry->addRegistry(*ot, *it); 
			} ++ot;
		}
		++it; 
	}
}
void ParticleSystem::explode() //new explosion forcegenerator
{
	Explosion* e = new Explosion(2, Vector3(0, 0, 0), 10000, 10000, 1);
	force_generators.push_back(e);
	addSingleForceGeneratorToAll(e);
}
void ParticleSystem::shootProjectile(type ty) //(new projectile)
{
	Projectile* pj = new Projectile(ty);
	particles.push_back(pj);
	for (ForceGenerator* g : force_generators)
	{
		pfRegistry->addRegistry(g, pj);
	}
}
void ParticleSystem::seeControls()
{
	std::cout << "Press WASD to move the camera" << std::endl;
	std::cout << "To Activate/Deactivate Forces Press..." << std::endl;
	std::cout << "G: gravity force" << std::endl;
	std::cout << "V: drag force (wind)" << std::endl;
	std::cout << "H: whirlwind force" << std::endl;
	std::cout << "E: explosion force" << std::endl;
	std::cout << "B: brief drag force (wind, 6 sec)" << std::endl;
	std::cout << "Press M to add mass to the floating pink box" << std::endl;
	std::cout << "Press K to increase the elastic constant of every spring force" << std::endl;

	std::cout<<std::endl;

}
void ParticleSystem::createBriefWind()
{
	ParticleDragGenerator* dr = new ParticleDragGenerator(0.5, 0, Vector3(0, 0, 0), Vector3(350, 350, 350), Vector3(20, 0, 0), 6);
	dr->activate();
	force_generators.push_back(dr);
	addSingleForceGeneratorToAll(dr);
}
void ParticleSystem::generatespringDemo()
{
	//(they have a limited time life of 60s)
	//First one standard spring uniting 2 particles
	Particle* p1 = new Particle(Vector4(0, 200, 0, 0), 1, Vector3(-50, -25, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, true, 1);
	Particle* p2 = new Particle(Vector4(0, 200, 0, 0), 1, Vector3(-30, -25, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, true, 1);
	SpringForceGenerator* f1 = new SpringForceGenerator(20, 1, 10, p2);
	pfRegistry->addRegistry(f1, p1);
	SpringForceGenerator* f2 = new SpringForceGenerator(20, 1, 10, p1);
	pfRegistry->addRegistry(f2, p2);
	force_generators.push_back(f1);
	force_generators.push_back(f2);
	particles.push_back(p1);
	particles.push_back(p2);
	
	//two but theyre elastic
	Particle* p4 = new Particle(Vector4(0, 200, 0, 0), 1, Vector3(-50, 25, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, true, 1);
	Particle* p5 = new Particle(Vector4(0, 200, 0, 0), 1, Vector3(-30, 25, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, true, 1);
	ElasticSpringFG* f4 = new ElasticSpringFG(20, 1, 10, p5);
	pfRegistry->addRegistry(f4, p4);
	ElasticSpringFG* f5 = new ElasticSpringFG(20, 1, 10, p4);
	pfRegistry->addRegistry(f5, p5);
	force_generators.push_back(f4);
	force_generators.push_back(f5);
	particles.push_back(p4);
	particles.push_back(p5);

	//one w a fixed side ---> anchored spring
	Particle* p3 = new Particle(Vector4(0, 200, 0, 0), 0.2, Vector3(50, 10, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, true, 1);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(100,1, 10, { 50.0,0.0,0.0 });
	pfRegistry->addRegistry(f3, p3);
	force_generators.push_back(f3);
	particles.push_back(p3);

	
	//buoyancy
	Particle* p6 = new Particle(Vector4(60, 0, 0, 0), 0, Vector3(0, 10, 2), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, true, 1000,BOX, Vector3(1,5,1), 0.86);
	particles.push_back(p6);
	changeMassP = new Particle(Vector4(60, 0, 60, 0), 0, Vector3(10, 10, 2), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, true, 300, BOX, Vector3(1, 5, 1), 0.86);
	particles.push_back(changeMassP);
	Particle* p8 = new Particle(Vector4(0, 120, 60, 0), 0, Vector3(20, 10, 2), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, true, 2000, BOX, Vector3(1, 5, 1), 0.86);
	particles.push_back(p8);


	BuoyancyForceGenerator* b = new BuoyancyForceGenerator(1000, Vector3(0,0,0));
	force_generators.push_back(b);
	pfRegistry->addRegistry(b, p6);
	pfRegistry->addRegistry(b, changeMassP);
	pfRegistry->addRegistry(b, p8);


	//solo añado gravedad aqui a las que me interesan
	GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, -9.8, 0));
	force_generators.push_back(g);
	pfRegistry->addRegistry(g, p3);
	pfRegistry->addRegistry(g, p6);
	pfRegistry->addRegistry(g, changeMassP);
	pfRegistry->addRegistry(g, p8);


}
void ParticleSystem::addK()
{
	for (auto e : force_generators) //sumamos a todo que sea o herede de spring force gen
	{
		if (e->getName()== "springFG")
		{
			SpringForceGenerator* s=static_cast <SpringForceGenerator*>(e);
			s->addK(10); std::cout << "New value of springforceGenerators: " << s->getK() << std::endl;
		}
	}
}
void ParticleSystem::activateFG(std::string name)
{
	for (auto e : force_generators) //sumamos a todo que sea o herede de spring force gen
	{
		if (e->getName() == name)
		{
			bool aux=e->activate(); //or deactivate
			if(aux) std::cout << name << " activated " << std::endl;
			else std::cout << name << " deactivated " << std::endl;
		}
	}
}
void ParticleSystem::addSingleForceGeneratorToAll(ForceGenerator* f)
{
	for (auto it = particles.begin(); it != particles.end();++it)
	{
		pfRegistry->addRegistry(f, *it);
	}
}

