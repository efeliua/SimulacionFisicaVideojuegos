#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <chrono>
class UniformParticleGenerator: public ParticleGenerator
{
protected: 
	Vector3 _pos_width;
	Vector3 _vel_width;
public:
	UniformParticleGenerator(std::string name, Particle* model, double _genprob, int maxpart, Vector3 _posw, Vector3 _velw);
	virtual std::list<Particle*> generateParticles();
	std::uniform_real_distribution<double>* dposx;
	std::uniform_real_distribution<double>* dposy;
	std::uniform_real_distribution<double>* dposz;

	std::uniform_real_distribution<double>* dvelx;
	std::uniform_real_distribution<double>* dvely;
	std::uniform_real_distribution<double>* dvelz;
	
	void initialiseDs();

	

};

