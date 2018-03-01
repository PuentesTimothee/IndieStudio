//
// Created by benito on 25/05/17.
//

#ifndef INDIE_SOUND_HPP
#define INDIE_SOUND_HPP

#include <iostream>
#include "Components.hpp"

namespace Gauntlet
{
    struct Sound : public IComponent
    {
        std::string death;
        std::string move;
        std::string attack;

        Sound() = default;
        Sound(std::string const& d,
              std::string const& m,
              std::string const& a) : death(d), move(m), attack(a)
        {};
    };
}

#endif //INDIE_SOUND_HPP
