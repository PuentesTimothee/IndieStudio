//
// Created by mymy on 12/06/17.
//

#ifndef INDIE_BOSS_HPP
#define INDIE_BOSS_HPP

#include "Entity/Entity.hpp"
#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/Animation.hpp"
#include "Components/Stats.hpp"
#include "Components/EntityState.hpp"
#include "Components/Weapon.hpp"

namespace Gauntlet
{
  class Boss : public Entity
  {
   public:
    Boss(int id);
    ~Boss() {};
  };
}

#endif //INDIE_BOSS_HPP
