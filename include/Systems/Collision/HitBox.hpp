//
// Created by puentes on 01/06/17.
//

#ifndef INDIE_HITBOX_HPP
#define INDIE_HITBOX_HPP

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#include "Systems/Collision/CollisionConvertion.hpp"
#include "Systems/Collision/CollisionCallBack.hpp"
#include "Systems/Collision/CollisionObject.hpp"
#include "Systems/Collision/OgreMotionState.hpp"

namespace Gauntlet
{
  class HitBox : public CollisionObject
  {
   private:
    btRigidBody						*_body;
    std::shared_ptr<btMotionState>			_motionState;
    std::shared_ptr<Gauntlet::CollisionCallBack>	_callback;

   public:
    HitBox(std::shared_ptr<btCollisionShape> const	&shape,
	   Ogre::SceneNode				*node,
	   Ogre::Vector3 const				&offset,
	   std::shared_ptr<btDynamicsWorld> const	&world);

    virtual void			setLinearVelocity(Ogre::Vector3	const &dir);
    virtual void			addLinearVelocity(Ogre::Vector3	const &dir);
  };
}

#endif //INDIE_HITBOX_HPP
