#include "Bolo.h"
#include "BoloManager.h"
#include <iostream>
//bolo default
Bolo::Bolo(BoloManager* b, physx::PxScene* scene, physx::PxPhysics* phys, physx::PxTransform Pos,int Size)
{
	boloMngr = b;
	model = false;
	size = Size;
	//render
	color = Vector4{ 0.2,0.3,0.4,1 };
	shapeType=BOX;

	//phys
	gScene = scene;
	gPhysics = phys;

	//creaci�n s�lido r�gido (din�mico)
	physx::PxRigidDynamic* new_solid;
	new_solid = gPhysics->createRigidDynamic(Pos);
	new_solid->setLinearVelocity({0,0,0});
	new_solid->setAngularVelocity({0,0,0});
	new_solid->setLinearDamping(0.98);
	//physx::PxRigidBodyExt::updateMassAndInertia(*new_solid, 2);
	//tensor  de inercia
	recSize = size* Vector3{ 2,4,2 };
	new_solid->setMassSpaceInertiaTensor({ recSize.y * recSize.z, recSize.x * recSize.z, recSize.x * recSize.y });
	RigidBody::addShape(BOX, 0, recSize);
	new_solid->attachShape(*shape);
	
	renderItem = new RenderItem(shape, new_solid, color);
	
	gScene->addActor(*new_solid);
	rigidB = new_solid;
	rigidBstatic = nullptr;

	//tiempo de vida
	remainingTime = lifeTime = 2000000;

}

Bolo::Bolo(BoloManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 Color, float Size, physx::PxTransform Pos, float timeLife, bool Model)
{
	boloMngr = b;
	model = Model;

	//render
	color = Color;
	size = Size;
	shapeType = BOX;

	//phys
	gScene = scene;
	gPhysics = phys;

	//tama�o
	recSize = size * Vector3{ 2,4,2 };

	//creaci�n s�lido r�gido (din�mico)
	physx::PxRigidDynamic* new_solid;
	new_solid = gPhysics->createRigidDynamic(Pos);
	new_solid->setLinearVelocity({ 0,0,0 });
	new_solid->setAngularVelocity({0,0,0});
	new_solid->setLinearDamping(0.98);
	//physx::PxRigidBodyExt::updateMassAndInertia(*new_solid, Density);
	new_solid->setMassSpaceInertiaTensor({ recSize.y * recSize.z, recSize.x * recSize.z, recSize.x * recSize.y });


	RigidBody::addShape(BOX, 0, recSize);
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

Bolo::~Bolo()
{
	boloMngr->onBoloDeath(this);
}
