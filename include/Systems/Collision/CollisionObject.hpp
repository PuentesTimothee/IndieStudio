//
// Created by puentes on 29/05/17.
//

#ifndef INDIE_COLLISIONOBJECT_HPP
#define INDIE_COLLISIONOBJECT_HPP

#include <Ogre.h>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "Systems/Collision/CollisionConvertion.hpp"

namespace Gauntlet
{
  class CollisionObject
  {
   protected:
    std::shared_ptr<btCollisionObject>	_object;
    std::shared_ptr<btCollisionShape>	_shape;
    std::shared_ptr<btDynamicsWorld>	_world;

    CollisionObject(std::shared_ptr<btCollisionShape> const	&shape,
		    std::shared_ptr<btDynamicsWorld> const	&world);
   public:
    virtual				~CollisionObject();

    virtual void			setPosition(Ogre::Vector3 const &pos);
    virtual void			setOrientation(Ogre::Quaternion const &dir);

    virtual Ogre::Vector3		getPosition() const;
    virtual Ogre::Quaternion		getOrientation() const;
    virtual void			setLinearVelocity(Ogre::Vector3	const &) = 0;
    virtual void			addLinearVelocity(Ogre::Vector3	const &) = 0;

    virtual void 			getEvent() const {};
    btCollisionObject			*getBtObj() const;
  };
};


#endif //INDIE_COLLISIONOBJECT_HPP
