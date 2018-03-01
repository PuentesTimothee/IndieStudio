//
// FactoryImplem.hpp for indie in /home/benito/rendu/cpp/cpp_indie_studio
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Wed May 10 16:06:50 2017 benito
// Last update Tue May 23 11:32:28 2017 benito
//

template<typename T>
std::shared_ptr<T> EntityFactory::create()
{
  auto entity = (new T(id));
  EntityFactory::entities[id] = entity;
  ++id;
  return (std::shared_ptr<T>(static_cast<T *>(entity)));
}
