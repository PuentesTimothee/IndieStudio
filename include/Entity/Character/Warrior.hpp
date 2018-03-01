//
// Warrior.hpp for indie in /home/benito/rendu/cpp/cpp_indie_studio/include
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Tue May  9 20:52:27 2017 benito
// Last update Tue May 23 11:23:29 2017 benito
//

#ifndef WARRIOR_HPP_
# define WARRIOR_HPP_

#include "Entity/Entity.hpp"
#include "Entity/Character/Hero.hpp"

#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/Animation.hpp"
#include "Components/EntityState.hpp"
#include "Components/Stats.hpp"
#include "Components/Weapon.hpp"

namespace Gauntlet
{
  class Warrior : public Gauntlet::Hero
  {
   public:
    Warrior(int id);

    virtual ~Warrior()
    {};
    virtual void becomeAI(std::vector<std::shared_ptr<Gauntlet::Entity>> const& a) override ;
  };
}

# endif //WARRIOR_HPP_
