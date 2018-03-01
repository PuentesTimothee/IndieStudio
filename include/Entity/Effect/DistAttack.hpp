//
// Created by puentes on 06/06/17.
//

#ifndef INDIE_DISTATTACK_HPP
#define INDIE_DISTATTACK_HPP

#include "Entity/Effect/Attack.hpp"

namespace Gauntlet
{
  class DistAttack: public Attack
  {
   public:
    DistAttack(int id);

    virtual ~DistAttack()
    {

    };
  };
}

#endif //INDIE_DISTATTACK_HPP
