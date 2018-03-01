//
// Created by puentes on 01/06/17.
//

#ifndef INDIE_ATTACK_HPP
#define INDIE_ATTACK_HPP

#include "Entity/Entity.hpp"

#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/Animation.hpp"
#include "Components/EntityState.hpp"
#include <Components/Stats.hpp>

namespace Gauntlet
{
  class Attack : public Gauntlet::Entity
  {
   protected:
    Attack(int id,
	   std::string const &modelName);
   public:
    virtual ~Attack()
    {
    };
  };
}

#endif //INDIE_ATTACK_HPP
