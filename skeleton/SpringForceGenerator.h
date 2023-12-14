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
	double _k; //elastic coeff-> constante el�stica del muelle (cu�nto se deformar� ig)
	double _resting_length; //cuando no est� deformado, length original (no llega a stainearse nunca en principio)
	Object* _other;
};

