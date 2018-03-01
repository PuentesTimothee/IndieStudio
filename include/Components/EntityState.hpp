//
// Created by puentes on 22/05/17.
//

#ifndef INDIE_GAMELOGIC_HPP
#define INDIE_GAMELOGIC_HPP

#include <Ogre.h>

#include "Components.hpp"

namespace Gauntlet
{
  struct State : public IComponent
  {
    enum class Type
    {
      DEFAULT,
      ATTACK,
      IDLE,
      MOVING,
      DASH,
      DEAD
    };

    Type	type;

    State();
  };
}

#endif //INDIE_GAMELOGIC_HPP
