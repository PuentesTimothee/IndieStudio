//
// Created by benito on 05/06/17.
//

#ifndef INDIE_AISCRIPT_HPP
#define INDIE_AISCRIPT_HPP

#include "Components/Components.hpp"
#include "Event/Event.hpp"

namespace Gauntlet
{
    struct IAIScript : public IComponent
    {
        virtual  std::pair<std::shared_ptr<Gauntlet::Entity>, float >  chooseTarget(std::shared_ptr<Entity> const&,
                                                        std::vector<std::shared_ptr<Gauntlet::Entity>> const&) const = 0;
        virtual Gauntlet::Event *makeAction(std::shared_ptr<Entity> const&,
                                      std::vector<std::shared_ptr<Gauntlet::Entity>> const&) = 0;
        virtual Gauntlet::Event         *HitOrRun(std::pair<std::shared_ptr<Gauntlet::Entity>, float > const& ret,
                                          std::shared_ptr<Entity> const& s);
        std::vector<float> calculDir(std::shared_ptr<Entity> const&,
                                          std::pair<std::shared_ptr<Gauntlet::Entity>, float > const&) const;
        bool                    youMayTurn(std::vector<float> const&,
                                           std::shared_ptr<Entity> const& s) const;

        virtual ~IAIScript() {};
    };

    struct IBaseFighter : public IAIScript
    {
        /* contient la fonction de recherche de base */
        virtual std::pair<std::shared_ptr<Gauntlet::Entity>, float >  chooseTarget(std::shared_ptr<Entity> const&,
                                                           std::vector<std::shared_ptr<Gauntlet::Entity>> const&) const override ;
        virtual ~IBaseFighter() {};
    };

    struct IHeroScript
    {
        protected:
            std::vector<std::shared_ptr<Entity> > const& refOnArmy;
        /* d'autres trucs définissant ce qu'un script de héros à besoin */

    public:
        IHeroScript(std::vector<std::shared_ptr<Entity> >const& a) : refOnArmy(a) {};
        virtual ~IHeroScript() {};
    };

    struct PigScript : public IBaseFighter
    {
        virtual Gauntlet::Event *makeAction(std::shared_ptr<Entity> const& s,
                                      std::vector<std::shared_ptr<Gauntlet::Entity>> const& heroes) override ;
        virtual ~PigScript() {};
    };

    struct GhostScript : public IAIScript
    {
        virtual  std::pair<std::shared_ptr<Gauntlet::Entity>, float >  chooseTarget(std::shared_ptr<Entity> const&,
                                                                    std::vector<std::shared_ptr<Gauntlet::Entity>> const&) const override ;
        virtual Gauntlet::Event *makeAction(std::shared_ptr<Entity> const& s,
                                            std::vector<std::shared_ptr<Gauntlet::Entity>> const& heroes) override ;
        virtual ~GhostScript() {};
    };

    struct BossScript : public IBaseFighter
    {
        std::uniform_int_distribution<int> x;
        std::uniform_int_distribution<int> z;

        //std::queue<int> summonings;

        BossScript();
        virtual Gauntlet::Event *makeAction(std::shared_ptr<Entity> const& s,
                                            std::vector<std::shared_ptr<Gauntlet::Entity>> const& heroes) override ;
        virtual Gauntlet::Event         *HitOrRun(std::pair<std::shared_ptr<Gauntlet::Entity>, float > const& ret,
                                                  std::shared_ptr<Entity> const& s) override ;
        virtual ~BossScript() {};
    };

    struct ValkyrieScript : public IHeroScript, public IBaseFighter
    {
        ValkyrieScript(std::vector<std::shared_ptr<Entity> >const& a) : IHeroScript(a) {};
        virtual Gauntlet::Event *makeAction(std::shared_ptr<Entity> const& s,
                                      std::vector<std::shared_ptr<Gauntlet::Entity>> const& heroes) override ;
        virtual ~ValkyrieScript() {};
    };

    struct Runner
    {
        protected:
            Gauntlet::Event *runAway(std::shared_ptr<Entity> const& s,
                                     std::pair<std::shared_ptr<Gauntlet::Entity>, float > const& ret) const;
    };

    struct PriestScript : public IHeroScript, public IBaseFighter, public Runner
    {
        PriestScript(std::vector<std::shared_ptr<Entity> >const& a) : IHeroScript(a) {};
        virtual Gauntlet::Event *makeAction(std::shared_ptr<Entity> const& s,
                                            std::vector<std::shared_ptr<Gauntlet::Entity>> const& heroes) override ;
        virtual  std::pair<std::shared_ptr<Gauntlet::Entity>, float >  chooseTarget(std::shared_ptr<Entity> const&,
                                                                    std::vector<std::shared_ptr<Gauntlet::Entity>> const&) const override ;
        virtual ~PriestScript() {};
    };

    struct AssassinScript : public IHeroScript, public IBaseFighter, public Runner
    {
        AssassinScript(std::vector<std::shared_ptr<Entity> >const& a) : IHeroScript(a) {};
        virtual Gauntlet::Event *makeAction(std::shared_ptr<Entity> const& s,
                                            std::vector<std::shared_ptr<Gauntlet::Entity>> const& heroes) override ;
        virtual ~AssassinScript() {};
    };
}

#endif //INDIE_AISCRIPT_HPP
