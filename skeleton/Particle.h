#pragma once
#include "RenderUtils.hpp"
#include <vector>
//#include "core.hpp"
#include <PxPhysicsAPI.h>
class Particle
{
	public: 
		Particle(Vector3 Pos, Vector3 Vel);
		~Particle(); // deregistrar el objeto 
		//RenderItem de la escena en el destructor de la partícula
		void integrate(double t);
private:
	Vector3 vel;
	physx::PxTransform pose; //no hace falta tocar el quaternion no?
	RenderItem *renderItem;
	physx::PxShape* shape;
	Vector4 color;
};

