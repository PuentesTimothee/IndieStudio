//
// Created by puentes on 14/06/17.
//

#include "Entity/Destroyable/Vase.hpp"
#include "CoreGame.hpp"

Gauntlet::Vase::Vase(int id) :
	Entity(Entity::Type::DESTROYABLE, id)
{
  Gauntlet::Model		*model = new Gauntlet::Model("vase.mesh",
							      "Vase" + std::to_string(id),
							      Ogre::Vector3(2, 10, 2));
  Gauntlet::State		*entState = new Gauntlet::State();
  Gauntlet::Stats		*stat = new Gauntlet::Stats(20, 20, 0);

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