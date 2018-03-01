//
// Created by puentes on 31/05/17.
//

#ifndef INDIE_GROUND_HPP
#define INDIE_GROUND_HPP

#include "Entity/Entity.hpp"

#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/Animation.hpp"
#include "Components/EntityState.hpp"

namespace Gauntlet
{
  class Ground : public Gauntlet::Entity
  {
   private:
    static std::string modelName;
    static std::string name;

   public:
    Ground(int id);
    virtual ~Ground()
    {
    };
  };
}

#endif //INDIE_GROUND_HPP
