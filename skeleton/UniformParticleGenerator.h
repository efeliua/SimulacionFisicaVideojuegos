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
	UniformParticleGenerator(std::string name, Object* model, double _genprob, int maxpart, Vector3 _posw, Vector3 _velw);
	~UniformParticleGenerator();
	virtual std::list<Object*> generateParticles();

	//distribuciones uniformes
	std::uniform_real_distribution<double>* dposx;
	std::uniform_real_distribution<double>* dposy;
	std::uniform_real_distribution<double>* dposz;

	std::uniform_real_distribution<double>* dvelx;
	std::uniform_real_distribution<double>* dvely;
	std::uniform_real_distribution<double>* dvelz;
	
	void initialiseDs(); //tambien se podría llamar para redefinir las distribuciones si se cambiara de modelo dentro de un mismo generador desde un setmodel
};

