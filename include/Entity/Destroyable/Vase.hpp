//
// Created by puentes on 14/06/17.
//

#ifndef INDIE_VASE_HPP
#define INDIE_VASE_HPP

#include <Entity/Entity.hpp>
#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/EntityState.hpp"
#include "Components/Stats.hpp"
#include "Components/Sound.hpp"

namespace Gauntlet
{
  class Vase : public Gauntlet::Entity
  {
   public:
    Vase(int id);
    ~Vase() {};
  };
}

#endif //INDIE_VASE_HPP
