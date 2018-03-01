//
// Created by mymy on 02/06/17.
//

#include "Components/Weapon.hpp"

Gauntlet::Weapon::Weapon(int			damage,
			 double			attackSpeed,
			 Weapon::Type const	&type,
			 Ogre::Vector3 const	&rangeStart,
			 Ogre::Vector3 const	&rangeEnd)
	: damage(damage),
	  attackSpeed(attackSpeed),
	  type(type),
	  rangeStart(rangeStart),
	  rangeEnd(rangeEnd)
{
}

Gauntlet::Weapon::Weapon(Gauntlet::Weapon const &other)
  : damage(other.damage),
    attackSpeed(other.attackSpeed),
    type(other.type),
    rangeStart(other.rangeStart),
    rangeEnd(other.rangeEnd)
{
}
