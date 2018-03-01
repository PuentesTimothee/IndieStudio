//
// Created by puentes on 06/06/17.
//

#ifndef INDIE_HEALATTACK_HPP
#define INDIE_HEALATTACK_HPP

#include "Entity/Effect/Attack.hpp"

namespace Gauntlet
{
  class HealAttack: public Attack
  {
   public:
    HealAttack(int id);

    virtual ~HealAttack()
    {

    };
  };
}

#endif //INDIE_HEALATTACK_HPP
