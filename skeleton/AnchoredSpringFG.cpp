#include "AnchoredSpringFG.h"
#include "Particle.h"

AnchoredSpringFG::AnchoredSpringFG(double t, double k, double resting, const Vector3& anchor_pos):SpringForceGenerator(t, k, resting, nullptr)
{
	(Vector4(0, 200, 0, 0), 0.2, Vector3(20, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 60, true, true, 1);
	_other = new Particle(Vector4{100,200,100,1}, 2, anchor_pos,  Vector3(0,0,0), Vector3(0,0,0), 60, false, false, 1, BOX );
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _other;
}
