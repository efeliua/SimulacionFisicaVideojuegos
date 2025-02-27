#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <chrono>
class GaussianParticleGenerator:public  ParticleGenerator
{
protected:
	Vector3 std_dev_pos, std_dev_vel; 
	double std_dev_t; //en vez de generarla con un t de vida cte a vcees varia
public:
	GaussianParticleGenerator(std::string name, Object* model, double _genprob, int maxpart, Vector3 _devpos, Vector3 _devvel, double _devt, int maxTotal=0);
	~GaussianParticleGenerator();
	virtual std::list<Object*> generateParticles();

	std::normal_distribution<float>* posdx=nullptr;
	std::normal_distribution<float>* posdy=nullptr;
	std::normal_distribution<float>* posdz=nullptr;

	std::normal_distribution<float>* veldx=nullptr;
	std::normal_distribution<float>* veldy=nullptr;
	std::normal_distribution<float>* veldz=nullptr;

	std::normal_distribution<float>* td = nullptr;


	void initialiseDs();
	

};

