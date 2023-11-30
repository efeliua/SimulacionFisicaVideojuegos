#pragma once
#include "Particle.h"
#include <string>
class ForceGenerator
{
public:
	ForceGenerator() {};
	ForceGenerator(double dur, bool active=false) : _duration(dur),_active(active)  {};
	inline void setName(std::string n) { _name = n; }
	inline std::string getName() { return _name; }
	virtual void updateForce(Particle* particle, double time=0) = 0;
	std::string _name; 
	double _t = 0.0;
	double _duration = -1e10;
	bool _active=false;
	inline bool updateTime(double t) { _t += t; return _t < _duration || _duration < 0.0; };
	inline bool activate() {
		_active = !_active; return _active;
	}
	//devuelve true si ya era cero o si es positivo
	virtual ~ForceGenerator() {};
};

