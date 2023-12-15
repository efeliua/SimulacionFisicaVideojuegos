#include "RigidBody.h"


RigidBody::RigidBody(physx::PxScene* scene, physx::PxPhysics* phys, Vector4 Color, float Size, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, float timeLife, bool model, float Density, itemShape s, Vector3 boxSize, float Dam)
{
	//render
	color = Color;
	size = Size;
	shapeType = s;

	//phys
	gScene = scene;
	gPhysics = phys;

	//tam
	if (size != 0) { recSize = Vector3(size, size, size); }
	else recSize = boxSize;

	physx::PxRigidDynamic* new_solid;
	new_solid = gPhysics->createRigidDynamic(Pos);
	new_solid->setLinearVelocity(LinearVel);
	new_solid->setAngularVelocity(AngularVel);
	new_solid->setLinearDamping(Dam);
	physx::PxRigidBodyExt::updateMassAndInertia(*new_solid, Density);
	
	if (!model) {
		addShape(s, size, boxSize);
		new_solid->attachShape(*shape);
		gScene->addActor(*new_solid);
		renderItem = new RenderItem(shape, new_solid, color);
	}
	rigidB = new_solid;
	rigidBstatic = NULL;

	remainingTime = lifeTime = timeLife;
}

RigidBody::RigidBody(physx::PxScene* scene, physx::PxPhysics* phys, Vector4 Color, float Size, physx::PxTransform Pos, float timeLife, bool model, itemShape s, Vector3 boxSize)
{
	//render
	color = Color;
	size = Size;
	shapeType = s;

	//phys
	gScene = scene;
	gPhysics = phys;

	//tam
	if (size != 0) { recSize = Vector3(size, size, size); }
	else recSize = boxSize;

	physx::PxRigidStatic* new_solid;
	new_solid = gPhysics->createRigidStatic(Pos);

	if (!model) {
		addShape(s, size, boxSize);
		new_solid->attachShape(*shape);
		renderItem = new RenderItem(shape, new_solid, color);
	}
	gScene->addActor(*new_solid);
	rigidBstatic = new_solid;
	rigidB = NULL;

	remainingTime = lifeTime = timeLife;

}

RigidBody::~RigidBody()
{
	if (renderItem!=nullptr) 
	{ 
		DeregisterRenderItem(renderItem); renderItem = nullptr; 
	}
	if (rigidB != NULL) {
		 rigidB->release();//gScene->removeActor(*rigidB);
	}
	else
	{
		rigidBstatic->release();//gScene->removeActor(*rigidBstatic);
	}
}

void RigidBody::integrate(double t)
{
	// Clear accum?
	//clearForce();

	//disminuye tiempo por vivir
	remainingTime -= t;
}
void RigidBody::addShape(itemShape s, float size, Vector3 boxSize)
{
	switch (s)
	{
	case SPHERE:  shape = CreateShape(physx::PxSphereGeometry(size));  break;
	case BOX:
		Vector3 s = Vector3(size, size, size);
		if (size == 0) s = boxSize;
		physx::PxBoxGeometry box(s);
		shape = CreateShape(box); break;
	}
	
}
