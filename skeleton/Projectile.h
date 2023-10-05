#pragma once
#include "Particle.h"
enum type { BALA, TANQUE, CANON };
class Projectile:public Particle
{
public:
	Projectile(type Tipo);
private:
	type tipo;
};

