//
// Created by mymy on 13/06/17.
//

#include "Entity/Character/MiniBoss.hpp"
#include "CoreGame.hpp"
#include <Components/Sound.hpp>
#include <Components/AIScript.hpp>

Gauntlet::MiniBoss::MiniBoss(int id) :
	Entity(Gauntlet::Entity::Type::EVIL, id)
{
  Gauntlet::Model *model = new Gauntlet::Model("miniBoss.mesh",
					       "miniBoss" + std::to_string(id),
					       Ogre::Vector3(2, 5, 2));
  Gauntlet::State *entState = new Gauntlet::State();
  Gauntlet::Weapon *weapon = new Gauntlet::Weapon(10, 1, Weapon::Type::CAC);
  Gauntlet::Stats *stat = new Gauntlet::Stats(80, 80, 1.5, 1, 1);

  Gauntlet::Animation *animation = new Gauntlet::Animation(model->ent);

  auto death = " ";
  auto move = " ";
  auto attack = " ";
  Gauntlet::Sound *sound = new Gauntlet::Sound(death, move, attack);

  this->attach<Gauntlet::Weapon>(weapon);
  this->attach<Gauntlet::State>(entState);
  this->attach<Gauntlet::Stats>(stat);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  this->attach<Gauntlet::Sound>(sound);
  this->attach<Gauntlet::IAIScript>(new Gauntlet::GhostScript);
  Gauntlet::CoreGame::core->getMovementMgr().addEntity(this);
}