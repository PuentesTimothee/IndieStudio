//
// Created by puentes on 18/05/17.
//

#ifndef INDIE_ANIMATION_HPP
#define INDIE_ANIMATION_HPP

#include <Ogre.h>

#include "Components.hpp"
#include "Components/Model.hpp"

#include "Systems/Animation/AnimationManager.hpp"

namespace Gauntlet
{
  struct Animation : public IComponent
  {
    Ogre::Entity	*ent;

    std::string		actualAnim;
    std::string		entName;

      bool		on;
      bool 		loop;
      double    speed;

    Animation() = default;
    Animation(Ogre::Entity *entity);

    virtual ~Animation();

    void			setAnimation(std::string name,
					     bool repeat = true, double speed = 1);
    Ogre::AnimationState	*getState() const;
  };
};

#endif //INDIE_ANIMATION_HPP
