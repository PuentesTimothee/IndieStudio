//
// Created by puentes on 31/05/17.
//

#ifndef INDIE_COLLISIONBODY_HPP
#define INDIE_COLLISIONBODY_HPP

#include <Ogre.h>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

#include "Systems/Collision/CollisionConvertion.hpp"
#include "Systems/Collision/CollisionObject.hpp"
#include "Systems/Collision/OgreMotionState.hpp"

namespace Gauntlet
{
  class CollisionBody : public CollisionObject
  {
   private:
    Ogre::SceneNode			*_node;
    btRigidBody				*_body;
    std::shared_ptr<btMotionState>	_motionState;

    void 			initObject(int			mass,
					   btVector3 const	&pos,
					   btQuaternion	const	&orientation,
					   Ogre::Vector3 const	&offset);

   public:
    /*
     *  Visible object
     */
    CollisionBody(std::shared_ptr<btCollisionShape> const	&shape,
		  int 						mass,
		  Ogre::SceneNode				*node,
		  std::shared_ptr<btDynamicsWorld> const	&world,
		  Ogre::Vector3 const				&offset = Ogre::Vector3::ZERO);

    /*
     * Static Object
     */
    CollisionBody(std::shared_ptr<btCollisionShape> const	&shape,
		  btVector3 const				&pos,
		  std::shared_ptr<btDynamicsWorld> const	&world,
		  Ogre::Vector3 const				&offset = Ogre::Vector3::ZERO);

    virtual ~CollisionBody();

    void		setLinearVelocity(Ogre::Vector3	const &dir);
    void		addLinearVelocity(Ogre::Vector3	const &dir);

    virtual void	setPosition(Ogre::Vector3 const &pos);
    virtual void	setOrientation(Ogre::Quaternion const &dir);
  };
}

#endif //INDIE_COLLISIONBODY_HPP
