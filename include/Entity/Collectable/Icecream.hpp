//
// Created by mymy on 05/06/17.
//

#ifndef INDIE_ICECREAM_HPP
#define INDIE_ICECREAM_HPP

#include "Entity/Entity.hpp"
#include <Components/Model.hpp>
#include <Components/Weapon.hpp>
#include <Components/Stats.hpp>
#include <Components/Animation.hpp>
#include <Components/PowerUpStats.hpp>

namespace Gauntlet
{
  class Icecream : public Entity
  {
   public:
    Icecream(int id);
    ~Icecream() {};
  };
}

#endif //INDIE_ICECREAM_HPP
