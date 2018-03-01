//
// Created by mymy on 07/06/17.
//

#ifndef INDIE_CHESS_HPP
#define INDIE_CHESS_HPP

#include <Entity/Entity.hpp>
#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/EntityState.hpp"
#include "Components/Stats.hpp"

namespace Gauntlet
{
  class Chest : public Gauntlet::Entity
  {
   public:
    Chest(int id);
    ~Chest() {};
  };
}

#endif //INDIE_CHESS_HPP
