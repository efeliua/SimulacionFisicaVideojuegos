#include "GaussianParticleGenerator.h"
#include "Firework.h"
GaussianParticleGenerator::GaussianParticleGenerator(std::string name, Object* model, double _genprob, int maxpart, Vector3 _devpos, Vector3 _devvel, double _devt, int maxTotal) : ParticleGenerator(name, model, _genprob, maxpart, maxTotal),
std_dev_pos(_devpos), std_dev_vel(_devvel), std_dev_t(_devt) {
	initialiseDs();
}
GaussianParticleGenerator::~GaussianParticleGenerator()
{
	delete(posdx); delete(posdy); delete(posdz); delete(veldx); delete(veldy); delete(veldz);
}
;
std::list<Object*> GaussianParticleGenerator::generateParticles()
{
	//coge particula modelo
	//y sus atributos
	//los altera segun la funcion gaussiana (media, desv)
	std::list<Object*> ps;
	int n=0;  //num d particulas a generar 
	for (int i = 0; i < _num_particles; i++) { if ((rand() % 100) < _generator_probability) n++; } 
	if (_maxTotalParticles != 0 && _totalGeneratedParticles + n > _maxTotalParticles) { n = _maxTotalParticles - _totalGeneratedParticles; };
	for (int i = 0; i < n; i++)
	{
		Vector3 newpos = Vector3((*posdx)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())), 
			(*posdy)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())),
			(*posdz)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())));        
			
		Vector3 newvel = Vector3((*veldx)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())),
			(*veldy)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())),
			(*veldz)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())));
		
		float newTime = (*td)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
		//ponemos las vel, pos modificadas segun la distr
		Object* newP = _model->clone(); newP->setPos(newpos); newP->setVel(newvel); newP->setTimeLife(newTime);
		ps.push_back(newP);
	}
	_totalGeneratedParticles += n;
	return ps;
}

void GaussianParticleGenerator::initialiseDs()
{
	_mean_pos = _model->getPos();
	_mean_vel = _model->getVel();

	posdx = new  std::normal_distribution<float>(_mean_pos.x, std_dev_pos.x); 
	posdy =new  std::normal_distribution<float>(_mean_pos.y, std_dev_pos.y);
	posdz = new std::normal_distribution<float>(_mean_pos.z, std_dev_pos.z);

	veldx = new std::normal_distribution<float>(_mean_vel.x, std_dev_vel.x);
	veldy =new  std::normal_distribution<float>(_mean_vel.y, std_dev_vel.y);
	veldz = new std::normal_distribution<float>(_mean_vel.z, std_dev_vel.z);

	td = new std::normal_distribution<float>(_model->getTimeLife(), std_dev_t);

}
