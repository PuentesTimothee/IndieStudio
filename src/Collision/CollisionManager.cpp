//
// Created by puentes on 26/05/17.
//

#include <CoreGame.hpp>

#include "Systems/Collision/CollisionManager.hpp"

Gauntlet::CollisionManager::CollisionManager(Ogre::SceneManager	*sceneMgr)
	: _broadphase(nullptr),
	  _collisionConfiguration(nullptr),
	  _dispatcher(nullptr),
	  _solver(nullptr),
	  _world(nullptr),
	  _objects(),
	  _sceneMgr(sceneMgr)
{
  this->_broadphase.reset(new btDbvtBroadphase());
  this->_collisionConfiguration.reset(new btDefaultCollisionConfiguration());
  this->_dispatcher.reset(new btCollisionDispatcher(this->_collisionConfiguration.get()));
  this->_solver.reset(new btSequentialImpulseConstraintSolver);

  btGImpactCollisionAlgorithm::registerAlgorithm(this->_dispatcher.get());

  this->_world.reset(new btDiscreteDynamicsWorld(this->_dispatcher.get(),
					     this->_broadphase.get(),
					     this->_solver.get(),
					     this->_collisionConfiguration.get()));

  this->_world->setGravity(btVector3(0, -9.81, 0));
  gContactAddedCallback = ContactAddedCallBack;
}

Gauntlet::CollisionManager::~CollisionManager()
{
  for (auto &object : this->_objects)
    object.obj.reset();

  this->_world.reset();
  this->_solver.reset();
  this->_dispatcher.reset();
  this->_collisionConfiguration.reset();
  this->_broadphase.reset();
}

void				Gauntlet::CollisionManager::updateSimulation()
{
  this->_world->stepSimulation(Gauntlet::CoreGame::frameRate);
}

Gauntlet::CollisionBody		*Gauntlet::CollisionManager::addPlane(Ogre::SceneNode			*node,
									     Ogre::Vector3 const &	normal,
									     bool			isStatic)
{
  std::shared_ptr<btCollisionShape>	shape(new btStaticPlaneShape(OgreToBullet::convert(normal), 0));
  Gauntlet::CollisionBody		*object = new Gauntlet::CollisionBody(shape,
									       (isStatic) ? (0) : (70),
									       node,
									       this->_world);
  return (object);
}

Gauntlet::CollisionBody		*Gauntlet::CollisionManager::addBox(Ogre::SceneNode			*node,
									   Ogre::Vector3 const &	size,
									   bool				isStatic)
{
  Ogre::Vector3				offset(0, size.y, 0);
  std::shared_ptr<btCollisionShape>	shape(new btBoxShape(OgreToBullet::convert(size)));
  Gauntlet::CollisionBody		*object = new Gauntlet::CollisionBody(shape,
									       ((isStatic) ? (0) : (70)),
									       node,
									       this->_world,
									       offset);

  this->_objects.emplace_back(object);
  return (object);
}

Gauntlet::HitBox			*Gauntlet::CollisionManager::addHitBox(Ogre::SceneNode *node,
									       Ogre::Vector3 const	&size,
										Ogre::Vector3 const	&at,
										Ogre::Quaternion const	&rot)
{
  btTransform				trans(OgreToBullet::convert(rot),
						   OgreToBullet::convert(at));

  std::shared_ptr<btCollisionShape>	shape(new btBoxShape(OgreToBullet::convert(size)));

  Ogre::Vector3				offset(0, size.y / 2, 0);

  Gauntlet::HitBox			*object = new Gauntlet::HitBox(shape,
									 node,
									 offset,
									 this->_world);

  this->_objects.emplace_back(object);
  return (object);
}

void 					Gauntlet::CollisionManager::getCollision() const
{
  for (auto & obj : this->_objects)
    obj.obj->getEvent();
}

void					Gauntlet::CollisionManager::deleteBody(Gauntlet::CollisionObject *obj)
{
     * this->_objects.erase(std::remove_if(this->_objects.begin(), this->_objects.end(),
                                        [obj](Gauntlet::CollisionData const &object) {
                                            return (obj == object.obj.get());
                                        }),
                         this->_objects.end());
}

bool					Gauntlet::CollisionManager::addToListOfHit(btCollisionObject const *obj,
										       int id)
{
   for (auto & object : this->_objects)
    {
      if (object.obj->getBtObj() == obj)
	{
	  if (std::find(object.hitId.begin(), object.hitId.end(), id) !=
	      object.hitId.end())
	      return (false);
	  object.hitId.push_back(id);
	  return (true);
	}
    }
  return (false);
}

Gauntlet::CollisionData::CollisionData(Gauntlet::CollisionObject *paramObj)
	: obj(paramObj),
	  hitId()
{

}
