//
// Created by benito on 01/06/17.
//

#ifndef INDIE_MOUVEMENTMANAGER_HPP
#define INDIE_MOUVEMENTMANAGER_HPP

#include <Systems/System.hpp>
#include "Components/Model.hpp"
#include "Components/Stats.hpp"

namespace Gauntlet
{
  struct MovementData
  {
   private:
    MovementData() {};
   public:
    MovementData(Gauntlet::Entity *entity1,
		 Gauntlet::Model *model1,
		 Gauntlet::Stats *stats1,
		 Gauntlet::State *state1);

    Gauntlet::Entity	*entity;
    Gauntlet::State	*state;
    Gauntlet::Stats	*stats;
    Gauntlet::Model	*model;
    float 		timer;
  };

  class MovementMgr : public Gauntlet::System
  {
   private:
    std::vector<Gauntlet::MovementData>		_entity;

    void		handleMove(Gauntlet::Event const &event) const;
    void		handleDash(Gauntlet::Event const &event);
    void		handleOther(Gauntlet::Event const &event);

    void 		destroyEntity(std::shared_ptr<Gauntlet::Entity> const& entity);
   public:
    MovementMgr() {};
    virtual ~MovementMgr() {};

    virtual void takeEvent(Gauntlet::Event const&) override ;
    void 		addEntity(Gauntlet::Entity *entity);
    void 		updateSpeed();

    void 		destroyAllEntity();
  };
}

#endif //INDIE_MOUVEMENTMANAGER_HPP
