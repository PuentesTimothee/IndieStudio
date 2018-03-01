//
// Pig.hpp for indie in /home/benito/rendu/cpp/cpp_indie_studio
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Mon May 22 16:42:20 2017 benito
// Last update Mon M    ay 22 17:32:46 2017 benito
//

#ifndef PIG_HPP_
# define PIG_HPP_

#include "Entity/Entity.hpp"

#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/Animation.hpp"
#include "Components/EntityState.hpp"
#include "Components/Stats.hpp"
#include "Components/Weapon.hpp"

namespace Gauntlet
{
  class Pig : public Gauntlet::Entity
  {
  public:
    static std::string modelName;
    static std::string name;
   public:
    Pig(int id);

    virtual ~Pig()
    {};
  };
};

# endif //PIG_HPP_
