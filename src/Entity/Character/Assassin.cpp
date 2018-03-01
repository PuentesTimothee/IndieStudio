//
// Priest.cpp for GAUNTLET in /home/mymy/Modules/C++/cpp_indie_studio/src/Entity
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May 23 15:52:35 2017 Mymy Aragon
// Last update Tue May 23 17:44:34 2017 Mymy Aragon
//

#include "Entity/Character/Assassin.hpp"
#include "CoreGame.hpp"
#include <Components/Sound.hpp>
#include <Components/AIScript.hpp>

Gauntlet::Assassin::Assassin(int id) : Hero(id)
{
  Gauntlet::Model		*model = new Gauntlet::Model("assasin.mesh",
							      "assassin",
							      Ogre::Vector3(2, 5, 2));
  Gauntlet::State		*state = new Gauntlet::State();
  Gauntlet::Weapon              *weapon = new Gauntlet::Weapon(40, 2, Weapon::DIST,
							       Ogre::Vector3(5, 1, 0),
							       Ogre::Vector3(15, 1, 0));
  Gauntlet::Stats		*stat = new Gauntlet::Stats(100, 100, 2.5);
  Gauntlet::Animation		*animation = new Gauntlet::Animation(model->ent);

  auto death = "../audio/sfx/player//assassin/cri_mignon.wav";
  auto move = " ";
  auto attack = "../audio/sfx/player//assassin/lancer.wav";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(death, move, attack);

  this->attach<Gauntlet::Weapon>(weapon);
  this->attach<Gauntlet::Stats>(stat);
  this->attach<Gauntlet::State>(state);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  this->attach<Gauntlet::Sound>(sound);
  Gauntlet::CoreGame::core->getMovementMgr().addEntity(this);
}

void    Gauntlet::Assassin::becomeAI(std::vector<std::shared_ptr<Gauntlet::Entity>> const &a)
{
    this->attach<Gauntlet::IAIScript>(new Gauntlet::AssassinScript(a));
}