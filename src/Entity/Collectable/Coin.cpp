//
// Created by mymy on 05/06/17.
//

#include "Entity/Collectable/Coin.hpp"
#include <Components/Sound.hpp>

Gauntlet::Coin::Coin(int id) :
	Entity(Gauntlet::Entity::Type::POWERUP, id)

{
  std::string                   nameEntity = "coin" + std::to_string(id);
  Ogre::Vector3			hitbox(1, 0.5, 1);
  Gauntlet::Model		*model = new Gauntlet::GhostModel("coin.mesh",
								   nameEntity,
								   hitbox,
								   false);
  Gauntlet::State		*state = new Gauntlet::State();
  Gauntlet::PowerUpStats        *powerUpStats = new Gauntlet::PowerUpStats(Gauntlet::PowerUpStats::Type::SCORE, 10);
  Gauntlet::Animation		*animation = new Gauntlet::Animation(model->ent);

  auto death = "../audio/sfx/object/gold_drop.wav";
  auto move = " ";
  auto attack = " ";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(death, move, attack);

  state->type = Gauntlet::State::Type::IDLE;
  this->attach<Gauntlet::State>(state);
  this->attach<Gauntlet::PowerUpStats>(powerUpStats);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  this->attach<Gauntlet::Sound>(sound);
}