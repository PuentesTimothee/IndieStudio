//
// Created by mymy on 25/05/17.
//

#include "Event/Event.hpp"

Gauntlet::Event::Event(Gauntlet::EventType type) :
_type(type), _entities()
{
}

Gauntlet::Event::~Event()
{
}

std::ostream &		Gauntlet::operator<<(std::ostream& istream, Gauntlet::Event const & event)
{
  istream << static_cast<int>(event._type);
  return (istream);
}