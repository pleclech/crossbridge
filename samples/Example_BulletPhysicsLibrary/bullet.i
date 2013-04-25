// Copyright (c) 2013 Adobe Systems Inc

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

%{
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h"
#include "BulletDynamics/ConstraintSolver/btConstraintSolver.h"
#ifdef USE_PTHREADS
#include "BulletMultiThreaded/PosixThreadSupport.h"
#include "BulletMultiThreaded/btThreadSupportInterface.h"
#include "BulletMultiThreaded/btParallelConstraintSolver.h"
#include "BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.h"
#include "BulletMultiThreaded/SpuGatheringCollisionDispatcher.h"
#endif
#include <math.h>
#include <AS3/AS3.h>

inline btVector3 QuaternionToEuler(const btQuaternion &q) {
	btScalar X = q.getX();
	btScalar Y = q.getY();
	btScalar Z = q.getZ();
	btScalar W = q.getW();
	btScalar XX = X * X;
	btScalar YY = Y * Y;
	btScalar ZZ = Z * Z;
	btScalar WW = W * W;

	btVector3 result;
	result.setX(atan2f(2.0f * (Y * Z + X * W), -XX - YY + ZZ + WW));
	result.setY(asinf(-2.0f * (X * Z - Y * W)));
	result.setZ(atan2f(2.0f * (X * Y + Z * W), XX - YY - ZZ + WW));
	result *= 180.0/M_PI;
	return result;
}

void positionAndRotateMesh() __attribute__((used,
	annotate("as3sig:public function positionAndRotateMesh(mesh:*, rigidBody:*):void"),
	annotate("as3package:org.bulletphysics"),
	annotate("as3import:flash.geom.Vector3D")));

void positionAndRotateMesh()
{
	btRigidBody *rb = NULL;
	AS3_GetScalarFromVar(rb, rigidBody.swigCPtr);

	btMotionState *ms = rb->getMotionState();

	btTransform trans;
	ms->getWorldTransform(trans);
	btVector3 pos = trans.getOrigin();

	AS3_CopyScalarToVar(mesh.x, pos.getX());
	AS3_CopyScalarToVar(mesh.y, pos.getY());
	AS3_CopyScalarToVar(mesh.z, pos.getZ());

	btVector3 eulerAngles = QuaternionToEuler(trans.getRotation());
	AS3_CopyScalarToVar(mesh.rotationX, eulerAngles.getX());
	AS3_CopyScalarToVar(mesh.rotationY, eulerAngles.getY());
	AS3_CopyScalarToVar(mesh.rotationZ, eulerAngles.getZ());
}

//btRigidBodyConstructionInfo.create(mass, ms.swigCPtr, shape.swigCPtr, inertia.swigCPtr)
btRigidBody* createRigidBody(btScalar mass, btDefaultMotionState *ms, btCollisionShape *shape, 
								btVector3 *inertia, btScalar restitution, btScalar friction)
{
	btRigidBody::btRigidBodyConstructionInfo rbci = btRigidBody::btRigidBodyConstructionInfo(mass, ms, shape, *inertia);
	rbci.m_restitution = restitution;
	rbci.m_friction = friction;

	return new btRigidBody(rbci);
}

#ifdef USE_PTHREADS
SpuGatheringCollisionDispatcher* createThreadedDispatcher(btDefaultCollisionConfiguration *collisionConfig, int numTasks)
{
	PosixThreadSupport::ThreadConstructionInfo ctci("collision",
								processCollisionTask,
								createCollisionLocalStoreMemory,
								numTasks);

	btThreadSupportInterface *tsi = new PosixThreadSupport(ctci);
    
    return new SpuGatheringCollisionDispatcher(tsi, numTasks, collisionConfig);
}

btParallelConstraintSolver* createThreadedSolver(int numTasks)
{
	PosixThreadSupport::ThreadConstructionInfo stci("solver",
								SolverThreadFunc,
								SolverlsMemoryFunc,
								numTasks);

	btThreadSupportInterface *tsi = new PosixThreadSupport(stci);
    
    return new btParallelConstraintSolver(tsi);
}
#endif

%}

