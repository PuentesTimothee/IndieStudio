//
// Created by puentes on 09/06/17.
//

#include "CoreGame.hpp"
#include "Components/LightSource.hpp"

Gauntlet::LightSource::LightSource(Ogre::SceneNode *node,
				   const Ogre::Vector3 &offset,
				   Ogre::ColourValue const & colorS,
				   Ogre::ColourValue const & colorD,
				   float power)
	: lightNode(nullptr),
	  light(nullptr)
{
  this->lightNode = Gauntlet::CoreGame::core->getDisplayer().createLight(node, offset,
									 colorD,
									 colorS,
									 power,
									 this->light);
}

Gauntlet::LightSource::~LightSource()
{
  Gauntlet::CoreGame::core->getDisplayer().deleteLight(this->lightNode, this->light);
}
