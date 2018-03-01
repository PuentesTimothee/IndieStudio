//
// Created by mymy on 01/06/17.
//

#ifndef INDIE_ATTACKMANAGER_HPP
#define INDIE_ATTACKMANAGER_HPP

#include <Ogre.h>
#include <OgreMath.h>

#include <Systems/System.hpp>

#include "Components/Weapon.hpp"
#include "Entity/Effect/Attack.hpp"
#include "Entity/Effect/CaCAttack.hpp"
#include "Entity/Effect/DistAttack.hpp"
#include "Entity/Effect/HealAttack.hpp"
#include "Entity/Effect/ZoneDistAttack.hpp"
#include "CustomMath.hpp"

namespace Gauntlet
{
  struct AttackData
  {
   public:
    AttackData(std::shared_ptr<Gauntlet::Entity> const &paramAttac,
	       Gauntlet::Weapon *paramAttackWeapon,
	       std::shared_ptr<Gauntlet::Entity> const& paramAttacker);

    std::shared_ptr<Gauntlet::Entity>	attack;
    Gauntlet::Weapon			*attackWeapon;
    std::shared_ptr<Gauntlet::Entity>	attacker;
    float				perc;
  };

  class AttackManager : public Gauntlet::System
  {
   private:
    std::vector<Gauntlet::AttackData> _attacks;

    void	generateAttack(std::shared_ptr<Gauntlet::Entity> const&);

   public:
    AttackManager() {};
    ~AttackManager() {};

    void	updateTrajectorys();
    void	takeEvent(Gauntlet::Event const &evt);
    void	destroyEnt(Gauntlet::Entity *ent);
    void	destroyAllEntity();
  };
}

#include "Factory/Factory.hpp"

#endif //INDIE_ATTACKMANAGER_HPP
