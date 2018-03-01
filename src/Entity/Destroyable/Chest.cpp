//
// Created by mymy on 07/06/17.
//

#include "Entity/Destroyable/Chest.hpp"
#include "CoreGame.hpp"
#include <Components/Sound.hpp>

Gauntlet::Chest::Chest(int id) :
	Entity(Entity::Type::DESTROYABLE, id)
{
  Gauntlet::Model		*model = new Gauntlet::Model("chest.mesh",
							      "chess" + std::to_string(id),
							      Ogre::Vector3(2, 10, 2));
  Gauntlet::State		*entState = new Gauntlet::State();
  Gauntlet::Stats		*stat = new Gauntlet::Stats(50, 50, 0);

  auto death = "../audio/sfx/cursor/select.wav";
  auto move = " ";
  auto attack = " ";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(death, move, attack);

  this->attach<Gauntlet::State>(entState);
  this->attach<Gauntlet::Stats>(stat);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Sound>(sound);
  Gauntlet::CoreGame::core->getMovementMgr().addEntity(this);
}