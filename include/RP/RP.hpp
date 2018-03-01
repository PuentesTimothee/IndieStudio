//
// Created by mymy on 25/05/17.
//

#ifndef INDIE_RP_HPP
#define INDIE_RP_HPP

#include <Systems/System.hpp>
#include <Components/EntityState.hpp>
#include <Components/Model.hpp>
#include "Components/Stats.hpp"
#include <Components/PowerUpStats.hpp>

namespace Gauntlet
{
    class RP : public Gauntlet::System
    {
      int nbLevel;

      void handleAttack(Event const &) const;
      void handleMove(Event const &) const;
      void handleDash(Event const &) const;
      void handleCollision(Event const &) const;
      void handleIdle(Event const &) const;
      void handlePowerUp(Event const &) const;
      void handleRevive(Event const &) const;
      void fightEngaged(Event const &) const;
      bool isEnnemy(Entity::Type const &, Entity::Type const &) const;

      bool checkDefeat(std::vector<std::shared_ptr<Entity>> const &);
      void checkVictory(std::vector<std::shared_ptr<Entity>> const &);

     public:
      RP() : nbLevel(0)
      {};

      virtual ~RP()
      {};

      void checkGameState(std::vector<std::shared_ptr<Entity>>	const &);
      virtual void takeEvent(Event const &) override;
    };
}

#endif //INDIE_RP_HPP
