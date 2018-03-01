//
// Created by puentes on 29/05/17.
//

#ifndef INDIE_COLLISIONCONVERTION_HPP
#define INDIE_COLLISIONCONVERTION_HPP

#include <Ogre.h>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

class OgreToBullet
{
 public:
  static btVector3		convert(Ogre::Vector3 const &vector);
  static btQuaternion		convert(Ogre::Quaternion const &quat);
};

class BulletToOgre
{
 public:
  static Ogre::Vector3		convert(btVector3 const &vector);
  static Ogre::Quaternion	convert(btQuaternion const &quat);
};

#endif //INDIE_COLLISIONCONVERTION_HPP
