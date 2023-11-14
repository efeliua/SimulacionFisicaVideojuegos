#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class ParticleDragGenerator:public ForceGenerator
{
	public: 
		ParticleDragGenerator();
		ParticleDragGenerator(const float k1, const float k2);
		ParticleDragGenerator(const float k1, const float k2, Vector3 og, Vector3 area) : _k1(k1), _k2(k2), origin(og), space(area) {};

		virtual void updateForce(Particle* particle, double t);
		inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; };
		inline float getk1() { return _k1; }
		inline float getk2() { return _k2; }
		inline bool isInside(Vector3 pos) {
			return (pos.x < (origin.x + space.x / 2)) && (pos.x > (origin.x - space.x / 2) 
				&& (pos.y < (origin.y + space.y / 2)) && (pos.y > (origin.y - space.y / 2))
				&& (pos.z < (origin.z + space.z / 2))&& (pos.z > (origin.y - space.z / 2)));
		}
protected:
	float _k1; //coef for velocity
	float _k2; //coef for square velocity
	Vector3 origin; //punto central del área de drag
	Vector3 space; //width, height, depth
};

