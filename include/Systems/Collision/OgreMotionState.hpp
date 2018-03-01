//
// Created by puentes on 31/05/17.
//

#ifndef INDIE_OGREMOTIONSTATE_HPP
#define INDIE_OGREMOTIONSTATE_HPP

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#include "Systems/Collision/CollisionConvertion.hpp"

namespace Gauntlet
{
  class OgreMotionState : public btMotionState
  {
   protected:
    Ogre::SceneNode*	_node;
    Ogre::Vector3	_offset;
    btTransform		_defaultPos;

   public:
    OgreMotionState(btTransform const	&defaultPos,
		    Ogre::SceneNode	*node,
		    Ogre::Vector3 const	&offset = Ogre::Vector3::ZERO);

    virtual ~OgreMotionState() {};

    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);
  };
}


#endif //INDIE_OGREMOTIONSTATE_HPP
