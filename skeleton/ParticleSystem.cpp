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
#include "RigidBody.h"

//bolos
#include "Bolo.h"
#include <iostream>
#define TORBELLINO
#define WIND
#define GRAVITY
#define PGENERATORS
#define TESTPARTICLE
#define TESTPARTICLESTATIC

ParticleSystem::ParticleSystem(physx::PxScene* scene, physx::PxPhysics* p)
{
	std::cout << "\nBOLOS :D" << std::endl;
	//seeControls();
	//reg fuerzas
	pfRegistry = new ParticleForceRegistry();
	//escena de physx
	gScene = scene;
	gPhysics = p;
	//generadores de partículas 
		//generateGS();
	//muestra de partículas con muelles/flotación 
		//generatespringDemo();
	//partículas ejemplo con velocidad inicial
		//generateTestDynamicParticles();
	//partículas ejemplo sin velocidad inicial, masas diferentes (ejemplo de explosión)
		//generateTestStaticParticles();
	//escena de solido rigido-> generadores de sólido rígido
		//generateSolidScene();
	//fuerzas que actuarán sobre la escena
		generateFG();
	//Bolos :D
	createGameScene();

	//RigidBody* r1 = new RigidBody(gScene, gPhysics, Vector4(0, 200, 0, 0), 4, physx::PxTransform(Vector3(0, 10, 0)), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, 0.15, BOX);
	
	
}

