//
// Created by benito on 25/05/17.
//

#ifndef INDIE_SYSTEM_HPP
#define INDIE_SYSTEM_HPP

#include <Event/Event.hpp>

namespace Gauntlet
{
    class System
    {
    public:
        System() = default;
        virtual ~System() {};
        virtual void takeEvent(Gauntlet::Event const &) = 0;
    };
}

#endif //INDIE_SYSTEM_HPP
