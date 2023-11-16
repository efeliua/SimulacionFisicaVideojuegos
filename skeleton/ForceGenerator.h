#pragma once
#include "Particle.h"
class ForceGenerator
{
public:
	ForceGenerator() {};
	ForceGenerator(double dur) : _duration(dur) {};
	virtual void updateForce(Particle* particle, double time=0) = 0;
	std::string _name; //para nada porque luego ya veras que no lo usare
	double _t = 0.0;
	double _duration = -1e10;
	inline bool updateTime(double t) { _t += t; return _t < _duration || _duration < 0.0; };
	//devuelve true si ua era cero o si es positivo
	virtual ~ForceGenerator() {};

	//todo en publico?????????? como asi

};