ParticleSystem::~ParticleSystem()
{
	for (auto it = particles.begin(); it != particles.end();)
	{
		delete(*it);
		it = particles.erase(it);
	}
	for (auto it = modelParticles.begin(); it != modelParticles.end(); )
	{
		delete(*it);
		it = modelParticles.erase(it);
	}
	for (auto it = particles_generators.begin(); it != particles_generators.end();)
	{
		delete(*it);
		it = particles_generators.erase(it);
	}
	for (auto it = force_generators.begin(); it != force_generators.end();)
	{
		delete(*it);
		it = force_generators.erase(it);
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
		Object* p = static_cast<Object*>(*it); ++it;
		//comprueba que esté viva (dentro de límites y tiempo de vida)
		if (p->timeLeft()&& p->insideBounds())
		{
			p->integrate(t);
		}
		else { 
			std::list <Object*> newP=p->onDeath(); //si es firework generará nuevas partículas a añadir
			if (newP.size() != 0) { addForceGenerators(newP);  particles.splice(particles.end(), newP); }
			particles.remove(p); pfRegistry->deleteParticleRegistry(p); delete(p); //borra la particula del mapa de fuerzas
		}
	}
	for (ParticleGenerator* g : particles_generators)
	{
		//integra las nuevas particulas a la lista, les añade fuerzas presentes en el sistema
		std::list<Object*> ps=g->generateParticles();
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
void ParticleSystem::addMass() //para escena flotación 
{
	if (changeMassP != nullptr)
	{
		changeMassP->addMass(100);
		std::cout << "The pink box new mass is " << changeMassP->getMass() << std::endl;
	}
}
void ParticleSystem::addSingleForceGeneratorToSome(ForceGenerator* f, std::list<Object*> p)
{
	for (auto it = p.begin(); it != p.end(); ++it)
	{
		pfRegistry->addRegistry(f, *it);
	}
}
void ParticleSystem::shoot() //(fireworks)
{
	std::list<Object*> ps =fireGen->generateParticles();
	particles.splice(particles.end(), ps);
}
void ParticleSystem::shoot(int n)
{
	std::list<Object*> ps = fireGen2->generateParticles();
	particles.splice(particles.end(), ps);
	ps = fireGen2->generateParticles();
	particles.splice(particles.end(), ps);
}
void ParticleSystem::generateFG() //de tiempo infinito, aplicadas a todas las particulas que vayan a existir
{
	//fuerzas
	#ifdef GRAVITY
		GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, -9.8, 0));
		force_generators.push_back(g);
		addSingleForceGeneratorToAll(g);
		g->activate(); ////esto por ahora, dejarlo bien -----------------------------------------
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

	
		fireGen = new FireworkGenerator({ 0,-10,0 }); //único generador de fireworks por sistema
		fireGen2= new FireworkGenerator({-50,-5,-20}); //único generador de fireworks por sistema
		fireGen3 = new FireworkGenerator({ {50,-5,-20} }); //único generador de fireworks por sistema
}
void ParticleSystem::generateGS()
{
	//modelos ejemplo para los generadores (el último valor de estos constructor es la masa)
	Particle* p = new Particle(Vector4(0, 200, 0, 0), 0.2, Vector3(20, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, true, 1);
	Particle* p2 = new Particle(Vector4(020, 040, 350, 708), 0.5, Vector3(-50, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, true, 1);
	modelParticles.push_back(p);
	modelParticles.push_back(p2);
	//generadores de partículas
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
void ParticleSystem::addForceGenerators(std::list <Object*> p )
{
	for (auto it = p.begin(); it != p.end();)
	{
		for (auto ot = force_generators.begin(); ot != force_generators.end();)
		{
			std::string name = (*ot)->getName();
			if ( name!= "springFG"&&name!="buoyancySFG") //que la fuerza de muelle no afecte a más que los establecidos
			{
				pfRegistry->addRegistry(*ot, *it); 
			} ++ot;
		}
		++it; 
	}
}
void ParticleSystem::explode(Vector3 pos) //new explosion forcegenerator
{
	Explosion* e = new Explosion(2, pos, 10000, 10000, 1);
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
	std::cout << "\nCONTROLS" << std::endl;
	std::cout << "\nPress WASD to move the camera" << std::endl;
	std::cout << "To Activate/Deactivate Forces Press..." << std::endl;
	std::cout << "G: gravity force" << std::endl;
	std::cout << "V: drag force (wind)" << std::endl;
	std::cout << "H: whirlwind force" << std::endl;
	std::cout << "E: explosion force" << std::endl;
	std::cout << "B: brief drag force (wind, 6 sec)" << std::endl;
	std::cout << "Press M to add mass to the floating pink box (spring scene)" << std::endl;
	std::cout << "Press K to increase the elastic constant of every spring force (spring scene)" << std::endl;

	std::cout << "\nPress i to see controls again" << std::endl;

	std::cout<<std::endl;
}
void ParticleSystem::explode(Vector3 pos, std::list<Object*> p)
{
	Explosion* e = new Explosion(1, pos, 30, 50000, 1);
	force_generators.push_back(e);
	addSingleForceGeneratorToSome(e, p);
}
void ParticleSystem::addMuelle(Object* a, Object* b)
{
	ElasticSpringFG* f4 = new ElasticSpringFG(200, 5, 10, b);
	pfRegistry->addRegistry(f4, a);
	ElasticSpringFG* f5 = new ElasticSpringFG(200, 5, 10, a);
	pfRegistry->addRegistry(f5, b);
	force_generators.push_back(f4);
	force_generators.push_back(f5);
	std::pair<Object*, Object*> obs = { a, b };
	FRPair aP = { a, f4 };
	FRPair bP = { b, f5 };
	std::pair<FRPair, FRPair> frpairs = { aP, bP };
	MuellePair mp = { obs, frpairs };
	connected.push_back(mp);
}
void ParticleSystem::deleteMuelle(Object* a)
{
	for (auto p : connected)
	{
		if (a == p.pair.first)
		{
			//delete spring force (b) 
			pfRegistry->deletePair(p.fgpairs.second.first, p.fgpairs.second.second);
			break;
		}
		else if (a == p.pair.second)
		{
			//delete spring force (a)
			pfRegistry->deletePair(p.fgpairs.first.first, p.fgpairs.first.second);
			break;
		}
	}
}
void ParticleSystem::createBriefWind()
{
	ParticleDragGenerator* dr = new ParticleDragGenerator(0.5, 0, Vector3(0, 0, 0), Vector3(350, 350, 350), Vector3(20, 0, 0), 6);
	dr->activate();
	force_generators.push_back(dr);
	addSingleForceGeneratorToAll(dr);
}

void ParticleSystem::createBriefWind(Vector3 pos, std::list<Object*> p, Vector3 dir)
{
	ParticleDragGenerator* dr = new ParticleDragGenerator(0.9, 0, pos, Vector3(200, 40, 350),dir, 1);
	dr->activate();
	force_generators.push_back(dr);
	addSingleForceGeneratorToSome(dr, p);
}

void ParticleSystem::createInfoPanel()
{
	infoPanel = new RigidBody(gScene, gPhysics, Vector4(0, 0,0, 1), 0, physx::PxTransform(Vector3(0, 0, -10)), 0, false, BOX, Vector3(175,500, 25));
}

void ParticleSystem::createFloor()
{
	RigidBody* suelo = new RigidBody(gScene, gPhysics, Vector4(0.8, 0.8, 0.8, 1), 0, physx::PxTransform(Vector3(0, 0, 0)),  0, false,  BOX, Vector3(100, 0.1, 100));
	modelParticles.push_back(suelo);
}
void ParticleSystem::createGameScene() 
{
	RigidBody* suelo = new RigidBody(gScene, gPhysics, Vector4(0.2,0.1,0.2,1), 0, physx::PxTransform(Vector3(0, 0, -25)), 0, false, BOX, Vector3(50, 0.1, 200));
	modelParticles.push_back(suelo);
	
	RigidBody* paredIz = new RigidBody(gScene, gPhysics, Vector4(0.8, 3, 0.2, 1), 0, physx::PxTransform(Vector3(-100, 0, -450)), 0, false, BOX, Vector3(25, 300, 25));
	RigidBody* paredDch = new RigidBody(gScene, gPhysics, Vector4(0.8, 3, 0.2, 1), 0, physx::PxTransform(Vector3(100, 0, -450)), 0, false, BOX, Vector3(25, 300, 25));
	modelParticles.push_back(paredIz);
	modelParticles.push_back(paredDch);

	RigidBody* top = new RigidBody(gScene, gPhysics, Vector4(0.8, 0.8, 0.8, 1), 0, physx::PxTransform(Vector3(0, 75, -450)), 0, false, BOX, Vector3(175, 150, 25));
	

	//modelos ejemplo para los generadores (el último valor de estos constructor es la masa)
	Particle* p = new Particle(Vector4(1, 1,0,0), 0.3, Vector3(-90, 150, -450), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, true, 0.8, BOX);
	Particle* p2 = new Particle(Vector4(1, 1, 0, 0), 0.3, Vector3(90, 150, -450), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, true, 0.8, BOX);
	Particle* p3 = new Particle(Vector4(0.4, 0.8, 3, 1), 0.5, Vector3(-120, 150, -450), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, true, 1);
	Particle* p4 = new Particle(Vector4(0.4, 0.8, 3, 1), 0.5, Vector3(120, 150, -450), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, true, 1);
	modelParticles.push_back(p);
	modelParticles.push_back(p2);
	modelParticles.push_back(p3);
	modelParticles.push_back(p4);
	//generadores de partículas (decoracion)
	particles_generators.push_back(new GaussianParticleGenerator("fuente", p, 50, 4, Vector3(0.3, 0.3, 0.3), Vector3(1, 0.5, 0.5), 0.3));
	particles_generators.push_back(new GaussianParticleGenerator("fuente", p2, 50, 4, Vector3(0.3, 0.3, 0.3), Vector3(1, 0.5, 0.5), 0.3));
	particles_generators.push_back(new UniformParticleGenerator("uniforme", p3, 50, 3, Vector3(40, 10, 10), Vector3(5, 5, 5)));
	particles_generators.push_back(new UniformParticleGenerator("uniforme", p4, 50, 3, Vector3(40, 10, 10), Vector3(5, 5, 5)));

}

void ParticleSystem::generatespringDemo()
{
	//tienen una vida limitada de 60
	//Muelle estándar de dos partículas
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
	
	//Muelle elástico 
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

	//Muelle fijado en un punto
	Particle* p3 = new Particle(Vector4(0, 200, 0, 0), 0.2, Vector3(50, 10, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 60, false, true, 1);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(100,1, 10, { 50.0,0.0,0.0 });
	pfRegistry->addRegistry(f3, p3);
	force_generators.push_back(f3);
	particles.push_back(p3);

	
	//Flotación (tres partículas con diferentes masas)
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


	//Gravedad aplicada a quien convenga (solo a los flotadores y la partícula de muelle con extremo en punto fijado)
	GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, -9.8, 0));
	force_generators.push_back(g);
	pfRegistry->addRegistry(g, p3);
	pfRegistry->addRegistry(g, p6);
	pfRegistry->addRegistry(g, changeMassP);
	pfRegistry->addRegistry(g, p8);


}
void ParticleSystem::generateSolidScene()
{
	//Suelo
	createFloor();

	//Modelos ejemplo para los generadores 
	RigidBody* r1 = new RigidBody(gScene, gPhysics, Vector4(0, 200, 0, 0), 0.5, physx::PxTransform(Vector3(20, 10, 0)), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, 0.15, BOX);
	RigidBody* r2 = new RigidBody(gScene, gPhysics ,Vector4(0, 100, 50, 0), 1, physx::PxTransform(Vector3(-20, 10, 0)), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, 1.5, BOX);
	modelParticles.push_back(r1);
	modelParticles.push_back(r2);
	//Generadores (utimo valor es el numero de particulas que van a generar en su vida)
	particles_generators.push_back(new GaussianParticleGenerator("fuenteR", r1, 50, 2, Vector3(0.3, 0.3, 0.3), Vector3(1, 0.5, 0.5), 0.3,200));
	particles_generators.push_back(new UniformParticleGenerator("uniformeR", r2, 50, 2, Vector3(40, 10, 10), Vector3(5, 5, 5),250));

	/*A los objetos de tipo sólido rígido les afectan todas las fuerzas a medida que se activan mediante teclado. 
	Pulsar i en ejecución para ver en consola los controles. */
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

