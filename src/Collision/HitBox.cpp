//
// Created by puentes on 01/06/17.
//

#include "Systems/Collision/HitBox.hpp"

Gauntlet::HitBox::HitBox(std::shared_ptr<btCollisionShape> const	&shape,
			 Ogre::SceneNode				*node,
			 Ogre::Vector3 const				&offset,
			 std::shared_ptr<btDynamicsWorld> const		&world)
	: CollisionObject(shape, world),
	  _body(nullptr),
	  _callback(nullptr)
{
  btQuaternion	quat;
  quat.setW(0);
  quat.setX(0);
  quat.setY(1);
  quat.setZ(0);
  btTransform	transform(quat);

  this->_motionState.reset(new Gauntlet::OgreMotionState(transform,
							 node,
							 offset));

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(70,
						       this->_motionState.get(),
						       this->_shape.get());
  this->_body = new btRigidBody(rigidBodyCI);
  this->_object.reset(this->_body);
  this->_object->setCollisionFlags(this->_object->getCollisionFlags() |
					   btCollisionObject::CF_NO_CONTACT_RESPONSE |
					   btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
  this->_world->addRigidBody(this->_body,
			     btBroadphaseProxy::KinematicFilter,
			     btBroadphaseProxy::KinematicFilter);
  this->_body->setActivationState(DISABLE_DEACTIVATION);
  this->_body->setGravity(btVector3(0, 0, 0));

  //this->_callback.reset(new Gauntlet::CollisionCallBack(this->_body, this->_world));
}

void 		Gauntlet::HitBox::setLinearVelocity(Ogre::Vector3 const &dir)
{
  this->_body->setLinearVelocity(OgreToBullet::convert(dir));
}

void		Gauntlet::HitBox::addLinearVelocity(Ogre::Vector3 const &dir)
{
  this->_body->setLinearVelocity(OgreToBullet::convert(dir) +
					 this->_body->getLinearVelocity());
}
