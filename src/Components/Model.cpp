//
// Created by puentes on 19/05/17.
//

#include "Components/Model.hpp"
#include "CoreGame.hpp"

Ogre::Vector3		Gauntlet::Model::DEFAULT_HITBOX_SIZE(2, 5, 2);

Gauntlet::Model::Model(Ogre::SceneNode *nnode,
		       Ogre::Entity *nent,
		       Gauntlet::CollisionObject *nbody)
	: node(nnode),
	  ent(nent),
	  body(nbody),
	  dirVec(Ogre::Vector3::UNIT_X)
{
}

Gauntlet::Model::Model(std::string const	&modelName,
		       std::string const	&entityName,
		       Ogre::Vector3 const	&hitbox,
		       bool			isStatic,
		       std::string const	&matName)
	:  node(Gauntlet::CoreGame::core->getDisplayer().createEntity(modelName,
								      entityName,
								      matName)),
	   ent(Gauntlet::CoreGame::core->getDisplayer().getSceneManager()->getEntity(entityName)),
	   body(Gauntlet::CoreGame::core->getCollisionMgr().addBox(this->node,
								   hitbox,
								   isStatic)),
	   dirVec(Ogre::Vector3::UNIT_X)
{
}

Gauntlet::PlaneModel::PlaneModel(std::string const &	modelName,
				 std::string const &	entityName,
				 Ogre::Vector3 const &	normal,
				 bool			isStatic,
				 std::string const &	matName)
	:  Model(Gauntlet::CoreGame::core->getDisplayer().createEntity(modelName,
								       entityName,
								       matName),
		 nullptr,
		 nullptr)
{
  this->ent = Gauntlet::CoreGame::core->getDisplayer().getSceneManager()->getEntity(entityName);
  this->body = Gauntlet::CoreGame::core->getCollisionMgr().addPlane(this->node,
								    normal,
								    isStatic);
}

Gauntlet::GhostModel::GhostModel(std::string const	&modelName,
				 std::string const	&entityName,
				 Ogre::Vector3 const	&hitboxSize,
				 bool			,
				 const std::string	&/*matName*/)
	:  Model(Gauntlet::CoreGame::core->getDisplayer().createEntity(modelName, entityName,
								       "", false),
		 nullptr,
		 nullptr)
{
  this->ent = Gauntlet::CoreGame::core->getDisplayer().getSceneManager()->getEntity(entityName);
  this->body = Gauntlet::CoreGame::core->getCollisionMgr().addHitBox(this->node,
								     hitboxSize,
								     Ogre::Vector3::ZERO,
								     Ogre::Quaternion::IDENTITY);
}

Gauntlet::GhostModel::~GhostModel()
{}

Gauntlet::PlaneModel::~PlaneModel()
{}

Gauntlet::Model::~Model()
{
  Gauntlet::CoreGame::core->getCollisionMgr().deleteBody(this->body);
  Gauntlet::CoreGame::core->getDisplayer().deleteEntity(this->node, this->ent);
}

Ogre::Quaternion	Gauntlet::Model::getDiretion() const
{
  Ogre::Quaternion	quaternion(Ogre::Math::ACos(this->dirVec.dotProduct(Ogre::Vector3::UNIT_X))
				     * ((this->dirVec.z >= 0) ? (-1) : (1)),
				     Ogre::Vector3::UNIT_Y);
  return (quaternion);
}
