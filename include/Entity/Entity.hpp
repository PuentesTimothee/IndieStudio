//
// Entity.hpp for indie in /home/benito/rendu/cpp/cpp_indie_studio/include
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Tue May  9 17:35:47 2017 benito
// Last update Wed Jun  7 18:12:19 2017 Benito
//

#ifndef ENTITY_HPP_
# define ENTITY_HPP_

#include <iostream>
#include <memory>
#include <unordered_map>
#include <Ogre.h>
#include "Components/Components.hpp"

struct EnumClassHash
{
  template <typename T>
  std::size_t operator()(T t) const
  {
    return static_cast<std::size_t>(t);
  }
};

//
// Une entité répresente n'importe quel objet faisant partie du monde
// Elle est définie par un id et ses composants
//

namespace Gauntlet
{
    class		Entity
    {
        using map = std::unordered_map<int, std::shared_ptr<IComponent> >;
    public:
        enum class Type : int
        {
    	  DEFAULT,
	      HERO,
	      EVIL,
	      POWERUP,
	      WALLS,
	      HERO_ATTACK,
	      EVIL_ATTACK,
	      HEAL_ATTACK,
	      DESTROYABLE
        };

        Entity::Type	type;
      	const int	    id;
    protected:
        Entity::map	    components;

    public:
        Entity(int i) : type(Entity::Type::DEFAULT), id(i) {}

        Entity(Entity::Type t, int i) : type(t), id(i) {}

        Entity(Entity::Type t, int i, Entity::map& m) : type(t), id(i), components(m) {}

        virtual ~Entity() {}
    public:
        static int typeID;
    private:
        template <typename>
        int getTypeID()
        {
          static const int id = ++typeID;
          return (id);
        }
    public:
        template <typename T>
        T& get()
        {
          int key = getTypeID<T>();

          if (components.find(key) == components.end())
            throw std::runtime_error("Component doesnt exists");
          return (static_cast<T&>(*components[key]));
        }
       template <typename T>
        T*	getPtr()
        {
          int				key = getTypeID<T>();
          Entity::map::iterator	tmp;

          if ((tmp = components.find(key)) == components.end())
            return (nullptr);
          return (&(static_cast<T&>(*tmp->second)));
        }

        template <typename T>
        void attach(T *c)
        {
          int key = getTypeID<T>();
          components[key] = std::shared_ptr<T>(c);
        }

        template <typename T>
        void detach()
        {
          int key = getTypeID<T>();

          components.erase(key);
        }

        void 		setEntityTrans(Ogre::Vector3 const	&pos,
                                   Ogre::Vector3 const	&dir);
    };
}

# endif //ENTITY_HPP_
