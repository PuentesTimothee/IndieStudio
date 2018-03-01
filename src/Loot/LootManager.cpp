//
// Created by mymy on 07/06/17.
//

#include <random>
#include "Systems/Loot/LootManager.hpp"
#include <Factory/Factory.hpp>
#include <Entity/Collectable/Ananas.hpp>
#include <Entity/Collectable/Hamburger.hpp>

void Gauntlet::LootManager::takeEvent(Gauntlet::Event const &event)
{
  if (event._type == Gauntlet::EventType::DESTROY)
    this->handleDestroy(event);
}

void Gauntlet::LootManager::handleDestroy(Gauntlet::Event const &event)
{
  Gauntlet::Entity *entity;

  entity = event._entities[0].get();
  if (entity
      && (entity->type == Entity::Type::EVIL || entity->type == Entity::Type::DESTROYABLE))
    {
      this->generateObject(entity);
    }
}

void Gauntlet::LootManager::generateObject(Gauntlet::Entity *ent)
{
  int rand = nb(CoreGame::core->gen);

  if (ent->type == Entity::Type::DESTROYABLE && rand < 50)
    {
      std::shared_ptr<Gauntlet::Entity> object = EntityFactory::create<Gauntlet::Coin>();
      Gauntlet::CoreGame::core->addEntity(object);
      object->setEntityTrans(ent->getPtr<Model>()->node->getPosition(), Ogre::Vector3::ZERO);
    }
  else if (rand >= 50)
      {
	std::shared_ptr<Gauntlet::Entity> object;
	if (rand >= 50 && rand <= 74)
	  object = EntityFactory::create<Gauntlet::Coin>();
	else if (rand >= 75 && rand <= 86)
	    object = EntityFactory::create<Gauntlet::Meat>();
	  else if (rand >= 87 && rand <= 90)
	      object = EntityFactory::create<Gauntlet::Ananas>();
	    else if (rand >= 91 && rand <= 95)
		object = EntityFactory::create<Gauntlet::Icecream>();
	      else if (rand >= 96 && rand <= 97)
		  object = EntityFactory::create<Gauntlet::Hamburger>();
		else
		    object = EntityFactory::create<Gauntlet::Donuts>();
	Gauntlet::CoreGame::core->addEntity(object);
	object->setEntityTrans(ent->getPtr<Model>()->node->getPosition(), Ogre::Vector3::ZERO);
	Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::IDLE, object);
    }
}
