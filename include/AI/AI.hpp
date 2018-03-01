//
// Created by benito on 26/05/17.
//

#ifndef INDIE_AI_HPP
#define INDIE_AI_HPP

#include <utility>
#include <vector>
#include "Systems/System.hpp"
#include "Event/Event.hpp"

namespace Gauntlet
{
    class AI : public Gauntlet::System
    {
    private:
        unsigned int     _level;
        unsigned int     _wave;
        std::uniform_int_distribution<int> x;
        std::uniform_int_distribution<int> z;

        std::vector<std::shared_ptr<Entity> > _army;
        std::vector<std::shared_ptr<Entity> > _AIheroes;
        std::vector< std::vector<int> >       _armyCounter;
;

    private:
        std::pair<Gauntlet::Entity*, float >  findNearestHero(std::shared_ptr<Entity> const&,
                                                           std::vector<std::shared_ptr<Gauntlet::Entity>> const&) const;

    public:
        static float calculDir(float a, float b);

    public:
        AI();

        virtual ~AI() {};

    private:
        void placeBadGuy(std::shared_ptr<Gauntlet::Entity> const& entity);
        bool createSoldier();

    public:
      void addPlayer(std::shared_ptr<Gauntlet::Entity> const& hero);
      void play(std::vector<std::shared_ptr<Gauntlet::Entity>> const&);
      virtual void takeEvent(Event const &) override ;

      void	destroyEnt(Gauntlet::Entity* ent);
      void	destroyAllEnt();
    };
}

#endif //INDIE_AI_HPP
