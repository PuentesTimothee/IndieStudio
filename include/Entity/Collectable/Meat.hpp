//
// Created by mymy on 03/06/17.
//

#ifndef INDIE_MEAT_HPP
#define INDIE_MEAT_HPP

#include "Entity/Entity.hpp"
#include <Components/Model.hpp>
#include <Components/Weapon.hpp>
#include <Components/Stats.hpp>
#include <Components/Animation.hpp>
#include <Components/PowerUpStats.hpp>


namespace Gauntlet
{
  class Meat : public Entity
  {
   public:
    Meat(int id);
    virtual ~Meat() {};
  };
}

#endif //INDIE_MEAT_HPP
