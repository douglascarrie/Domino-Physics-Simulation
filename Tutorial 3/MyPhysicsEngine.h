#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>


namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(144.f/255.f,238.f/255.f,144.f/255.f),
		PxVec3(8.f / 255.f,66.f / 255.f,200.f / 255.f),PxVec3(77.f / 23.f,66.f / 255.f,111.f / 255.f) };

	//pyramid vertices
	static PxVec3 pyramid_verts[] = {PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1)};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxReal density=1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), pose, density)
		{
		}
	};

	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose=PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs),end(pyramid_trigs)), pose)
		{
		}
	};

	struct FilterGroup
	{
		enum Enum
		{
			ACTOR0		= (1 << 0),
			ACTOR1		= (1 << 1),
			ACTOR2		= (1 << 2)
			//add more if you need
		};
	};

	///An example class showing the use of springs (distance joints).
	class Trampoline
	{
		vector<DistanceJoint*> springs;
		Box *bottom, *top;

	public:
		Trampoline(const PxVec3& dimensions=PxVec3(1.f,1.f,1.f), PxReal stiffness=100.f, PxReal damping=15.f)
		{
			PxReal thickness = .1f;
			bottom = new Box(PxTransform(PxVec3(0.f,thickness,0.f)),PxVec3(dimensions.x,thickness,dimensions.z));
			top = new Box(PxTransform(PxVec3(0.f,dimensions.y+thickness,0.f)),PxVec3(dimensions.x,thickness,dimensions.z));
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,-dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,-dimensions.z)));

			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
			}
		}

		void AddToScene(Scene* scene)
		{
			scene->Add(bottom);
			scene->Add(top);
		}

		~Trampoline()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}
	};


	class Ball 
	{

	public:
		Sphere* ball;
		

		Ball(PxReal radius = 0.9f)
		{
			//originalPosition = position;
			

			ball = new Sphere(PxTransform(PxVec3(-17.5f, 1.5f, -15.f)), radius, 15);
			ball->Color(color_palette[6]);
			//ball->Mass(1.0f);

			
		}
		void AddToScene(Scene* scene)
		{
			scene->Add(ball);
			
		}
		void addForce(PxVec3 force)
		{
			PxRigidDynamic* ballDynamic = (PxRigidDynamic*)ball->Get();
			ballDynamic->addForce(force * 24);
			
		}

		
	};

	class CompoundShapeCross
	{

	public:
		Rect* rect1, * rect2, *rect3, *rect4;


		CompoundShapeCross()
		{
			//originalPosition = position;
			PxRigidBody* object1 = (PxRigidBody*)rect1->Get();
			PxRigidBody* object2 = (PxRigidBody*)rect2->Get();
			PxRigidBody* object3 = (PxRigidBody*)rect3->Get();
			PxRigidBody* object4 = (PxRigidBody*)rect4->Get();

			rect1 = new Rect(PxTransform(PxVec3(0.f, 0.5f, 0.f)));
			rect2 = new Rect(PxTransform(PxVec3(0.f, 0.5f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))));
			rect3 = new Rect(PxTransform(PxVec3(0.f, 0.5f, 0.f), PxQuat(PxPi / 4, PxVec3(0.f, 1.f, 0.f))));
			rect4 = new Rect(PxTransform(PxVec3(0.f, 0.5f, 0.f), PxQuat(PxPi / 6, PxVec3(0.f, 1.f, 0.f))));

			rect1->Color(color_palette[6]);
			rect2->Color(color_palette[6]);
			//ball->Mass(1.0f);
			

		}
		void AddToScene(Scene* scene)
		{
			scene->Add(rect1);
			scene->Add(rect2);
			scene->Add(rect3);
			scene->Add(rect4);

		}



	};
	class ShootObject
	{

	public:
		Box* box;


		ShootObject( PxReal radius = 3.f)
		{
			//PxVec3 camDirection
			//originalPosition = position;
			/*std::vector<DynamicActor*> objectsFire(2, 0);
			objectsFire[0] = new Box(PxTransform(PxVec3(0.0f, 0.f, 0.f)));
			objectsFire[0]->Color(color_palette[2]);*/
			box = new Box(PxTransform(PxVec3(0.0f, 0.f, 0.f)));
			
			box->Color(color_palette[2]);
			//ball->Mass(1.0f);

		}
		
		void Shoot(PxVec3 CameraPos, PxVec3 CameraDir)
		{
			
			PxRigidBody* object = (PxRigidBody*)box->Get();
			object->setGlobalPose(PxTransform(PxVec3(CameraPos)));
			
			physx::PxRigidBodyExt::addForceAtPos(*object, PxVec3(CameraDir.x*2000,CameraDir.y,CameraDir.z*2000), CameraDir, physx::PxForceMode::eFORCE);
			
			//addForceAtPos(object, const PxVec3 & force, const PxVec3);
			//object->addForce(PxVec3(CameraDir.x*400,CameraDir.y, CameraDir.z*400));
		}
		void AddToScene(Scene* scene)
		{
			scene->Add(box);

		}
		~ShootObject()
		{
			
			delete box;
		}
		


	};
	class ShootObject2
	{

	public:
		Sphere* sphere;


		ShootObject2(PxReal radius = 3.f)
		{
			//PxVec3 camDirection
			//originalPosition = position;
			/*std::vector<DynamicActor*> objectsFire(2, 0);
			objectsFire[0] = new Box(PxTransform(PxVec3(0.0f, 0.f, 0.f)));
			objectsFire[0]->Color(color_palette[2]);*/
			sphere = new Sphere(PxTransform(PxVec3(0.0f, 0.f, 0.f)), 1.6);

			sphere->Color(color_palette[4]);
			//ball->Mass(1.0f);

		}
	
		void Shoot(PxVec3 CameraPos, PxVec3 CameraDir)
		{

			PxRigidBody* object = (PxRigidBody*)sphere->Get();
			
			
			object->setGlobalPose(PxTransform(PxVec3(CameraPos)));

			physx::PxRigidBodyExt::addForceAtPos(*object, PxVec3(CameraDir.x * 3000, CameraDir.y, CameraDir.z * 3000), CameraDir, physx::PxForceMode::eFORCE);

			//addForceAtPos(object, const PxVec3 & force, const PxVec3);
			//object->addForce(PxVec3(CameraDir.x*400,CameraDir.y, CameraDir.z*400));
		}
		void AddToScene(Scene* scene)
		{
			scene->Add(sphere);

		}
		~ShootObject2()
		{

			delete sphere;
		}



	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		bool trigger;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						cerr << "The show is over, Final domino fell!" << endl;
						trigger = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;
					}
				}
			}
		}
		

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
#if PX_PHYSICS_VERSION >= 0x304000
		virtual void onAdvance(const PxRigidBody *const *bodyBuffer, const PxTransform *poseBuffer, const PxU32 count) {}
