//
// Created by puentes on 29/05/17.
//

#include "Systems/Collision/CollisionConvertion.hpp"

btVector3		OgreToBullet::convert(Ogre::Vector3 const &vector)
{
  return (btVector3(vector.x,
		    vector.y,
		    vector.z));
}

btQuaternion		OgreToBullet::convert(Ogre::Quaternion const &quat)
{
  return (btQuaternion(quat.x,
		       quat.y,
		       quat.z,
		       quat.w));
}

Ogre::Vector3		BulletToOgre::convert(btVector3 const &vector)
{
  return (Ogre::Vector3(vector.x(),
			vector.y(),
			vector.z()));
}

Ogre::Quaternion	BulletToOgre::convert(btQuaternion const &quat)
{
  return (Ogre::Quaternion(quat.w(),
			   quat.x(),
			   quat.y(),
			   quat.z()));
}
