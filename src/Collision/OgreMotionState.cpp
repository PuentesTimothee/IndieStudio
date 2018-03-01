//
// Created by puentes on 31/05/17.
//

#include "Systems/Collision/OgreMotionState.hpp"

Gauntlet::OgreMotionState::OgreMotionState(btTransform const &defaultPos,
					   Ogre::SceneNode *node,
					   Ogre::Vector3 const & offset)
	: _node(node),
	  _offset(offset),
	  _defaultPos(defaultPos)
{

}

void		Gauntlet::OgreMotionState::getWorldTransform(btTransform &worldTrans) const
{
  worldTrans = this->_defaultPos;
}

void		Gauntlet::OgreMotionState::setWorldTransform(const btTransform &worldTrans)
{
  this->_defaultPos = worldTrans;

  if (this->_node == nullptr)
    return;

  this->_node->setOrientation(BulletToOgre::convert(worldTrans.getRotation()));
  this->_node->setPosition(BulletToOgre::convert(worldTrans.getOrigin()) - this->_offset);
}