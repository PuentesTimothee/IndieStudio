//
// Created by puentes on 13/06/17.
//

#ifndef INDIE_TORCH_HPP
#define INDIE_TORCH_HPP

#include "Entity/Entity.hpp"

#include "Components/Components.hpp"
#include "Components/Model.hpp"
#include "Components/Animation.hpp"
#include "Components/EntityState.hpp"
#include "Components/LightSource.hpp"

namespace Gauntlet
{
  class Torch : public Gauntlet::Entity
  {
   private:
    static std::string modelName;
    static std::string name;

   public:
    Torch(int id);
    virtual ~Torch()
    {
    };
  };
}


#endif //INDIE_TORCH_HPP
