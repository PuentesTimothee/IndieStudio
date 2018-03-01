//
// Priest.cpp for GAUNTLET in /home/mymy/Modules/C++/cpp_indie_studio/src/Entity
// 
// Made by Mymy Aragon
// Login   <Gauntlet::my-lan.aragon@epitech.eu>
// 
// Started on  Tue May 23 15:52:35 2017 Mymy Aragon
// Last update Tue May 23 17:45:14 2017 Mymy Aragon
//

#include "Entity/Character/Priest.hpp"
#include "Components/AIScript.hpp"
#include "CoreGame.hpp"
#include <Components/Sound.hpp>

Gauntlet::Priest::Priest(int id) : Hero(id)
{
  Gauntlet::Model		*model = new Gauntlet::Model("priest.mesh",
							      "priest",
							      Ogre::Vector3(2, 5, 2));
  Gauntlet::State		*state = new Gauntlet::State();
  Gauntlet::Weapon              *weapon = new Gauntlet::Weapon(30, 1.5, Weapon::Type::HEAL,
							       Ogre::Vector3(5, 1, 0),
							       Ogre::Vector3(25, 1, 0));
  Gauntlet::Stats		*stat = new Gauntlet::Stats(85, 85, 2);
  Gauntlet::Animation		*animation = new Gauntlet::Animation(model->ent);

  auto death = "../audio/sfx/player//pretre/death2.wav";
  auto move = " ";
  auto attack = " ";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(death, move, attack);

  this->attach<Gauntlet::Weapon>(weapon);
  this->attach<Gauntlet::Stats>(stat);
  this->attach<Gauntlet::State>(state);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  Gauntlet::CoreGame::core->getMovementMgr().addEntity(this);
  this->attach<Gauntlet::Sound>(sound);
}

void    Gauntlet::Priest::becomeAI(std::vector<std::shared_ptr<Gauntlet::Entity>> const &a)
{
    this->attach<Gauntlet::IAIScript>(new Gauntlet::PriestScript(a));
}