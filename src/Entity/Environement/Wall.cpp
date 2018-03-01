//
// Created by puentes on 31/05/17.
//

#include "Entity/Environement/Wall.hpp"

std::string Gauntlet::Wall::modelName = "wall.mesh";
std::string Gauntlet::Wall::name = "wall";

Gauntlet::Wall::Wall(int id)
	: Entity(Entity::Type::WALLS, id)
{
  std::string nameEnt = this->name + std::to_string(id);

  Ogre::Vector3			hitbox(37.5, 4, 2);
  Gauntlet::Model		*model = new Gauntlet::Model(this->modelName,
							      nameEnt,
							      hitbox,
							      true);

  this->attach<Gauntlet::Model>(model);
}
