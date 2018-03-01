//
// Created by puentes on 25/05/17.
//

#ifndef INDIE_STATS_HPP
#define INDIE_STATS_HPP

#include <Ogre.h>

#include "Components.hpp"

namespace Gauntlet
{
  struct Stats : public IComponent
  {
    int		life;
    int		lifeMax;
    double	moveSpeed;
    int         stamina;
    int         staminaMax;

    Stats() = default;

    Stats(int l, int lM, double m, int stamina = 20, int staminaMax = 20);

    virtual ~Stats() {};

    bool	add(int);
    bool 	sub(int);
  };
};

#endif //INDIE_STATS_HPP
