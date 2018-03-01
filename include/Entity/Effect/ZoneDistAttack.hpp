//
// Created by mymy on 12/06/17.
//

#ifndef INDIE_ZONEDISTATTACK_HPP
#define INDIE_ZONEDISTATTACK_HPP

#include "Entity/Effect/Attack.hpp"

namespace Gauntlet
{
  class ZoneDistAttack: public Attack
  {
   public:
    ZoneDistAttack(int id);

    virtual ~ZoneDistAttack()
    {

    };
  };
}

#endif //INDIE_ZONEDISTATTACK_HPP
