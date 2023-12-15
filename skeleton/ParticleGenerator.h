#pragma once
#include "Object.h"
#include <list>
class ParticleGenerator
{
	protected:
		std::string _name;
		Vector3 _mean_pos, _mean_vel; //get these from model particle
		double _generator_probability; //constate, porcentaje de prob de que en que cada paso se genere una nueva particula
		int _num_particles; //max particulas que puede generar
		Object* _model; //tipo de particula que se genera
		int _maxTotalParticles;
		int _totalGeneratedParticles;

	public:
		ParticleGenerator() {};
		ParticleGenerator(std::string name, Object* model, double _genprob, int maxpart, int _maxParticles = 0) : _name(name), _model(model), _generator_probability(_genprob), _num_particles(maxpart), _maxTotalParticles(_maxParticles) { _totalGeneratedParticles = 0; };
		virtual ~ParticleGenerator() {};
		virtual void setParticle(Object* model) { _model = model; }; //solo te interesa si quieres cambiar el modelo por lo que sea---> hacer delete de la particula previa
		virtual std::list<Object*>generateParticles() = 0;

};

