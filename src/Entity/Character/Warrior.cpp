//
// Created by puentes on 22/05/17.
//

#include "Entity/Character/Warrior.hpp"
#include "Components/AIScript.hpp"
#include "CoreGame.hpp"
#include <Components/Sound.hpp>

Gauntlet::Warrior::Warrior(int id) : Hero(id)
{
  Gauntlet::Model		*model = new Gauntlet::Model("warrior.mesh",
							      "warrior",
							      Ogre::Vector3(2, 5, 2));
  Gauntlet::State		*state = new Gauntlet::State();
  Gauntlet::Weapon              *weapon = new Gauntlet::Weapon(60, 1,
							       Weapon::Type::CAC,
							       Ogre::Vector3(5, 1, 15),
							       Ogre::Vector3(5, 1, -15));
  Gauntlet::Stats		*stat = new Gauntlet::Stats(300, 300, 1.5);
  Gauntlet::Animation		*animation = new Gauntlet::Animation(model->ent);

  auto death = "../audio/sfx/player//guerrier/hmm.wav";
  auto move = " ";
  auto attack = "../audio/sfx/player//guerrier/sword.wav";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(death, move, attack);

  this->attach<Gauntlet::Weapon>(weapon);
  this->attach<Gauntlet::Stats>(stat);
  this->attach<Gauntlet::State>(state);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  this->attach<Gauntlet::Sound>(sound);
  Gauntlet::CoreGame::core->getMovementMgr().addEntity(this);
}

void    Gauntlet::Warrior::becomeAI(std::vector<std::shared_ptr<Gauntlet::Entity>> const &a)
{
    this->attach<Gauntlet::IAIScript>(new Gauntlet::ValkyrieScript(a));
}