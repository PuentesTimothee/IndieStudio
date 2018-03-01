//
// Priest.hpp for Indie in /home/mymy/Modules/C++/cpp_indie_studio/include/Entity
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May 23 15:51:19 2017 Mymy Aragon
// Last update Tue Jun 13 15:24:06 2017 benito
//

#ifndef VALKYRIE_HPP_
# define VALKYRIE_HPP_

#include "Entity/Entity.hpp"

#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/Animation.hpp"
#include "Components/EntityState.hpp"
#include "Components/Stats.hpp"
#include "Components/Weapon.hpp"
#include "Entity/Character/Hero.hpp"

namespace Gauntlet
{
  class Valkyrie : public Gauntlet::Hero
  {
   public:
    Valkyrie(int id);

    virtual ~Valkyrie() {};

    virtual void becomeAI(std::vector<std::shared_ptr<Gauntlet::Entity>> const& a) override ;
  };
}

# endif //VALKYRIE_HPP_
