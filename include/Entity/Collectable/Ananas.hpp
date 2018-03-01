//
// Created by mymy on 09/06/17.
//

#ifndef INDIE_ANANAS_HPP
#define INDIE_ANANAS_HPP

#include "Entity/Entity.hpp"
#include <Components/Model.hpp>
#include <Components/Stats.hpp>
#include <Components/Animation.hpp>
#include <Components/PowerUpStats.hpp>

namespace Gauntlet
{
  class Ananas : public Entity
  {
   public:
    Ananas(int id);
    ~Ananas() {};
  };
}

#endif //INDIE_ANANAS_HPP
