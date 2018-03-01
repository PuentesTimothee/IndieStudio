//
// Created by mymy on 05/06/17.
//

#include "Systems/Map/MapLoader.hpp"
#include <CoreGame.hpp>

Gauntlet::MapLoader::MapLoader()
	: indexMap(0), loadFunctions(0)
{
  loadFunctions.push_back(std::bind(&Gauntlet::MapLoader::loadMap1, this));
  loadFunctions.push_back(std::bind(&Gauntlet::MapLoader::loadMap2, this));
  loadFunctions.push_back(std::bind(&Gauntlet::MapLoader::loadMap3, this));
}

void Gauntlet::MapLoader::takeEvent(Gauntlet::Event const &event)
{
  if (event._type == Gauntlet::EventType::LEVEL_END)
    this->loadNextMap();
}

void    Gauntlet::MapLoader::loadNextMap()
{
  if (this->loadFunctions.size() > this->indexMap)
    {
      this->loadFunctions[indexMap]();
      this->indexMap += 1;
    }
}

void    Gauntlet::MapLoader::putBase() const
{
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(0, 0, -105), Ogre::Vector3(-1, 0, 0));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(75, 0, -105), Ogre::Vector3(-1, 0, 0));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(-75, 0, -105), Ogre::Vector3(-1, 0, 0));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(0, 0, 75), Ogre::Vector3(1, 0, 0));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(75, 0, 75), Ogre::Vector3(1, 0, 0));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(-75, 0, 75), Ogre::Vector3(1, 0, 0));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(-105, 0, 0), Ogre::Vector3(0, 0, 1));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(-105, 0, 75), Ogre::Vector3(0, 0, 1));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(-105, 0, -75), Ogre::Vector3(0, 0, 1));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(105, 0, 0), Ogre::Vector3(0, 0, -1));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(105, 0, 75), Ogre::Vector3(0, 0, -1));
  this->createItemAt<Gauntlet::Wall>(Ogre::Vector3(105, 0, -75), Ogre::Vector3(0, 0, -1));

  this->createItemAt<Gauntlet::Torch>(Ogre::Vector3(-75, 0, -10));
  this->createItemAt<Gauntlet::Torch>(Ogre::Vector3(75, 0, 10));

  this->createItemAt<Gauntlet::Ground>();
}

void			Gauntlet::MapLoader::loadMap1() const
{
  this->putBase();

  this->createItemAt<Gauntlet::Crate>(Ogre::Vector3(15, 0, -95));
  this->createItemAt<Gauntlet::Vase>(Ogre::Vector3(10, 0, -90));
  this->createItemAt<Gauntlet::Vase>(Ogre::Vector3(12, 0, -93));
  this->createItemAt<Gauntlet::Crate>(Ogre::Vector3(12, 0, 20));
  this->createItemAt<Gauntlet::Crate>(Ogre::Vector3(12, 0, 21));
  this->createItemAt<Gauntlet::Crate>(Ogre::Vector3(11, 0, 22));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(10, 0, -95));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(-10, 0, -95));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(-92, 0, 0));
}

void			Gauntlet::MapLoader::loadMap2() const
{
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(-75, 0, -75));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(-65, 0, -75));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(75, 0, -75));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(65, 0, -75));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(75, 0, 10));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(75, 0, -10));
}

void			Gauntlet::MapLoader::loadMap3() const
{
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(0, 0, 75));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(10, 0, 75));
  this->createItemAt<Gauntlet::Chest>(Ogre::Vector3(-10, 0, 75));
}

void	Gauntlet::MapLoader::restartGame()
{
  this->indexMap = 0;
}

template<typename Item>
void			Gauntlet::MapLoader::createItemAt(Ogre::Vector3 const &pos,
							      Ogre::Vector3 const &rot) const
{
  std::shared_ptr<Gauntlet::Entity>     item = EntityFactory::create<Item>();
  item->setEntityTrans(pos, rot);
  Gauntlet::CoreGame::core->addEntity(item);
}