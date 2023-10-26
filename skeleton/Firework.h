#pragma once
#include "Particle.h"
#include "Constants.h"
class FireworkGenerator;
class Firework: public Particle
{
	protected:
		 //el generador padre con el pool
		int gen;
	public: 
		Firework(Vector3 Pos, Vector3 Vel, Vector3 Ac, bool model, int gen, ParticleGenerator* firegen) :Particle(Pos, Vel, Ac, model), gen(gen) { g = firegen; };
		virtual std::list<Particle*> onDeath();
		inline int getGnumber() { return gen; }
};

