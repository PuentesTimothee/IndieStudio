//
// Pig.cpp for indie in /home/benito/rendu/cpp/cpp_indie_studio
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Mon May 22 16:46:16 2017 benito
// Last update Fri May 26 18:03:06 2017 benito
//

#include <Components/AIScript.hpp>
#include <Components/Sound.hpp>
#include "Entity/Character/Pig.hpp"
#include "CoreGame.hpp"

std::string Gauntlet::Pig::modelName = "pig.mesh";
std::string Gauntlet::Pig::name = "pig";

Gauntlet::Pig::Pig(int id)
	: Entity(Entity::Type::EVIL, id)
{
  Gauntlet::Model		*model = new Gauntlet::Model(this->modelName,
							     this->name + std::to_string(id),
							      Ogre::Vector3(2, 5, 2));
  Gauntlet::State		*entState = new Gauntlet::State();
  Gauntlet::Weapon              *weapon = new Gauntlet::Weapon(5, 1, Weapon::Type::CAC);
  Gauntlet::Stats		*stat = new Gauntlet::Stats(110, 110, 1, 0, 0);

  Gauntlet::Animation		*animation = new Gauntlet::Animation(model->ent);

  auto death = "../audio/sfx/pig/pig-1.wav";
  auto move = " ";
  auto attack = " ";
  Gauntlet::Sound       *sound = new Gauntlet::Sound(death, move, attack);

  this->attach<Gauntlet::Weapon>(weapon);
  this->attach<Gauntlet::State>(entState);
  this->attach<Gauntlet::Stats>(stat);
  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::Animation>(animation);
  this->attach<Gauntlet::Sound>(sound);
  this->attach<Gauntlet::IAIScript>(new Gauntlet::PigScript);
  Gauntlet::CoreGame::core->getMovementMgr().addEntity(this);
}
