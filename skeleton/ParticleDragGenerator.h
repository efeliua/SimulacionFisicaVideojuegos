#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class ParticleDragGenerator:public ForceGenerator
{
	public: 
		ParticleDragGenerator() {};
		ParticleDragGenerator( const float k1, const float k2, Vector3 og, Vector3 area, Vector3 wvel,double t= -1e10) : ForceGenerator(t),_k1(k1), _k2(k2), origin(og), space(area), windvel(wvel) { setName("dragFG"); };
		
		virtual void updateForce(Particle* particle, double t);

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
	Vector3 windvel;
};

