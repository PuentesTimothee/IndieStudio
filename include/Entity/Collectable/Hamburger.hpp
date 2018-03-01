//
// Created by mymy on 09/06/17.
//

#ifndef INDIE_HAMBURGER_HPP
#define INDIE_HAMBURGER_HPP

#include "Entity/Entity.hpp"
#include <Components/Model.hpp>
#include <Components/Stats.hpp>
#include <Components/Animation.hpp>
#include <Components/PowerUpStats.hpp>

namespace Gauntlet
{
  class Hamburger : public Entity
  {
   public:
    Hamburger(int id);
    ~Hamburger() {};
  };
}

#endif //INDIE_HAMBURGER_HPP
