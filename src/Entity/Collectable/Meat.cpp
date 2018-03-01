//
// Created by mymy on 03/06/17.
//

#include <Components/Sound.hpp>
#include "Entity/Collectable/Meat.hpp"

Gauntlet::Meat::Meat(int id) :
	Entity(Gauntlet::Entity::Type::POWERUP, id)

{
  std::string                   nameEntity = "meat" + std::to_string(id);
  Ogre::Vector3			hitbox(1, 0.5, 1);
  Gauntlet::Model		*model = new Gauntlet::GhostModel("food1.mesh",
								   nameEntity,
								   hitbox,
								   false);
  Gauntlet::State		*state = new Gauntlet::State();
  Gauntlet::PowerUpStats        *powerUpStats = new Gauntlet::PowerUpStats(Gauntlet::PowerUpStats::Type::HEALTH, 25);
  Gauntlet::Animation		*animation = new Gauntlet::Animation(model->ent);

  auto death = "../audio/sfx/object/meat_pickup.wav";
  auto move = " ";
  auto attack = " ";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(death, move, attack);

  model->node->setPosition(-20, 3, -20);
  model->body->setPosition(Ogre::Vector3(-20, 3, -20));
  state->type = Gauntlet::State::Type::IDLE;
  this->attach<Gauntlet::State>(state);
  this->attach<Gauntlet::PowerUpStats>(powerUpStats);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  this->attach<Gauntlet::Sound>(sound);
}