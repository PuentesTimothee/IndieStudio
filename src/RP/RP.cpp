//
// Created by mymy on 25/05/17.
//


#include <CoreGame.hpp>
#include "RP/RP.hpp"

void    Gauntlet::RP::takeEvent(Event const &event)
{
  switch (event._type)
    {
      case (EventType::ATTACK) :
	this->handleAttack(event);
      break;
      case (EventType::DASH) :
	this->handleDash(event);
      break;
      case (EventType::MOVE) :
	this->handleMove(event);
      break;
      case (EventType::COLLISION) :
	this->handleCollision(event);
      break;
      case (EventType::IDLE) :
      this->handleIdle(event);
      break;
      case (EventType::ATTACK_END) :
	this->handleIdle(event);
      break;
      case (EventType::REVIVE) :
	this->handleRevive(event);
      break;
      case (EventType::LEVEL_END) :
	this->nbLevel += 1;
      default:
	break;
    }
}

void    Gauntlet::RP::handleAttack(Event const &event) const
{
  State *state;

  if (!event._entities.empty())
    {
      if ((state = event._entities[0]->getPtr<State>()))
	state->type = State::Type::ATTACK;
    }
}

void			Gauntlet::RP::handleDash(Event const &event) const
{
  State			*state;
  Stats                 *stats;

  if (!event._entities.empty())
    {
      if ((state = event._entities[0]->getPtr<State>())
	  && (stats = event._entities[0]->getPtr<Stats>()))
	{
	  if (stats->stamina >= 5)
	    {
	      state->type = State::Type::DASH;
	      stats->stamina -= 5;
	    }
	}
    }
}

void			Gauntlet::RP::handleMove(Event const &event) const
{
  State			*state;

  if (!event._entities.empty())
    {
      if ((state = event._entities[0]->getPtr<State>()))
	state->type = State::Type::MOVING;
    }
}

void			Gauntlet::RP::handleCollision(Event const &event) const
{
  Gauntlet::State       *state;

  if (event._entities.size() >= 2)
    {
      state = event._entities[0]->getPtr<Gauntlet::State>();
      if (state && state->type == State::Type::ATTACK)
	this->fightEngaged(event);
      else if (event._entities[0]->type == Entity::Type::POWERUP
	       && event._entities[1]->type == Entity::Type::HERO)
	  this->handlePowerUp(event);

    }
}

void                Gauntlet::RP::handlePowerUp(Event const &event) const
{
  Gauntlet::PowerUpStats *powerUpStats;
  Gauntlet::Stats        *statsPlayer;

  if (event._entities[1]->getPtr<Gauntlet::State>()->type == State::Type::DEAD)
    return;

  powerUpStats = event._entities[0]->getPtr<Gauntlet::PowerUpStats>();
  statsPlayer = event._entities[1]->getPtr<Gauntlet::Stats>();

  if (statsPlayer && powerUpStats && powerUpStats->type == PowerUpStats::Type::HEALTH)
    {
      statsPlayer->life += powerUpStats->amount;
      if (statsPlayer->life > statsPlayer->lifeMax)
	statsPlayer->life = statsPlayer->lifeMax;
    }
  else if (statsPlayer && powerUpStats && powerUpStats->type == PowerUpStats::Type::SPEED)
      statsPlayer->moveSpeed += powerUpStats->amount;
  else if (powerUpStats && powerUpStats->type == PowerUpStats::Type::SCORE)
	Gauntlet::CoreGame::score += powerUpStats->amount;
      else if (statsPlayer && powerUpStats && powerUpStats->type == PowerUpStats::Type::HEALTH_MAX)
	  {
	    statsPlayer->lifeMax += powerUpStats->amount;
	    statsPlayer->life = statsPlayer->lifeMax;
	  }
	else if (statsPlayer && powerUpStats && powerUpStats->type == PowerUpStats::Type::STAMINA)
	    {
	      statsPlayer->stamina += powerUpStats->amount;
	      if (statsPlayer->stamina > statsPlayer->staminaMax)
		statsPlayer->stamina = statsPlayer->staminaMax;
	    }
	  else if (statsPlayer && powerUpStats && powerUpStats->type == PowerUpStats::Type::STAMINA_MAX)
	      {
		statsPlayer->staminaMax += powerUpStats->amount;
		statsPlayer->stamina = statsPlayer->staminaMax;
	      }

  Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::DESTROY, event._entities[0]);
}

