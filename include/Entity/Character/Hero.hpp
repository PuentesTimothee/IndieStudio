//
// Created by benito on 07/06/17.
//

#ifndef INDIE_HERO_HPP
#define INDIE_HERO_HPP

namespace Gauntlet
{
    class Hero : public Gauntlet::Entity
    {
    public:
        Hero(int id) : Entity(Gauntlet::Entity::Type::HERO, id) {}
        virtual void becomeAI(std::vector<std::shared_ptr<Entity>> const& a) = 0;
        virtual ~Hero() {};
    };
}

#endif //INDIE_HERO_HPP
