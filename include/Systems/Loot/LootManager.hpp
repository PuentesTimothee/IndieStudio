//
// Created by mymy on 07/06/17.
//

#ifndef INDIE_LOOTMANAGER_HPP
#define INDIE_LOOTMANAGER_HPP

#include <Systems/System.hpp>
#include <Entity/Collectable/Coin.hpp>
#include <Entity/Collectable/Icecream.hpp>
#include <Entity/Collectable/Meat.hpp>
#include <Entity/Collectable/Donuts.hpp>

namespace Gauntlet
{
  class LootManager : public System
  {
    std::uniform_int_distribution<int> nb;
    void	handleDestroy(Gauntlet::Event const &);
    void	generateObject(Gauntlet::Entity *);

   public:
    LootManager() : nb(0, 99) {};
    ~LootManager() {};

    void	takeEvent(Gauntlet::Event const &);
  };
}

#endif //INDIE_LOOTMANAGER_HPP
