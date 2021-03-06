//
// Priest.hpp for Indie in /home/mymy/Modules/C++/cpp_indie_studio/include/Entity
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May 23 15:51:19 2017 Mymy Aragon
// Last update Tue May 23 15:51:59 2017 Mymy Aragon
//

#ifndef PRIEST_HPP_
# define PRIEST_HPP_

#include "Entity/Entity.hpp"
#include "Entity/Character/Hero.hpp"
#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/Animation.hpp"
#include "Components/Stats.hpp"
#include "Components/EntityState.hpp"
#include "Components/Weapon.hpp"

namespace Gauntlet
{
  class Priest : public Gauntlet::Hero
  {
     public:
      Priest(int id);

      virtual void becomeAI(std::vector<std::shared_ptr<Gauntlet::Entity>> const& a) override ;
      virtual ~Priest() {};
  };
}

# endif //PRIEST_HPP_
