//
// Created by mymy on 02/06/17.
//

#ifndef INDIE_WEAPON_HPP
#define INDIE_WEAPON_HPP

#include <OgreVector3.h>
#include "Components.hpp"

namespace Gauntlet
{
  struct Weapon : public IComponent
  {
    enum Type : int
    {
      CAC,
      DIST,
      HEAL,
      ZONE_DIST,
    };

    int			damage;
    double		attackSpeed;
    Weapon::Type	type;
    Ogre::Vector3	rangeStart;
    Ogre::Vector3	rangeEnd;

    Weapon(int damage, double attackSpeed, Weapon::Type const &type, Ogre::Vector3 const &rangeStart = Ogre::Vector3(5, 1, 0), Ogre::Vector3 const &rangeEnd = Ogre::Vector3(10, 1, 0));
    Weapon(Weapon const &other);

    ~Weapon() {};
  };
}

#endif //INDIE_WEAPON_HPP
