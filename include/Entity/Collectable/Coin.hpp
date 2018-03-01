//
// Created by mymy on 05/06/17.
//

#ifndef INDIE_COIN_HPP
#define INDIE_COIN_HPP

#include "Entity/Entity.hpp"
#include <Components/Model.hpp>
#include <Components/Weapon.hpp>
#include <Components/Stats.hpp>
#include <Components/Animation.hpp>
#include <Components/PowerUpStats.hpp>

namespace Gauntlet
{
  class Coin : public Entity
  {
   public:
    Coin(int id);
    ~Coin() {};
  };
}

#endif //INDIE_COIN_HPP
