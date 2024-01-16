#include "Bolo.h"
#include "BoloManager.h"
#include <iostream>
//bolo default
Bolo::Bolo(BoloManager* b, physx::PxScene* scene, physx::PxPhysics* phys,float Size, physx::PxTransform Pos, bool Model, bool Muelle)
{
	boloMngr = b;
	model = Model;
	size = Size;
	//render
	color = Vector4{ 0.29,0,0.51,1 };
	shapeType=BOX;

	//phys
	gScene = scene;
	gPhysics = phys;

	//creación sólido rígido (dinámico)
	physx::PxRigidDynamic* new_solid;
	new_solid = gPhysics->createRigidDynamic(Pos);
	new_solid->setLinearVelocity({0,0,0});
	new_solid->setAngularVelocity({0,0,0});
	new_solid->setLinearDamping(0.98);

	//tensor  de inercia
	recSize = size* Vector3{ 2,4,2 };
	new_solid->setMass(3.0f);
	new_solid->setMassSpaceInertiaTensor({ recSize.y * recSize.z, 0.2, recSize.x * recSize.y});//(recSize.x * recSize.z)/4

	//shape
	RigidBody::addShape(BOX, 0, recSize);
	new_solid->attachShape(*shape);
	
	if (!model)
	{
		renderItem = new RenderItem(shape, new_solid, color);
		gScene->addActor(*new_solid);
	}
	rigidB = new_solid;
	rigidBstatic = nullptr;

	//tiempo de vida
	remainingTime = lifeTime = 2000000;

	//muelle
	muelle = Muelle;
	
}

Bolo::Bolo(BoloManager* b, physx::PxScene* scene, physx::PxPhysics* phys, Vector4 Color, float Size, physx::PxTransform Pos, bool Model, float timeLife, bool Muelle)
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

	//tamaño
	recSize = size * Vector3{ 2,4,2 };

	//creación sólido rígido (dinámico)
	physx::PxRigidDynamic* new_solid;
	new_solid = gPhysics->createRigidDynamic(Pos);
	new_solid->setLinearVelocity({ 0,0,0 });
	new_solid->setAngularVelocity({0,0,0});
	new_solid->setLinearDamping(0.98);

	new_solid->setMass(3.0f);
	new_solid->setMassSpaceInertiaTensor({ recSize.y * recSize.z, recSize.x * recSize.z, recSize.x * recSize.y });


	RigidBody::addShape(BOX, 0, recSize);
	new_solid->attachShape(*shape);
	if (!model) {
		renderItem = new RenderItem(shape, new_solid, color);
		gScene->addActor(*new_solid);
	}
	rigidB = new_solid;
	rigidBstatic = nullptr;

	//tiempo de vida
	remainingTime = lifeTime = timeLife;
	//muelle
	muelle = Muelle;


}

Bolo::~Bolo()
{
	boloMngr->onBoloDeath(this);
}
