#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class SpringForceGenerator: public ForceGenerator
{
public:
	SpringForceGenerator(double t,double k, double resting_length, Object* other);
	virtual void updateForce(Object* particle, double time);
	inline void setK(double k) { _k = k; }
	inline void addK(double k) { _k += k; }
	inline float getK() { return _k; }
protected:
	double _k; //elastic coeff-> constante elástica del muelle (cuánto se deformará ig)
	double _resting_length; //cuando no está deformado, length original (no llega a stainearse nunca en principio)
	Object* _other;
};

