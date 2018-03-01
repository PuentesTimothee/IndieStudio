//
// Created by puentes on 18/05/17.
//

#ifndef INDIE_MODEL_HPP
#define INDIE_MODEL_HPP

#include <Ogre.h>

#include "Systems/Displayer/Displayer.hpp"
#include "Systems/Collision/CollisionManager.hpp"

namespace Gauntlet
{
  struct Model : public IComponent
  {
    Ogre::SceneNode				*node;
    Ogre::Entity				*ent;
    Gauntlet::CollisionObject			*body;

    Ogre::Vector3				dirVec;

    Model() = default;

    Model(Ogre::SceneNode *node,
	  Ogre::Entity *ent,
	  Gauntlet::CollisionObject *body);
    Model(std::string const	&modelName,
	  std::string const	&entityName,
	  Ogre::Vector3 const	&hitboxSize = Gauntlet::Model::DEFAULT_HITBOX_SIZE,
	  bool			isStatic = false,
	  std::string const	&matName = "");

    Ogre::Quaternion	getDiretion() const;

    virtual ~Model();

    static Ogre::Vector3		DEFAULT_HITBOX_SIZE;
  };

  struct PlaneModel : public Model
  {
    PlaneModel() = default;

    PlaneModel(std::string const &modelName,
	       std::string const &entityName,
	       Ogre::Vector3 const & normal,
	       bool isStatic = false,
	       std::string const &matName = "");

    virtual ~PlaneModel();
  };

  struct GhostModel : public Model
  {
    GhostModel() = default;


    GhostModel(std::string const	&modelName,
	       std::string const	&entityName,
	       Ogre::Vector3 const	&hitboxSize = Gauntlet::Model::DEFAULT_HITBOX_SIZE,
	       bool			isStatic = false,
	       std::string const	&matName = "");

    virtual ~GhostModel();
  };
};

#endif //INDIE_MODEL_HPP
