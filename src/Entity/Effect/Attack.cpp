//
// Created by puentes on 01/06/17.
//

#include "Entity/Effect/Attack.hpp"

Gauntlet::Attack::Attack(int id, std::string const &modelName)
	: Entity(Entity::Type::DEFAULT, id)
{
  std::string nameEnt = "attack" + std::to_string(id);

  Ogre::Vector3			hitbox(1, 0.5, 1);
  Gauntlet::Model		*model = new Gauntlet::GhostModel(modelName,
								   nameEnt,
								   hitbox,
								   false);
  Gauntlet::Stats		*stats = new Gauntlet::Stats(1, 1, 1);
  Gauntlet::State		*state = new Gauntlet::State();

  state->type = Gauntlet::State::Type::ATTACK;

  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Stats>(stats);
  this->attach<Gauntlet::State>(state);
}