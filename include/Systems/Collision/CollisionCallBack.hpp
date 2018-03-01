//
// Created by puentes on 30/05/17.
//

#ifndef INDIE_COLLISIONCALLBACK_HPP
#define INDIE_COLLISIONCALLBACK_HPP

#include <iostream>
#include <memory>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

namespace Gauntlet
{
  struct CollisionCallBack : public btCollisionWorld::ContactResultCallback
  {
    CollisionCallBack(btRigidBody *body,
		      std::shared_ptr<btDynamicsWorld> const &world);

    btRigidBody *_body;

    virtual bool needsCollision(btBroadphaseProxy *proxy) const;

    virtual btScalar addSingleResult(btManifoldPoint &cp,
				     const btCollisionObjectWrapper *colObj0, int partId0, int index0,
				     const btCollisionObjectWrapper *colObj1, int partId1, int index1);
  };

  bool ContactAddedCallBack(btManifoldPoint &cp,
			    const btCollisionObjectWrapper *colObj0,
			    int partId0, int index0,
			    const btCollisionObjectWrapper *colObj1,
			    int partId1, int index1);

};


#endif //INDIE_COLLISIONCALLBACK_HPP
