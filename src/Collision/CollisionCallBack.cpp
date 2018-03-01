//
// Created by puentes on 30/05/17.
//

#include <Event/Event.hpp>
#include <Factory/Factory.hpp>
#include "Systems/Collision/CollisionCallBack.hpp"

Gauntlet::CollisionCallBack::CollisionCallBack(btRigidBody				*,
					       std::shared_ptr<btDynamicsWorld> const	&)
	: btCollisionWorld::ContactResultCallback(),
	  _body()
{
}

bool Gauntlet::CollisionCallBack::needsCollision(btBroadphaseProxy *proxy) const
{
  // superclass will check m_collisionFilterGroup and m_collisionFilterMask
  if (!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
    return (false);
  // if passed filters, may also want to avoid contacts between constraints
  return (this->_body->checkCollideWithOverride(static_cast<btCollisionObject *>(proxy->m_clientObject)));
}

btScalar		Gauntlet::CollisionCallBack::addSingleResult(btManifoldPoint			&cp,
								     const btCollisionObjectWrapper	*colObj0,
								     int				/*partId0*/,
								     int				/*index0*/,
								     const btCollisionObjectWrapper	*colObj1,
								     int				/*partId1*/,
								     int				/*index1*/)
{
  btVector3		pt;

  if (colObj0->m_collisionObject == this->_body)
    pt = cp.m_localPointA;
  else
    {
      if (colObj1->m_collisionObject != this->_body)
	return (0);
      pt = cp.m_localPointB;
    }

  return (0);
}

bool			Gauntlet::ContactAddedCallBack(btManifoldPoint& /*cp*/,
							   const btCollisionObjectWrapper* colObj0,
							   int /*partId0*/, int /*index0*/,
							   const btCollisionObjectWrapper* colObj1,
							   int /*partId1*/, int /*index1*/)
{
  std::shared_ptr<Gauntlet::Entity>		hitBox;
  std::shared_ptr<Gauntlet::Entity>		target;
  Gauntlet::Model		*model;

  for (auto const& entity : CoreGame::core->getEntities())
    {
      if ((model = entity->getPtr<Model>()))
    	{
    	  if (model->body != nullptr && model->body->getBtObj() == colObj0->getCollisionObject())
	        target = entity;
	      if (model->body != nullptr && model->body->getBtObj() == colObj1->getCollisionObject())
    	    hitBox = entity;
    	}
    }
  if (hitBox && target &&
	  Gauntlet::CoreGame::core->getCollisionMgr().addToListOfHit(colObj1->getCollisionObject(),
								     target->id))
    {
        Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::COLLISION, hitBox, target);
    }
  return (true);
}