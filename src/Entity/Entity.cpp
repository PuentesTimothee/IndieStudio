//
// Entity.cpp for indie in /home/benito/rendu/cpp/cpp_indie_studio
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Tue May 23 09:52:57 2017 benito
// Last update Tue May 23 10:16:43 2017 benito
//

#include "Entity/Entity.hpp"
#include "Components/Model.hpp"

int Gauntlet::Entity::typeID;

void		Gauntlet::Entity::setEntityTrans(const Ogre::Vector3 &pos,
                                             const Ogre::Vector3 &dir)
{
    Gauntlet::Model	*model = this->getPtr<Gauntlet::Model>();

    if (model != nullptr)
    {
        model->body->setPosition(pos);
        model->node->setPosition(pos);
        model->dirVec = dir;
        model->node->setOrientation(Ogre::Quaternion(Ogre::Math::ACos(model->dirVec.dotProduct(Ogre::Vector3::UNIT_X)) *
                                                     ((model->dirVec.z >= 0) ? (-1) : (1)),
                                                     Ogre::Vector3::UNIT_Y));
        model->body->setOrientation(Ogre::Quaternion(Ogre::Math::ACos(model->dirVec.dotProduct(Ogre::Vector3::UNIT_X)) *
                                                     ((model->dirVec.z >= 0) ? (-1) : (1)),
                                                     Ogre::Vector3::UNIT_Y));
    }
}