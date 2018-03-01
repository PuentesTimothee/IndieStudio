//
// Created by puentes on 06/06/17.
//

#include "Entity/Effect/HealAttack.hpp"
#include "Components/LightSource.hpp"

Gauntlet::HealAttack::HealAttack(int id)
	: Attack(id, "lightBall.mesh")
{
  Gauntlet::Model	*model = this->getPtr<Gauntlet::Model>();
  Gauntlet::LightSource	*light = new Gauntlet::LightSource(model->node,
								  Ogre::Vector3(0, 2.5, 0),
								  Ogre::ColourValue(1, 0.5, 0.3),
								  Ogre::ColourValue(1, 1, 0.3),
								  15);

  this->attach<Gauntlet::LightSource>(light);
}
