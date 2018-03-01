//
// Priest.cpp for GAUNTLET in /home/mymy/Modules/C++/cpp_indie_studio/src/Entity
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May 23 15:52:35 2017 Mymy Aragon
// Last update Wed Jun  7 14:15:33 2017 Benito
//

#include <Components/Sound.hpp>
#include <Components/AIScript.hpp>
#include "Entity/Character/Valkyrie.hpp"
#include "CoreGame.hpp"

Gauntlet::Valkyrie::Valkyrie(int id) : Hero(id)
{
  Gauntlet::Model		*model = new Gauntlet::Model("valkyrie.mesh",
							      "valkyrie",
							      Ogre::Vector3(2, 5, 2));
  Gauntlet::State		*state = new Gauntlet::State();

  auto d = "../audio/sfx/player//valkyrie/gethit1.wav";
  auto m = " ";
  auto a = "../audio/sfx/knife/knife_slash1.wav";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(d, m, a);


  Gauntlet::Weapon              *weapon = new Gauntlet::Weapon(50, 1.5, Weapon::Type::CAC,
                                                               Ogre::Vector3(5, 1, 0),
                                                               Ogre::Vector3(15, 1, 0));
  Gauntlet::Stats		        *stat = new Gauntlet::Stats(120, 120, 2);
  Gauntlet::Animation		    *animation = new Gauntlet::Animation(model->ent);

  this->attach<Gauntlet::Weapon>(weapon);
  this->attach<Gauntlet::Stats>(stat);
  this->attach<Gauntlet::State>(state);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  this->attach<Gauntlet::Sound>(sound);
  Gauntlet::CoreGame::core->getMovementMgr().addEntity(this);
}

void    Gauntlet::Valkyrie::becomeAI(std::vector<std::shared_ptr<Gauntlet::Entity>> const &a)
{
  this->attach<Gauntlet::IAIScript>(new Gauntlet::ValkyrieScript(a));
}