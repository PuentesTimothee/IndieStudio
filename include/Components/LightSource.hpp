//
// Created by puentes on 09/06/17.
//

#ifndef INDIE_LIGHTSOURCE_HPP
#define INDIE_LIGHTSOURCE_HPP

#include <Ogre.h>
#include "Components.hpp"

namespace Gauntlet
{
  class LightSource : public IComponent
  {
   public:
    Ogre::SceneNode	*lightNode;
    Ogre::Light		*light;

    LightSource(Ogre::SceneNode	*node,
		Ogre::Vector3 const & offset = Ogre::Vector3::ZERO,
		Ogre::ColourValue const &colorD = Ogre::ColourValue::White,
		Ogre::ColourValue const &colorS = Ogre::ColourValue::White,
		float power = 1);

    virtual ~LightSource();
  };
}

#endif //INDIE_LIGHTSOURCE_HPP
