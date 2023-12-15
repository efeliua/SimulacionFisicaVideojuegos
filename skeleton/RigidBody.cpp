#include "RigidBody.h"

//dynamic
RigidBody::RigidBody(physx::PxScene* scene, physx::PxPhysics* phys, Vector4 Color, float Size, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, float timeLife, bool Model, float Density, itemShape s, Vector3 boxSize, float Dam)
{
	model = Model;
	//render
	color = Color;
	size = Size;
	shapeType = s;

	//phys
	gScene = scene;
	gPhysics = phys;

	//tamaño
	if (size != 0) { recSize = Vector3(size, size, size); }
	else recSize = boxSize;

	//creación sólido rígido (dinámico)
	physx::PxRigidDynamic* new_solid;
	new_solid = gPhysics->createRigidDynamic(Pos);
	new_solid->setLinearVelocity(LinearVel);
	new_solid->setAngularVelocity(AngularVel);
	new_solid->setLinearDamping(Dam);
	physx::PxRigidBodyExt::updateMassAndInertia(*new_solid, Density);
	
	addShape(s, size, boxSize);
	new_solid->attachShape(*shape);
	if (!model) {
		renderItem = new RenderItem(shape, new_solid, color);
	}
	gScene->addActor(*new_solid);
	rigidB = new_solid;
	rigidBstatic = nullptr;

	//tiempo de vida
	remainingTime = lifeTime = timeLife;
}
//static
RigidBody::RigidBody(physx::PxScene* scene, physx::PxPhysics* phys, Vector4 Color, float Size, physx::PxTransform Pos, float timeLife, bool Model, itemShape s, Vector3 boxSize)
{
	model = Model;
	
	//render
	color = Color;
	size = Size;
	shapeType = s;

	//phys
	gScene = scene;
	gPhysics = phys;

	//tamaño
	if (size != 0) { recSize = Vector3(size, size, size); }
	else recSize = boxSize;

	//creación de sólido rígido (estático)
	physx::PxRigidStatic* new_solid;
	new_solid = gPhysics->createRigidStatic(Pos);

	addShape(s, size, boxSize);
	new_solid->attachShape(*shape);

	if (!model) {
		renderItem = new RenderItem(shape, new_solid, color);
	}
	gScene->addActor(*new_solid);
	rigidBstatic = new_solid;
	rigidB = nullptr;

	//tiempo de vida
	remainingTime = lifeTime = timeLife;

}

RigidBody::~RigidBody()
{
	if (renderItem!=nullptr) 
	{ 
		DeregisterRenderItem(renderItem); renderItem = nullptr; 
	}
	if (rigidB != nullptr) {
		 rigidB->release();
	}
	else
	{
		rigidBstatic->release();
	}
}

void RigidBody::integrate(double t)
{
	//disminuye tiempo por vivir
	remainingTime -= t;
}
void RigidBody::setPos(Vector3 v)
{
	if (rigidBstatic != nullptr) {
		physx::PxTransform tr = rigidBstatic->getGlobalPose();  tr.p = v;  rigidBstatic->setGlobalPose(tr);
	}
	else
	{
		physx::PxTransform tr = rigidB->getGlobalPose();  tr.p = v;  rigidB->setGlobalPose(tr);
	}
}
void RigidBody::addShape(itemShape s, float size, Vector3 boxSize)
{
	switch (s)
	{
	case SPHERE:  shape = CreateShape(physx::PxSphereGeometry(size));  break;
	case BOX:
		Vector3 s = Vector3(size, size, size);
		if (size == 0) s = boxSize;
		physx::PxBoxGeometry box(s/2);
		shape = CreateShape(box); break;
	}
	
}
