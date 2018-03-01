//
// Created by puentes on 31/05/17.
//

#ifndef INDIE_WALL_HPP
#define INDIE_WALL_HPP

#include "Entity/Entity.hpp"

#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/Animation.hpp"
#include "Components/EntityState.hpp"

namespace Gauntlet
{
  class Wall : public Gauntlet::Entity
  {
   private:
    static std::string modelName;
    static std::string name;

   public:
    Wall(int id);
    virtual ~Wall()
    {
    };
  };
}

#endif //INDIE_WALL_HPP
