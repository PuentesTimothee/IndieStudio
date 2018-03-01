//
// Created by mymy on 12/06/17.
//

#include "Entity/Character/Boss.hpp"

#include "CoreGame.hpp"
#include <Components/Sound.hpp>
#include <Components/AIScript.hpp>

Gauntlet::Boss::Boss(int id) :
	Entity(Entity::Type::EVIL, id)
{
  Gauntlet::Model		*model = new Gauntlet::Model("boss.mesh",
							      "boss" + std::to_string(id),
							      Ogre::Vector3(2, 5, 2));
  Gauntlet::State		*state = new Gauntlet::State();
  Gauntlet::Weapon              *weapon = new Gauntlet::Weapon(80, 1.5, Weapon::Type::ZONE_DIST,
							       Ogre::Vector3(5, 1, 5),
							       Ogre::Vector3(35, 1, 35));
  Gauntlet::Stats		*stat = new Gauntlet::Stats(1000, 1000, 1.5);
  Gauntlet::Animation		*animation = new Gauntlet::Animation(model->ent);

  auto death = "../audio/sfx/boss//dinosaur/trex.ogg";
  auto move = "";
  auto attack = "";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(death, move, attack);

  this->attach<Gauntlet::Weapon>(weapon);
  this->attach<Gauntlet::Stats>(stat);
  this->attach<Gauntlet::State>(state);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  Gauntlet::CoreGame::core->getMovementMgr().addEntity(this);
  this->attach<Gauntlet::IAIScript>(new Gauntlet::BossScript);
  this->attach<Gauntlet::Sound>(sound);
}