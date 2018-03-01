//
// Created by puentes on 05/06/17.
//

#ifndef INDIE_CUSTOMMATH_HPP
#define INDIE_CUSTOMMATH_HPP

#include <Ogre.h>
#include <OgreMath.h>

namespace Gauntlet
{
  class CustomMath
  {
   private:
    CustomMath() {};
   public:

    static Ogre::Vector3	rotateVectorOnY(Ogre::Vector3 &vec, Ogre::Radian const &rot);
  };
}

#endif //INDIE_CUSTOMMATH_HPP
