//
// Created by mymy on 03/06/17.
//

#ifndef INDIE_POWERUPSTATS_HPP
#define INDIE_POWERUPSTATS_HPP

#include "Components.hpp"

namespace Gauntlet
{
  struct PowerUpStats : public IComponent
  {
    enum class Type : int
    {
      HEALTH,
      SPEED,
      SCORE,
      HEALTH_MAX,
      STAMINA,
      STAMINA_MAX,
    };

    Type type;
    double amount;

    PowerUpStats(Type const &type, double amount);
  };
}

#endif //INDIE_POWERUPSTATS_HPP
