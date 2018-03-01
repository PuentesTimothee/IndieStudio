//
// Created by mymy on 07/06/17.
//

#ifndef INDIE_DONUTS_HPP
#define INDIE_DONUTS_HPP

#include "Entity/Entity.hpp"
#include <Components/Model.hpp>
#include <Components/Weapon.hpp>
#include <Components/Stats.hpp>
#include <Components/Animation.hpp>
#include <Components/PowerUpStats.hpp>

namespace Gauntlet
{
  class Donuts : public Entity
  {
   public:
    Donuts(int id);
    ~Donuts() {};
  };
}

#endif //INDIE_DONUTS_HPP
