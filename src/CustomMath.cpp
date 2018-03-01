//
// Created by puentes on 05/06/17.
//

#include "CustomMath.hpp"

Ogre::Vector3		Gauntlet::CustomMath::rotateVectorOnY(Ogre::Vector3 &vec,
								     Ogre::Radian const &rot)
{
  Ogre::Vector3		newVec;

  newVec.x = vec.x * Ogre::Math::Cos(rot) +
	  vec.z * Ogre::Math::Sin(rot);

  newVec.z = vec.z * Ogre::Math::Cos(rot) -
	  vec.x * Ogre::Math::Sin(rot);

  return (newVec);
}
