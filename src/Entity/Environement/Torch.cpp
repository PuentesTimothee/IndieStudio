//
// Created by puentes on 13/06/17.
//

#include "Entity/Environement/Torch.hpp"

std::string Gauntlet::Torch::modelName = "torch.mesh";
std::string Gauntlet::Torch::name = "torch";

Gauntlet::Torch::Torch(int id)
	: Entity(Entity::Type::WALLS, id)
{
  std::string nameEnt = this->name + std::to_string(id);

  Ogre::Vector3			hitbox(1, 4, 1);
  Gauntlet::Model		*model = new Gauntlet::Model(this->modelName,
							      nameEnt,
							      hitbox,
							      true);
  Gauntlet::LightSource		*light = new Gauntlet::LightSource(model->node,
									  Ogre::Vector3(0, 20, 0),
									  Ogre::ColourValue(1, 0.2, 0.2),
									  Ogre::ColourValue(1, 0.7, 0.2),
									  75);

  this->attach<Gauntlet::Model>(model);
  this->attach<Gauntlet::LightSource>(light);
}