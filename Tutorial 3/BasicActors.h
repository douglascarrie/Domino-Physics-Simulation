#pragma once

#include "PhysicsEngine.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	///Plane class
	class Plane : public StaticActor
	{
	public:
		//A plane with default paramters: XZ plane centred at (0,0,0)
		Plane(PxVec3 normal=PxVec3(0.f, 1.f, 0.f), PxReal distance=0.f) 
			: StaticActor(PxTransformFromPlaneEquation(PxPlane(normal, distance)))
		{
			CreateShape(PxPlaneGeometry());
		}
	};

	///Sphere class
	class Sphere : public DynamicActor
	{
	public:
		//a sphere with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m
		// - denisty: 1kg/m^3
		
		Sphere(const PxTransform& pose=PxTransform(PxIdentity), PxReal radius=3.f, PxReal density=1.f) 
			: DynamicActor(pose)
		{ 
			CreateShape(PxSphereGeometry(radius), density);
		}
	
	};

	///Box class
	class Box : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Box(const PxTransform& pose=PxTransform(PxIdentity), PxVec3 dimensions=PxVec3(1.5f,1.5f,1.5f), PxReal density=.86f) 
			: DynamicActor(pose)
		{ 
			CreateShape(PxBoxGeometry(dimensions), density);
		}


	};
	class Box2 : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Box2(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(0.3f, 1.5f, 0.4f), PxReal density = .86f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}


	};
	class DominoLast : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		DominoLast(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(0.30f, 2.0f, 0.9f), PxReal density = .99f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			GetShape(0)->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
		}
	};
	class BoxPlaceholder : public StaticActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		BoxPlaceholder(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(0.01f, 0.01f, 0.01f), PxReal density = .86f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
		void move()
		{
			GetShape(0)->setLocalPose(PxTransform(PxVec3(4.f,80,0)));
		}

	};
	class Hammer : public DynamicActor
	{
	public:
		Hammer(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(1.5f, 0.5f, 1.3f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			// needs two adjacent squares 
			

			CreateShape(PxBoxGeometry(PxVec3(0.2f, 1.7f, 0.3f)), density);
			CreateShape(PxCapsuleGeometry(0.8f, 1.f), density);
			
			
			GetShape(1)->setLocalPose(PxTransform(PxVec3(0.f, -2.f, 0.f)));


		}
	};
	class Rect : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Rect(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(0.1f, 0.05f, 1.4f), PxReal density = .86f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}


	};

	///Box class
	class Domino : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Domino(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(0.30f, 2.0f, 0.9f), PxReal density = .99f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};
	class Capsule : public DynamicActor
	{
	public:
		Capsule(const PxTransform& pose=PxTransform(PxIdentity), PxVec2 dimensions=PxVec2(1.f,1.f), PxReal density=1.f) 
			: DynamicActor(pose)
		{
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
		}
	};

	///The ConvexMesh class
	class ConvexMesh : public DynamicActor
	{
	public:
		//constructor
		ConvexMesh(const std::vector<PxVec3>& verts, const PxTransform& pose=PxTransform(PxIdentity), PxReal density=1.f)
			: DynamicActor(pose)
		{
			PxConvexMeshDesc mesh_desc;
			mesh_desc.points.count = (PxU32)verts.size();
			mesh_desc.points.stride = sizeof(PxVec3);
			mesh_desc.points.data = &verts.front();
			mesh_desc.flags = PxConvexFlag::eCOMPUTE_CONVEX;
			mesh_desc.vertexLimit = 256;

			CreateShape(PxConvexMeshGeometry(CookMesh(mesh_desc)), density);
		}

		//mesh cooking (preparation)
		PxConvexMesh* CookMesh(const PxConvexMeshDesc& mesh_desc)
		{
			PxDefaultMemoryOutputStream stream;

			if(!GetCooking()->cookConvexMesh(mesh_desc, stream))
				throw new Exception("ConvexMesh::CookMesh, cooking failed.");

			PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

			return GetPhysics()->createConvexMesh(input);
		}
	};
	class CompoundObject : public StaticActor
	{
	public:
		CompoundObject(PxVec3 dimensions = PxVec3(0.06f, 0.06f, 1.3f), const PxTransform& pose = PxTransform(PxVec3(-8.f, 8.f, -15.f)), PxReal density = 1.f)
			: StaticActor(pose)
		{
			// needs two adjacent squares 
			vector<Box*> boxes;

			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);

			GetShape(0)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(1.f, 0.f, 0.f))));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / 3, PxVec3(1.f, 0.f, 0.f))));
			GetShape(4)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / 3, PxVec3(0.f, 1.f, 0.f))));
			GetShape(5)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / -3, PxVec3(0.f, 1.f, 0.f))));
			GetShape(6)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / -3, PxVec3(1.f, 0.f, 0.f))));
			GetShape(7)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / -6, PxVec3(1.f, 0.f, 0.f))));
			GetShape(8)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / 6, PxVec3(1.f, 0.f, 0.f))));
			GetShape(9)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / -6, PxVec3(0.f, 1.f, 0.f))));
			GetShape(10)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / 6, PxVec3(0.f, 1.f, 0.f))));

		}
	};
	class CompoundObjectFloor : public StaticActor
	{
	public:
		CompoundObjectFloor(PxVec3 dimensions = PxVec3(0.04f, 0.04f, 0.8f), const PxTransform& pose = PxTransform(PxVec3(-6.f, 0.f, -15.f)), PxReal density = 1.f)
			: StaticActor(pose)
		{
			// needs two adjacent squares 
			vector<Box*> boxes;

			CreateShape(PxBoxGeometry(PxVec3(12.f, 0.5f, 3.f)), density);
			CreateShape(PxBoxGeometry(PxVec3(9.f, 0.5f, 3.f)), density);
			CreateShape(PxBoxGeometry(PxVec3(6.f, 0.5f, 3.f)), density);
			CreateShape(PxBoxGeometry(PxVec3(3.f, 0.5f, 3.f)), density);
			//edge walls
			CreateShape(PxBoxGeometry(PxVec3(12.f, 3.f, 0.2f)), density);

			CreateShape(PxBoxGeometry(PxVec3(0.2f, 3.f, 3.f)), density);
			//CreateShape(PxBoxGeometry(dimensions), density);
			

			GetShape(1)->setLocalPose(PxTransform(PxVec3(-4.f, 0.5f, 0.f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-7.f, 1.f, 0.f)));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(-10.f, 1.5f, 0.f)));

			GetShape(4)->setLocalPose(PxTransform(PxVec3(-1.f, 0.f, -3.f)));
			GetShape(5)->setLocalPose(PxTransform(PxVec3(-13.f, 0.f, 0.f)));
			/*GetShape(1)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(1.f, 0.f, 0.f))));
			*/

		}
	};
	class CompoundShapeCap : public DynamicActor
	{
	public:
		CompoundShapeCap(PxVec3 dimensions1, PxVec3 dimensions2, const PxTransform& pose = PxTransform(PxIdentity), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			// create 4 capsules
			CreateShape(PxCapsuleGeometry(dimensions1.x, dimensions1.y), density);
			CreateShape(PxCapsuleGeometry(dimensions2.x, dimensions2.y), density);
			CreateShape(PxCapsuleGeometry(dimensions1.x, dimensions1.y), density);
			CreateShape(PxCapsuleGeometry(dimensions2.x, dimensions2.y), density);

			//GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f,0.f,-10.f)));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(dimensions1.x * 6, 0.f, 0.f)));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-dimensions1.x * 6, 0.f, 0.f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(0.f, 0.f, dimensions1.x * 6)));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(-dimensions1.x * 6, 0.f, dimensions1.x * 6)));
		}
	};
	///The TriangleMesh class
	class TriangleMesh : public StaticActor
	{
	public:
		//constructor
		TriangleMesh(const std::vector<PxVec3>& verts, const std::vector<PxU32>& trigs, const PxTransform& pose=PxTransform(PxIdentity))
			: StaticActor(pose)
		{
			PxTriangleMeshDesc mesh_desc;
			mesh_desc.points.count = (PxU32)verts.size();
			mesh_desc.points.stride = sizeof(PxVec3);
			mesh_desc.points.data = &verts.front();
			mesh_desc.triangles.count = (PxU32)trigs.size()/3;
			mesh_desc.triangles.stride = 3*sizeof(PxU32);
			mesh_desc.triangles.data = &trigs.front();

			CreateShape(PxTriangleMeshGeometry(CookMesh(mesh_desc)));
		}

		//mesh cooking (preparation)
		PxTriangleMesh* CookMesh(const PxTriangleMeshDesc& mesh_desc)
		{
			PxDefaultMemoryOutputStream stream;

			if(!GetCooking()->cookTriangleMesh(mesh_desc, stream))
				throw new Exception("TriangleMesh::CookMesh, cooking failed.");

			PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

			return GetPhysics()->createTriangleMesh(input);
		}
	};

	//Distance joint with the springs switched on
	class DistanceJoint : public Joint
	{
	public:
		DistanceJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = (PxJoint*)PxDistanceJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
			((PxDistanceJoint*)joint)->setDistanceJointFlag(PxDistanceJointFlag::eSPRING_ENABLED, true);
			Damping(1.f);
			Stiffness(1.f);
		}

		void Stiffness(PxReal value)
		{
			((PxDistanceJoint*)joint)->setStiffness(value);
		}

		PxReal Stiffness()
		{
			return ((PxDistanceJoint*)joint)->getStiffness();		
		}

		void Damping(PxReal value)
		{
			((PxDistanceJoint*)joint)->setDamping(value);
		}

		PxReal Damping()
		{
			return ((PxDistanceJoint*)joint)->getDamping();
		}
	};

	///Revolute Joint
	class RevoluteJoint : public Joint
	{
	public:
		RevoluteJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = PxRevoluteJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION,true);
			((PxRevoluteJoint*)joint)->setDriveVelocity(-5.f);
			SetLimits(-PxPi / 4, PxPi/3 );

			
		}

		void DriveVelocity(PxReal value)
		{
			//wake up the attached actors
			PxRigidDynamic *actor_0, *actor_1;
			((PxRevoluteJoint*)joint)->getActors((PxRigidActor*&)actor_0, (PxRigidActor*&)actor_1);
			if (actor_0)
			{
				if (actor_0->isSleeping())
					actor_0->wakeUp();
			}
			if (actor_1)
			{
				if (actor_1->isSleeping())
					actor_1->wakeUp();
			}
			((PxRevoluteJoint*)joint)->setDriveVelocity(value);
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		}

		PxReal DriveVelocity()
		{
			return ((PxRevoluteJoint*)joint)->getDriveVelocity();
		}

		void SetLimits(PxReal lower, PxReal upper)
		{
			((PxRevoluteJoint*)joint)->setLimit(PxJointAngularLimitPair(lower, upper));
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}
	};
}