
//
// Created by mymy on 09/06/17.
//

#include "Entity/Collectable/Ananas.hpp"
#include <Components/Sound.hpp>

Gauntlet::Ananas::Ananas(int id) :
	Entity(Gauntlet::Entity::Type::POWERUP, id)

{
  std::string                   nameEntity = "ananas" + std::to_string(id);
  Ogre::Vector3			hitbox(1, 0.5, 1);
  Gauntlet::Model		*model = new Gauntlet::GhostModel("food4.mesh",
								   nameEntity,
								   hitbox,
								   false);
  Gauntlet::State		*state = new Gauntlet::State();
  Gauntlet::PowerUpStats        *powerUpStats = new Gauntlet::PowerUpStats(Gauntlet::PowerUpStats::Type::STAMINA_MAX, 5);
  Gauntlet::Animation		*animation = new Gauntlet::Animation(model->ent);

  auto death = "../audio/sfx/object/meat_drop.wav";
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