#include "Projectile.h"
#include "RenderUtils.hpp"
#include "Constants.h"

Projectile::Projectile(type Tipo):Particle(), tipo(Tipo)
{
	Vector3 simVel; float realMass; //SI

	//posicion y dirección dependiendo de la cámara
	simVel=GetCamera()->getDir();
	pose.p = GetCamera()->getTransform().p;
	
	//calculos de escala según tipo de bala 
	switch (tipo)
	{
		case BALA: {simVel*=150; vel = { 300,300,0 }; realMass = 0.2; }break; //(pistola)
		case TANQUE: {simVel *=300; vel = { 1800,1800,0 }; realMass = 1200; }break;
		case CANON: {simVel *=100; vel = { 250,250,0 }; realMass = 2.2; } break;
	}
	
	//ac = { 0,-constants::generalGravity, 0 }; //de momento no tendrá aceleracion adicional a la gravedad cte
	mass = realMass * (pow((vel.magnitude() / simVel.magnitude()), 2));
	//ac = ac * (pow((simVel.magnitude() / vel.magnitude()), 2)); 
	vel = simVel; 
}
