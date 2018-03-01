//
// Created by puentes on 31/05/17.
//

#include "Entity/Environement/Ground.hpp"

std::string Gauntlet::Ground::modelName = "groundMesh";
std::string Gauntlet::Ground::name = "ground";

Gauntlet::Ground::Ground(int id)
	: Entity(Entity::Type::WALLS, id)
{
  Ogre::Vector3			normal(0, 1, 0);
  Gauntlet::Model		*model = new Gauntlet::PlaneModel(this->modelName,
								   this->name,
								   normal,
								   true,
								   "groundMat");

  this->attach<Gauntlet::Model>(model);
}
