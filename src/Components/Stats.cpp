//
// Created by puentes on 25/05/17.
//

#include "Components/Stats.hpp"


Gauntlet::Stats::Stats(int l, int lM, double m, int stamina, int staminaMax)
	: life(l),
	  lifeMax(lM),
	  moveSpeed(m),
	  stamina(stamina),
	  staminaMax(staminaMax)
{

}

bool		Gauntlet::Stats::add(int heal)
{
  if (this->life == this->lifeMax)
    return (false);

  this->life += heal;
  if (this->life > this->lifeMax)
    this->life = this->lifeMax;
  return (true);
}

bool		Gauntlet::Stats::sub(int damage)
{
  if (this->life <= 0)
    return (false);

  this->life -= damage;
  if (this->life < 0)
    {
      this->life = 0;
      return (false);
    }
  return (true);
}
