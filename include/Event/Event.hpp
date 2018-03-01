//
// Created by mymy on 25/05/17.
//

#ifndef INDIE_EVENT_HPP
#define INDIE_EVENT_HPP

#include <vector>

#include <Ogre.h>

#include "Entity/Entity.hpp"

namespace Gauntlet
{
  enum class EventType : int
  {
    MOVE,
    ATTACK,
    ATTACK_END,
    DASH,
    COLLISION,
    IDLE,
    MENU,
    MAIN_MENU,
    NEW_GAME,
    ENTER,
    SUMMONING,
    SPAWN_BOSS,
    SAVE,
    LOAD,
    DESTROY,
    LEVEL_END,
    VICTORY,
    DEFEAT,
    QUIT,
    REVIVE
  };
  
  struct Event
  {
    EventType _type;
    std::vector<std::shared_ptr<Gauntlet::Entity> > _entities;
    Event() = default;
    Event(Gauntlet::EventType);
    Event(Gauntlet::EventType e,
	  std::vector<std::shared_ptr<Gauntlet::Entity> > v) : _type(e), _entities(v)
    {}
    virtual ~Event();
  };
  
  struct MoveEvent : public Event
  {
      enum class Type : int
      {
    	UP = 0,
	    DOWN = 1,
	    LEFT = 2,
	    RIGHT = 3,
	    CUSTOM = 4
      };

      Ogre::Vector3	customDir;

      MoveEvent() : Event(Gauntlet::EventType::MOVE) {}

      virtual ~MoveEvent() {}
      std::vector<Gauntlet::MoveEvent::Type> type;
  };

  std::ostream &	operator<<(std::ostream& istream, Gauntlet::Event const & event);
};

#endif //INDIE_EVENT_HPP
