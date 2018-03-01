//
// Created by puentes on 31/05/17.
//

#include "Systems/Collision/CollisionBody.hpp"

Gauntlet::CollisionBody::CollisionBody(std::shared_ptr<btCollisionShape> const	&shape,
				       int					mass,
				       Ogre::SceneNode				*node,
				       std::shared_ptr<btDynamicsWorld> const &	world,
				       Ogre::Vector3 const			&offset)
	: CollisionObject(shape, world),
	  _node(node),
	  _body(nullptr),
	  _motionState(nullptr)
{
  btVector3		pos = OgreToBullet::convert(node->getPosition());
  btQuaternion		orientation = OgreToBullet::convert(node->getOrientation());

  this->initObject(mass, pos, orientation, offset);
}

Gauntlet::CollisionBody::CollisionBody(std::shared_ptr<btCollisionShape> const	&shape,
				       btVector3 const				&pos,
				       std::shared_ptr<btDynamicsWorld> const	&world,
				       Ogre::Vector3 const			&offset)
	: CollisionObject(shape, world),
	  _node(nullptr),
	  _body(nullptr),
	  _motionState(nullptr)
{
    btQuaternion	quat(0, 1, 0, 0);

    this->initObject(0, pos, quat, offset);
}

Gauntlet::CollisionBody::~CollisionBody()
{
  this->_motionState.reset();
}

void			Gauntlet::CollisionBody::initObject(int				mass,
								btVector3 const		&pos,
								btQuaternion const 	&orientation,
								Ogre::Vector3 const	&offset)
{
  btTransform		defaultPos(orientation, pos);

  this->_motionState.reset(new Gauntlet::OgreMotionState(defaultPos,
							 this->_node,
							 offset));

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass * 100,
						       this->_motionState.get(),
						       this->_shape.get());
  this->_body = new btRigidBody(rigidBodyCI);
  this->_object.reset(this->_body);
  this->_object->setFriction(0);
  this->_world->addRigidBody(this->_body,
			     ((mass == 0) ?
			      (btBroadphaseProxy::StaticFilter) :
			      (btBroadphaseProxy::KinematicFilter)),
			     btBroadphaseProxy::KinematicFilter | btBroadphaseProxy::StaticFilter);

  if (mass != 0)
    this->_body->setActivationState(DISABLE_DEACTIVATION);
}

void			Gauntlet::CollisionBody::addLinearVelocity(Ogre::Vector3 const &dir)
{
  this->setLinearVelocity(dir + BulletToOgre::convert(this->_body->getLinearVelocity()));
}

void			Gauntlet::CollisionBody::setLinearVelocity(Ogre::Vector3 const &dir)
{
  this->_body->setLinearVelocity(OgreToBullet::convert(dir));
}

void Gauntlet::CollisionBody::setPosition(Ogre::Vector3 const &pos)
{
  this->_node->setPosition(pos);
  CollisionObject::setPosition(pos);
}

void Gauntlet::CollisionBody::setOrientation(Ogre::Quaternion const &dir)
{
  this->_node->setOrientation(dir);
  CollisionObject::setOrientation(dir);
}
