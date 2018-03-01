//
// Created by mymy on 09/06/17.
//

#ifndef INDIE_GHOST_HPP
#define INDIE_GHOST_HPP

#include <Entity/Entity.hpp>

namespace Gauntlet
{
  class Ghost : public Gauntlet::Entity
  {
   public:
    Ghost(int id);
    ~Ghost() {};
  };
}

#endif //INDIE_GHOST_HPP
