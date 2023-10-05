#pragma once
#include "RenderUtils.hpp"
#include <vector>
//#include "core.hpp"
#include <PxPhysicsAPI.h>
class Particle
{
	public: 
		Particle(Vector3 Pos, Vector3 Vel, Vector3 Ac, float Mass=0,float Dam = 0.998f);
		Particle(Vector3 Pos=Vector3{0,0,0});
		virtual ~Particle(); // deregistrar el objeto RenderItem 
		virtual void integrate(double t);
	protected:
		RenderItem *renderItem;
		physx::PxShape* shape;
		Vector4 color;
		physx::PxTransform pose; 
		Vector3 vel;
		float damping;
		Vector3 ac;
		float mass;
};

