//
// Factory.hpp for indie in /home/benito/rendu/cpp/cpp_indie_studio/include
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Tue May  9 20:17:10 2017 benito
// Last update Tue May 23 16:14:23 2017 Mymy Aragon
//

#ifndef FACTORY_HPP_
# define FACTORY_HPP_

#include <memory>
#include <unordered_map>
#include "Entity/Entity.hpp"
#include "Entity/Character/Warrior.hpp"
#include "Entity/Character/Priest.hpp"
#include "Entity/Character/Valkyrie.hpp"
#include "Entity/Character/Assassin.hpp"
#include "CoreGame.hpp"

#include "Systems/Collision/CollisionManager.hpp"

//
// Permet d'encapsuler la création d'entités et leur attribuer un id
//

class EntityFactory
{
private:
  static int id;
public:
  static std::unordered_map<int, Gauntlet::Entity *> entities;

  template<typename T>
  static std::shared_ptr<T>	create();
  static void 			destroy(Gauntlet::Entity *ent);
  static void 			destroyAll();
};

#include "FactoryImplem.hpp"

# endif //FACTORY_HPP_