#endif
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
//		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
//			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
		Plane* plane;
		Box* box;
		Box2* b;
		Hammer* h;
		Domino* domino, * domino2;
		DistanceJoint* j;
		MySimulationEventCallback* my_callback;
		//RevoluteJoint* joint;
		Trampoline* tramp;
		CompoundObjectFloor* floor;
		
		
		
	public:
		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene() {};
		Sphere* sphere;
		Ball* ball;
		DominoLast* trigg;
		ShootObject* shoot;
		ShootObject2* shoot2;

		CompoundShapeCross* cross;
		CompoundObject* sha;
		BoxPlaceholder* bPlace;
		
		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eBODY_LIN_VELOCITY, 2.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
			
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			GetMaterial()->setDynamicFriction(.2f);

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);

			plane = new Plane();
			plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));

			Add(plane);

			//ball = new Ball(PxTransform(PxVec3(-20.f, 0.5f, -15.f)), float size);
			// ball to set off dominos
			ball = new Ball();
			ball->AddToScene(this);
			
			shoot = new ShootObject();
			shoot2 = new ShootObject2();


			/*cross = new CompoundShapeCross();
			cross->AddToScene(this);*/

			sha = new CompoundObject();
			sha->Color(color_palette[1]);
			Add(sha);

			floor = new CompoundObjectFloor();
			Add(floor);
			
			//sphere = new Sphere(PxTransform(PxVec3(-20.f, 0.5f, -15.f)));
			//sphere->Color(color_palette[1]);
			
			//Add(sphere);
			//create dominos

			//dominos for tower
			
			std::vector<Domino*> dominoTower(6, 0);
			dominoTower[1] = new Domino(PxTransform(PxVec3(-12.f , 1.5f, -15.f)));
			dominoTower[2] = new Domino(PxTransform(PxVec3(-9.f, 1.5f, -15.f)));
			dominoTower[3] = new Domino(PxTransform(PxVec3(-6.f, 1.5f, -15.f)));
			dominoTower[4] = new Domino(PxTransform(PxVec3(-3.f, 1.5f, -15.f)));
			dominoTower[5] = new Domino(PxTransform(PxVec3(0.5f, 1.5f, -15.f)));

			dominoTower[1]->Color(color_palette[(rand() % 6) + 1]);
			Add(dominoTower[1]); 
			dominoTower[2]->Color(color_palette[(rand() % 6) + 1]);
			Add(dominoTower[2]);
			dominoTower[3]->Color(color_palette[(rand() % 6) + 1]);
			Add(dominoTower[3]);
			dominoTower[4]->Color(color_palette[(rand() % 6) + 1]);
			Add(dominoTower[4]);
			dominoTower[5]->Color(color_palette[(rand() % 6) + 1]);
			Add(dominoTower[5]);
			


			for (int i = 0; i < 40; i++) {
				
				std::vector<Domino*> domino(40,0);
				domino[i] = new Domino(PxTransform(PxVec3(4.f +(i*3.5), 0.5f, -15.f)));

				domino[i]->Color(color_palette[(rand() % 6) + 1]);
				Add(domino[i]);
			}
			for (int i = 0; i < 9; i++) {
				std::vector<double> curveVal{ PxPi / 6,PxPi / 5,PxPi / 4,PxPi / 4, PxPi / 3,PxPi / 3, PxPi / 3,PxPi / 3, PxPi / 3,PxPi / 3, };
				std::vector<Domino*> dominoCurve(12, 0);
				if (i < 6) {
					dominoCurve[i] = new Domino(PxTransform(PxVec3(142.f + (i * 2), 0.5f, -15.f + (i * 2)), PxQuat(-curveVal[i], PxVec3(0.f, 1.f, 0.f))));
				}
				else {
					dominoCurve[i] = new Domino(PxTransform(PxVec3(142.f + (i * 2), 0.5f, -15.f + (i * 2)), PxQuat(-curveVal[i], PxVec3(0.f, 1.f, 0.f))));
				}
				
				//, PxQuat(PxPi /4, PxVec3(0.f,0.f,1.f))
				dominoCurve[i]->Color(color_palette[(rand() % 6) + 1]);
				Add(dominoCurve[i]);
				//PxRigidBody* dc = (PxRigidBody*)dominoCurve[i]->Get();
				//dc->setGlobalPose
			}
			for (int i = 0; i < 5; i++) {
				
				std::vector<Domino*> dominoCurveLine(12, 0);
				dominoCurveLine[i] = new Domino(PxTransform(PxVec3(159.f, 0.5f, 3.f + (i * 2.2)), PxQuat(PxPi /2, PxVec3(0.f, 1.f, 0.f))));
				//, PxQuat(PxPi /4, PxVec3(0.f,0.f,1.f))
				dominoCurveLine[i]->Color(color_palette[(rand() % 6) + 1]);
				Add(dominoCurveLine[i]);
				//PxRigidBody* dc = (PxRigidBody*)dominoCurve[i]->Get();
				//dc->setGlobalPose
			}
			for (int i = 0; i < 9; i++) {
				std::vector<double> curveVal2{ PxPi / 6,PxPi / 5,PxPi / 4,PxPi / 4, PxPi / 3,PxPi / 3, PxPi / 3,PxPi / 3,PxPi / 3,PxPi / 3, };
				std::vector<Domino*> dominoCurve2(20, 0);
				if (i < 6) {
					dominoCurve2[i] = new Domino(PxTransform(PxVec3(142.f + (i * 2), 0.5f, 30.f - (i * 2)), PxQuat(curveVal2[i], PxVec3(0.f, 1.f, 0.f))));
				}
				else {
					dominoCurve2[i] = new Domino(PxTransform(PxVec3(142.f + (i * 2), 0.5f, 30.f - (i * 2)), PxQuat(curveVal2[i], PxVec3(0.f, 1.f, 0.f))));
				}
				
				//, PxQuat(PxPi /4, PxVec3(0.f,0.f,1.f))
				dominoCurve2[i]->Color(color_palette[(rand() % 6) + 1]);
				Add(dominoCurve2[i]);
				//PxRigidBody* dc = (PxRigidBody*)dominoCurve[i]->Get();
				//dc->setGlobalPose
			}
			for (int i = 1; i < 70; i++) {

				std::vector<Domino*> domino2(70, 0);
				domino2[i] = new Domino(PxTransform(PxVec3(144.f - (i * 3.5), 0.5f, 30.f)));

				domino2[i]->Color(color_palette[(rand() % 6) + 1]);
				Add(domino2[i]);
			}
			
			

			//box2 = new Box(PxTransform(PxVec3(-4.f, 8.f, -15.f)));
			//b = new Box2(PxTransform(PxVec3(-20.f, 16.f, -20.f)));
			h = new Hammer(PxTransform(PxVec3(-20.f, 16.f, -20.f)));
			Add(h);
			bPlace = new BoxPlaceholder(PxTransform(PxVec3(-16.f, 8.f, -15.f)));
			bPlace->Color(color_palette[4]);
			Add(bPlace);
			//Add(box2);
			//Add(b);
			//j = new DistanceJoint(NULL, PxTransform(PxVec3(-18.f, 8.f, -15.f)),box3, PxTransform(PxVec3(-18.f, 10.f, -15.f)));
			
			//->setConstraintFlag(PxConstraintFlag::eVISUALIZATION);
			//joint two boxes together
			//the joint is fixed to the centre of the first box, oriented by 90 degrees around the Y axis
			//and has the second object attached 5 meters away along the Y axis from the first object.
			RevoluteJoint joint(nullptr, PxTransform(PxVec3(-14.f,10.f,-15.f), PxQuat(PxPi/2, PxVec3(0.f,1.f,0.f))), h, PxTransform(PxVec3(0.f,3.f,0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))));
			

			// trigger for end
			trigg = new DominoLast(PxTransform(PxVec3(-101.f, 0.5f, 30.f)));
			trigg->Color(color_palette[5]);
			Add(trigg);
			trigg->SetTrigger(true);
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);
			//PxJoint joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
			//PxQuat(PxPi / 8, PxVec3(0.f, 0.f, 1.f)))
			
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
		}

		/// An example use of key release handling
		void ExampleKeyReleaseHandler()
		{
			cerr << "I am realeased!" << endl;
		}

		/// An example use of key presse handling
		void ExampleKeyPressHandler()
		{
			cerr << "I am pressed!" << endl;
		}
	};
}
