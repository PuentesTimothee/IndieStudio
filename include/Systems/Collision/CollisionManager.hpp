//
// Created by puentes on 26/05/17.
//

#ifndef INDIE_COLLISIONMANAGER_HPP
#define INDIE_COLLISIONMANAGER_HPP

#include <Ogre.h>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

#include "Systems/Collision/CollisionConvertion.hpp"
#include "Systems/Collision/CollisionObject.hpp"
#include "Systems/Collision/CollisionBody.hpp"
#include "Systems/Collision/HitBox.hpp"

namespace Gauntlet
{
  struct CollisionData
  {
   public:
    std::unique_ptr<Gauntlet::CollisionObject>	obj;
    std::vector<int>				hitId;

    CollisionData(Gauntlet::CollisionObject *obj);
  };

  class CollisionManager
  {
   private:
    std::unique_ptr<btBroadphaseInterface>			_broadphase;
    std::unique_ptr<btDefaultCollisionConfiguration>		_collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher>			_dispatcher;
    std::unique_ptr<btSequentialImpulseConstraintSolver>	_solver;

    std::shared_ptr<btDiscreteDynamicsWorld>			_world;
    std::vector<Gauntlet::CollisionData>			_objects;

    Ogre::SceneManager						*_sceneMgr;
   public:
    CollisionManager(Ogre::SceneManager *sceneMgr);
    ~CollisionManager();

    Gauntlet::CollisionBody	*addPlane(Ogre::SceneNode		*node,
					     Ogre::Vector3 const 	&normal,
					     bool			isStatic);
    Gauntlet::CollisionBody	*addBox(Ogre::SceneNode			*node,
					   Ogre::Vector3 const		&size,
					   bool				isStatic);

    Gauntlet::HitBox		*addHitBox(Ogre::SceneNode		*node,
					       Ogre::Vector3 const	&size,
					       Ogre::Vector3 const	&at,
					       Ogre::Quaternion const	&rot);

    void			updateSimulation();
    void 			getCollision() const;
    bool			addToListOfHit(btCollisionObject const *obj,
					       int id);
    void 			deleteBody(Gauntlet::CollisionObject *obj);
  };
}

#endif //INDIE_COLLISIONMANAGER_HPP
