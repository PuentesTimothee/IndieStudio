//
// Components.hpp for indie in /home/benito/rendu/cpp/cpp_indie_studio/include
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Tue May  9 19:37:24 2017 benito
// Last update Tue May 23 16:53:18 2017 benito
//

#ifndef COMPONENTS_HPP_
# define COMPONENTS_HPP_

struct IComponent
{
  enum class Type
    {
      POSITION,
      STATS,
      ASSETS,
      ATTACK,
      ANIMATION,	
    };
  
  virtual ~IComponent() {}
};

# endif //COMPONENTS_HPP_
