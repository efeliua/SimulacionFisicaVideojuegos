#pragma once
#include "Particle.h"
#include "Constants.h"
class FireworkGenerator;
class Firework: public Particle
{
	protected:
		int gen; //generación
	public: 
		Firework(Vector4 color, float size, Vector3 Pos, Vector3 Vel, Vector3 Ac, float timeLife, bool model, int gen, ParticleGenerator* firegen) :Particle(color, size, Pos, Vel, Ac, timeLife, model), gen(gen) { g = firegen; };
		virtual ~Firework() {};
		virtual std::list<Object*> onDeath();
		virtual Particle* clone() override { return new Firework(color, size, pose.p, vel, ac, lifeTime, false, gen, g); }
};

