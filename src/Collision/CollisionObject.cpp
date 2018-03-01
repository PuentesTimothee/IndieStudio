//
// Created by puentes on 29/05/17.
//

#include "Systems/Collision/CollisionObject.hpp"

Gauntlet::CollisionObject::CollisionObject(std::shared_ptr<btCollisionShape> const	&shape,
					   std::shared_ptr<btDynamicsWorld> const	&world)
	: _object(nullptr),
	  _shape(shape),
	  _world(world)
{
}

Gauntlet::CollisionObject::~CollisionObject()
{
  this->_world->removeCollisionObject(this->_object.get());
  this->_shape.reset();
  this->_world.reset();
}

Ogre::Quaternion	Gauntlet::CollisionObject::getOrientation() const
{
  btTransform		trans = this->_object->getWorldTransform();

  return (BulletToOgre::convert(trans.getRotation()));
}

Ogre::Vector3		Gauntlet::CollisionObject::getPosition() const
{
  btTransform		trans = this->_object->getWorldTransform();

  return (BulletToOgre::convert(trans.getOrigin()));
}

void			Gauntlet::CollisionObject::setPosition(Ogre::Vector3 const &pos)
{
  btTransform		oldTransform = this->_object->getWorldTransform();

  oldTransform.setOrigin(OgreToBullet::convert(pos));
  this->_object->setWorldTransform(oldTransform);
}

void			Gauntlet::CollisionObject::setOrientation(Ogre::Quaternion const &dir)
{
  btTransform		oldTransform = this->_object->getWorldTransform();

  oldTransform.setRotation(OgreToBullet::convert(dir));
  this->_object->setWorldTransform(oldTransform);
}

btCollisionObject	*Gauntlet::CollisionObject::getBtObj() const
{
  return (this->_object.get());
}
