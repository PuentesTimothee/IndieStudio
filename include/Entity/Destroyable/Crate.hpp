//
// Created by puentes on 14/06/17.
//

#ifndef INDIE_CRATE_HPP
#define INDIE_CRATE_HPP

#include <Entity/Entity.hpp>
#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/EntityState.hpp"
#include "Components/Stats.hpp"
#include "Components/Sound.hpp"

namespace Gauntlet
{
  class Crate : public Gauntlet::Entity
  {
   public:
    Crate(int id);
    ~Crate() {};
  };
}

#endif //INDIE_CRATE_HPP
