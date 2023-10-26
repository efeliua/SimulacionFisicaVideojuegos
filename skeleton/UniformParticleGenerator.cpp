#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(std::string name,Particle* model, double _genprob, int maxpart, Vector3 _posw, Vector3 _velw) : ParticleGenerator(name, model, _genprob, maxpart),
_vel_width(_velw), _pos_width(_posw)
{
	initialiseDs();
}
UniformParticleGenerator::~UniformParticleGenerator()
{
	delete(dposx); delete(dposy); delete(dposz); delete(dvelx); delete(dvely); delete(dvelz);
}
std::list<Particle*> UniformParticleGenerator::generateParticles()
{
	std::list<Particle*> ps;
	int n = 0;  //num d particulas a generar 
	for (int i = 0; i < _num_particles; i++) { if ((rand() % 100) < _generator_probability) n++; }
	for (int i = 0; i < n; i++)
	{
		float posx = (*dposx)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
		float posy = (*dposy)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
		float posz = (*dposz)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
		float velx = (*dvelx)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
		float vely = (*dvely)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
		float velz = (*dvelz)(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
		Particle* newP = _model->clone(); newP->setPos(Vector3(posx, posy, posz)); newP->setVel(Vector3(velx, vely, velz));
		ps.push_back(newP);
	}

	return ps;
}
void UniformParticleGenerator::initialiseDs()
{
	//inicializacion de distribuciones (valor minimo, valor máximo)
	dposx = new std::uniform_real_distribution<double>(_model->getPos().x - (_pos_width.x / 2), _model->getPos().x + (_pos_width.x / 2));
	dposy = new std::uniform_real_distribution<double>(_model->getPos().y - (_pos_width.y / 2), _model->getPos().y + (_pos_width.y / 2));
	dposz = new std::uniform_real_distribution<double>(_model->getPos().z - (_pos_width.z / 2), _model->getPos().z + (_pos_width.z / 2));
	dvelx = new std::uniform_real_distribution<double>(_model->getVel().x - (_vel_width.x / 2), _model->getVel().x + (_vel_width.x / 2));
	dvely = new std::uniform_real_distribution<double>(_model->getVel().y - (_vel_width.y / 2), _model->getVel().y + (_vel_width.y / 2));
	dvelz = new std::uniform_real_distribution<double>(_model->getVel().z - (_vel_width.z / 2), _model->getVel().z + (_vel_width.z / 2));

}
;
