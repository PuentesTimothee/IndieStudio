//
// Created by mymy on 05/06/17.
//

#include "Entity/Collectable/Icecream.hpp"
#include <Components/Sound.hpp>

Gauntlet::Icecream::Icecream(int id) :
	Entity(Gauntlet::Entity::Type::POWERUP, id)
{
  std::string                   entityName = "ice" + std::to_string(id);
  Ogre::Vector3			hitbox(1, 0.5, 1);
  Gauntlet::Model		*model = new Gauntlet::GhostModel("food0.mesh",
								   entityName,
								   hitbox,
								   false);
  Gauntlet::State		*state = new Gauntlet::State();
  Gauntlet::PowerUpStats        *powerUpStats = new Gauntlet::PowerUpStats(Gauntlet::PowerUpStats::Type::SPEED, 0.1);
  Gauntlet::Animation		*animation = new Gauntlet::Animation(model->ent);

  auto death = "../audio/sfx/object/ice_pickup.wav";
  auto move = " ";
  auto attack = " ";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(death, move, attack);

  model->node->setPosition(20, 3, -20);
  model->body->setPosition(Ogre::Vector3(20, 3, -20));
  state->type = Gauntlet::State::Type::IDLE;
  this->attach<Gauntlet::State>(state);
  this->attach<Gauntlet::PowerUpStats>(powerUpStats);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  this->attach<Gauntlet::Sound>(sound);
}