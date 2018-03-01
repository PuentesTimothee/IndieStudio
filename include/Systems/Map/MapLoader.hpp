//
// Created by mymy on 05/06/17.
//

#ifndef INDIE_MAPLOADER_HPP
#define INDIE_MAPLOADER_HPP

#include <Systems/System.hpp>
#include "Entity/Collectable/Coin.hpp"
#include "Entity/Collectable/Icecream.hpp"
#include "Entity/Collectable/Meat.hpp"
#include "Entity/Destroyable/Chest.hpp"
#include "Entity/Environement/Torch.hpp"
#include "Entity/Destroyable/Crate.hpp"
#include "Entity/Destroyable/Vase.hpp"

#include <functional>

namespace Gauntlet
{
  class MapLoader : System
  {

   private:
    size_t indexMap;
    std::vector<std::function<void()>> loadFunctions;

    void putBase() const;

    void loadMap1() const;
    void loadMap2() const;
    void loadMap3() const;

    template <typename Item>
    void		createItemAt(Ogre::Vector3 const &pos = Ogre::Vector3::ZERO,
				     Ogre::Vector3 const &rot = Ogre::Vector3::ZERO) const;
   public:
    MapLoader();
    ~MapLoader() {};

    void	loadNextMap();
    void	takeEvent(Gauntlet::Event const &);
    void	restartGame();
  };
}


#endif //INDIE_MAPLOADER_HPP