// Deal with overloaded copy constructors
%ignore btTransform(const btTransform&);
%ignore btClock(const btClock&);

// TODO: these cause problems due to overloaded methods not being detected
// as overloaded by swig. Ignore for now.
%ignore getCollisionShape;
%ignore setValue;

// Declared in bullet headers but never defined
%ignore Enter_Largest_Child;

%include "LinearMath/btScalar.h"

///Bullet's btCollisionWorld and btCollisionObject definitions
%include "BulletCollision/CollisionDispatch/btCollisionWorld.h"
%include "BulletCollision/CollisionDispatch/btCollisionObject.h"

///Collision Shapes
%include "BulletCollision/CollisionShapes/btCollisionShape.h"
%include "BulletCollision/CollisionShapes/btBoxShape.h"
%include "BulletCollision/CollisionShapes/btSphereShape.h"
%include "BulletCollision/CollisionShapes/btCapsuleShape.h"
%include "BulletCollision/CollisionShapes/btCylinderShape.h"
%include "BulletCollision/CollisionShapes/btConeShape.h"
%include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
%include "BulletCollision/CollisionShapes/btConvexHullShape.h"
%include "BulletCollision/CollisionShapes/btTriangleMesh.h"
%include "BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h"
%include "BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h"
%include "BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h"
%include "BulletCollision/CollisionShapes/btTriangleMeshShape.h"
%include "BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h"
%include "BulletCollision/CollisionShapes/btCompoundShape.h"
%include "BulletCollision/CollisionShapes/btTetrahedronShape.h"
%include "BulletCollision/CollisionShapes/btEmptyShape.h"
%include "BulletCollision/CollisionShapes/btMultiSphereShape.h"
%include "BulletCollision/CollisionShapes/btUniformScalingShape.h"

///Narrowphase Collision Detector
%include "BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h"

//btSphereBoxCollisionAlgorithm is broken, use gjk for now
%include "BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h"
%include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"

///Dispatching and generation of collision pairs (broadphase)
%include "BulletCollision/BroadphaseCollision/btBroadphaseInterface.h"
%include "BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
%include "BulletCollision/BroadphaseCollision/btSimpleBroadphase.h"
%include "BulletCollision/BroadphaseCollision/btAxisSweep3.h"
//%include "BulletCollision/BroadphaseCollision/btMultiSapBroadphase.h"
%include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"

///Math library & Utils
%include "LinearMath/btQuadWord.h"
%include "LinearMath/btQuaternion.h"
%include "LinearMath/btTransform.h"
%include "LinearMath/btDefaultMotionState.h"
%include "LinearMath/btQuickprof.h"
%include "LinearMath/btIDebugDraw.h"
%include "LinearMath/btSerializer.h"
%include "LinearMath/btVector3.h"

%include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
%include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
%include "BulletDynamics/Dynamics/btRigidBody.h"

// Threading!
#ifdef USE_PTHREADS
%include "BulletMultiThreaded/PosixThreadSupport.h"
%include "BulletMultiThreaded/btThreadSupportInterface.h"
%include "BulletMultiThreaded/SpuGatheringCollisionDispatcher.h"
%include "BulletMultiThreaded/btParallelConstraintSolver.h"
%include "BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.h"

SpuGatheringCollisionDispatcher* createThreadedDispatcher(btDefaultCollisionConfiguration *collisionConfig, int numTasks);
btParallelConstraintSolver* createThreadedSolver(int numTasks);
#endif

btRigidBody* createRigidBody(btScalar mass, btDefaultMotionState *ms, btCollisionShape *shape, 
								btVector3 *inertia, btScalar restitution, btScalar friction);