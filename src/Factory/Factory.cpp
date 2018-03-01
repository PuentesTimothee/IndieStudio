//
// Factory.cpp for indie in /home/benito/rendu/cpp/cpp_indie_studio
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Wed May 10 15:53:41 2017 benito
// Last update Tue May 23 11:34:50 2017 benito
//

#include "Factory/Factory.hpp"


std::unordered_map<int, Gauntlet::Entity *>	EntityFactory::entities;
int			EntityFactory::id;

void			EntityFactory::destroy(Gauntlet::Entity *ent)
{
  EntityFactory::entities.erase(ent->id);
}

void			EntityFactory::destroyAll()
{
  EntityFactory::entities.clear();
}