void		    Gauntlet::RP::handleIdle(Event const &event) const
{
  State *state;

  if (!event._entities.empty())
    {
      if ((state = event._entities[0]->getPtr<State>()))
	state->type = State::Type::IDLE;
    }
}

void                    Gauntlet::RP::handleRevive(Event const &event) const
{
  State *state;
  Stats *stats;

  if (!event._entities.empty())
    {
      state = event._entities[0]->getPtr<State>();
      stats = event._entities[0]->getPtr<Stats>();

      if (stats)
	stats->life = 10;
      if (state)
	state->type = State::Type::IDLE;
    }
}

void			Gauntlet::RP::fightEngaged(Event const &event) const
{
  Gauntlet::Stats	*statsTarget;
  Gauntlet::Weapon      *weapon;
  Gauntlet::State       *state;
  bool                  isDead;

  state = event._entities[1]->getPtr<State>();
  isDead = state->type == State::Type::DEAD;
  statsTarget = event._entities[1]->getPtr<Gauntlet::Stats>();
  weapon = event._entities[0]->getPtr<Gauntlet::Weapon>();
  if (statsTarget && weapon && event._entities[0]->type == Entity::Type::HEAL_ATTACK &&
	  event._entities[1]->type == Entity::Type::HERO)
    {
      if (isDead)
	{
	  Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::REVIVE, event._entities[1]);
	}
      else
	statsTarget->add(weapon->damage);
    }
  else if (statsTarget && weapon &&
	    this->isEnnemy(event._entities[0]->type, event._entities[1]->type))
      {
	if (!isDead && !statsTarget->sub(weapon->damage))
	  {
	    event._entities[1]->getPtr<Gauntlet::State>()->type = State::Type::DEAD;
	    Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::DESTROY,
					       event._entities[1]);
	  }
      }
}

bool    Gauntlet::RP::isEnnemy(Entity::Type const &attacker, Entity::Type const &attacked) const
{
  switch (attacked)
    {
      case (Entity::Type::HERO) :
	return (attacker == Entity::Type::EVIL_ATTACK);
      case (Entity::Type::DESTROYABLE) :
	return (attacker == Entity::Type::HERO_ATTACK || attacker == Entity::Type::HEAL_ATTACK);
      case (Entity::Type::EVIL):
	return (attacker == Entity::Type::HERO_ATTACK || attacker == Entity::Type::HEAL_ATTACK);
      default:
	return (false);
    }
}

void   Gauntlet::RP::checkGameState(std::vector<std::shared_ptr<Entity>> const &entities)
{
  if (!this->checkDefeat(entities))
    this->checkVictory(entities);
}

bool   Gauntlet::RP::checkDefeat(std::vector<std::shared_ptr<Entity>> const &entities)
{
  Gauntlet::State *state;
  unsigned int nb_hero = 0;
  unsigned int nb_dead_hero = 0;

  for (auto entity : entities)
    {
      if (entity.get()->type == Entity::Type::HERO)
	{
	  nb_hero += 1;
	  if ((state = entity.get()->getPtr<Gauntlet::State>()) && state->type == Gauntlet::State::Type::DEAD)
	      nb_dead_hero += 1;
	}
    }
  if (nb_dead_hero == nb_hero)
    {
      Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::DEFEAT);
      this->nbLevel = 0;
      return (true);
    }
  return (false);
}

void Gauntlet::RP::checkVictory(std::vector<std::shared_ptr<Entity>> const &entities)
{
  int nbEvilAlive = 0;

  if (static_cast<unsigned int>(this->nbLevel) == Gauntlet::CoreGame::core->levels)
    {
      for (auto entity : entities)
	{
	  if (entity.get()->type == Entity::Type::EVIL)
	    nbEvilAlive += 1;
	}

      if (nbEvilAlive == 0)
	{
	  Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::VICTORY);
	  this->nbLevel = 0;
	}
    }
}
