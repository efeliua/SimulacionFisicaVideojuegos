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
	GaussianParticleGenerator(std::string name, Particle* model, double _genprob, int maxpart, Vector3 _devpos, Vector3 _devvel, double _devt);
	virtual std::list<Particle*> generateParticles();
	std::normal_distribution<double> d{0,1}; //-.-   {media(tiempo, vel, pos), dev} punto donde se generan el 75% de las particulas 
	/*std::normal_distribution<float> posdx{_mean_pos.x,std_dev_pos.x};
	std::normal_distribution<float> posdy{ _mean_pos.y,std_dev_pos.y};
	std::normal_distribution<float> posdz{ _mean_pos.z,std_dev_pos.z };

	std::normal_distribution<float> veldx{ _mean_vel.x,std_dev_vel.x }; 
	std::normal_distribution<float> veldy{ _mean_vel.y,std_dev_vel.y };
	std::normal_distribution<float> veldz{ _mean_vel.z,std_dev_vel.z };*/
	std::normal_distribution<float>* posdx=nullptr;
	std::normal_distribution<float>* posdy=nullptr;
	std::normal_distribution<float>* posdz=nullptr;

	std::normal_distribution<float>* veldx=nullptr;
	std::normal_distribution<float>* veldy=nullptr;
	std::normal_distribution<float>* veldz=nullptr;

	void initialiseDs();
	

};

