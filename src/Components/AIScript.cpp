//
// Created by benito on 05/06/17.
//

#include <AI/AI.hpp>
#include <Components/Weapon.hpp>
#include <CoreGame.hpp>
#include "Components/AIScript.hpp"
#include "Components/Model.hpp"
#include "Components/Stats.hpp"

std::vector<float> Gauntlet::IAIScript::calculDir(std::shared_ptr<Entity> const &s,
                                    std::pair<std::shared_ptr<Gauntlet::Entity>, float> const &ret) const
{
    Gauntlet::Model *model = s->getPtr<Gauntlet::Model>();
    if (!ret.first)
        throw std::runtime_error("Error with model");
    Gauntlet::Model *retModel = ret.first->getPtr<Gauntlet::Model>();

    if (!model ||
        !retModel)
        throw std::runtime_error("Error with model");

    auto const &actualX = model->dirVec.x;
    auto const &actualZ = model->dirVec.z;

    auto dirX = (AI::calculDir(retModel->node->getPosition().x,
                               model->node->getPosition().x));
    auto dirZ = (AI::calculDir(retModel->node->getPosition().z,
                               model->node->getPosition().z));
    return (std::vector<float>{dirX, dirZ, actualX, actualZ});
}

bool Gauntlet::IAIScript::youMayTurn(std::vector<float> const& dir,
                                     std::shared_ptr<Entity> const &s) const
{
     auto dirX = dir[0];
     auto dirZ = dir[1];
     auto actualX = dir[2];
     auto actualZ = dir[3];
     if (dirX != actualX ||
         dirZ != actualZ) {
         auto *event = new Gauntlet::MoveEvent;
         if (dirX == -1.0f)
             event->type.push_back(Gauntlet::MoveEvent::Type::LEFT);
         else if (dirX == 1.0f)
             event->type.push_back(Gauntlet::MoveEvent::Type::RIGHT);
         if (dirZ == -1.0f)
             event->type.push_back(Gauntlet::MoveEvent::Type::UP);
         else if (dirZ == 1.0f)
             event->type.push_back(Gauntlet::MoveEvent::Type::DOWN);
         event->_entities.push_back(s);
         Gauntlet::CoreGame::core->events.emplace_back(event);
         return (true);
     }
    return (false);
}

Gauntlet::Event* Gauntlet::IAIScript::HitOrRun(std::pair<std::shared_ptr<Gauntlet::Entity>, float > const& ret,
                                               std::shared_ptr<Entity> const& s)
{
    Gauntlet::Event *event = nullptr;

    try {

        if (ret.second < s->get<Gauntlet::Weapon>().rangeEnd.x && ret.second != 0.0) {
            auto dir = this->calculDir(s, ret);
            this->youMayTurn(dir, s);
            event = new Gauntlet::Event(Gauntlet::EventType::ATTACK);
        } else if (ret.second != -1.0) {
            auto rdir = this->calculDir(s, ret);
            this->youMayTurn(rdir, s);
        } else
            event = new Gauntlet::Event(Gauntlet::EventType::IDLE);
    }
    catch (std::exception const&) {}
    return (event);
}

std::pair<std::shared_ptr<Gauntlet::Entity>, float >       Gauntlet::IBaseFighter::chooseTarget(std::shared_ptr<Entity> const &soldier,
                                                                                std::vector<std::shared_ptr<Gauntlet::Entity>> const &targets) const
{
    auto const&         soldierVector = soldier->getPtr<Gauntlet::Model>()->node->getPosition();
    auto                max = -1.0;
    std::shared_ptr<Gauntlet::Entity>  ret = nullptr;

    for (auto const& h : targets)
    {
    	if (!h || h->getPtr<Gauntlet::State>()->type == Gauntlet::State::Type::DEAD)
	      {
	        continue;
    	  }
        auto const& hVector = h->get<Gauntlet::Model>().node->getPosition();
        auto dist = sqrt(pow(hVector.x - soldierVector.x, 2) + pow(hVector.z - soldierVector.z, 2));

        if (dist < max || max == -1.0)
        {
    	    ret = h;
            max = dist;
        }
    }
    return (std::make_pair(ret, max));
}

std::pair<std::shared_ptr<Gauntlet::Entity>, float > Gauntlet::GhostScript::chooseTarget(std::shared_ptr<Entity> const &soldier,
                                                                       std::vector<std::shared_ptr<Gauntlet::Entity>> const &targets) const
{
    auto const&         soldierVector = soldier->getPtr<Gauntlet::Model>()->node->getPosition();
    auto                max = -1.0;
    auto                dist = -1.0;
    std::shared_ptr<Gauntlet::Entity>  ret = nullptr;

    for (auto const& h : targets)
    {
        if (h->getPtr<Gauntlet::State>() && h->getPtr<Gauntlet::State>()->type == Gauntlet::State::Type::DEAD)
        {
            continue;
        }

        auto hp = h->get<Gauntlet::Stats>().life;
        if (hp < max || max == -1.0)
        {
            ret = h;
            max = hp;
            auto const& hVector =  h->get<Gauntlet::Model>().node->getPosition();
            dist = sqrt(pow(hVector.x - soldierVector.x, 2) + pow(hVector.z - soldierVector.z, 2));
        }
    }
    return (std::make_pair(ret, dist));
}

Gauntlet::Event    *Gauntlet::PigScript::makeAction(std::shared_ptr<Entity> const& s,
                            std::vector<std::shared_ptr<Gauntlet::Entity>> const& heroes)
{
    auto ret = this->chooseTarget(s, heroes);

    return (this->HitOrRun(ret, s));
}

Gauntlet::BossScript::BossScript() : x(0, 1), z(0, 1)
{
}

Gauntlet::Event* Gauntlet::BossScript::HitOrRun(std::pair<std::shared_ptr<Gauntlet::Entity>, float > const& ret,
                                               std::shared_ptr<Entity> const& s)
{
    Gauntlet::Event *event = nullptr;

    try {

        if (ret.second < s->get<Gauntlet::Weapon>().rangeEnd.x && ret.second != 0.0) {
            auto dir = this->calculDir(s, ret);
            auto &dirX = dir[0];
            auto &dirZ = dir[1];

            if (x(CoreGame::core->gen) == 1)
            {
                dirX *= -1.0;
                dirZ = 0.0;
            }
            if (z(CoreGame::core->gen) == 1)
            {
                dirZ *= -1.0;
                dirX = 0.0;
            }
            this->youMayTurn(dir, s);
            event = new Gauntlet::Event(Gauntlet::EventType::ATTACK);
        } else if (ret.second != -1.0) {
            auto rdir = this->calculDir(s, ret);
            this->youMayTurn(rdir, s);
        } else
            event = new Gauntlet::Event(Gauntlet::EventType::IDLE);
    }
    catch (std::exception const&) {}
    return (event);
}

Gauntlet::Event* Gauntlet::BossScript::makeAction(std::shared_ptr<Entity> const &s,
                                                  std::vector<std::shared_ptr<Gauntlet::Entity>> const &heroes)
{
    auto ret = this->chooseTarget(s, heroes);

    return (this->HitOrRun(ret, s));
}

Gauntlet::Event* Gauntlet::GhostScript::makeAction(std::shared_ptr<Entity> const &s,
                                                   std::vector<std::shared_ptr<Gauntlet::Entity>> const &heroes)
{
    auto ret = this->chooseTarget(s, heroes);

    return (this->HitOrRun(ret, s));
}

Gauntlet::Event    *Gauntlet::ValkyrieScript::makeAction(std::shared_ptr<Entity> const &s,
                                                         std::vector<std::shared_ptr<Gauntlet::Entity>> const &)
{
    auto ret = this->chooseTarget(s, this->refOnArmy);

    return (this->HitOrRun(ret, s));
}

std::pair<std::shared_ptr<Gauntlet::Entity>, float > Gauntlet::PriestScript::chooseTarget(std::shared_ptr<Entity> const &soldier,
                                                                      std::vector<std::shared_ptr<Gauntlet::Entity>> const &targets) const
{
    auto const&         soldierVector = soldier->getPtr<Gauntlet::Model>()->node->getPosition();
    auto                max = -1.0;
    auto                dist = -1.0;
    std::shared_ptr<Gauntlet::Entity> ret = nullptr;

    for (auto const& h : targets)
    {
        if ((h->getPtr<Gauntlet::State>() && h->getPtr<Gauntlet::State>()->type == Gauntlet::State::Type::DEAD) ||
                h == soldier)
        {
            continue;
        }

        auto hp = h->get<Gauntlet::Stats>().life;
        if ((hp < max || max == -1.0) && hp < h->get<Gauntlet::Stats>().lifeMax)
        {
            ret = h;
            max = hp;
            auto const& hVector =  h->get<Gauntlet::Model>().node->getPosition();
            dist = sqrt(pow(hVector.x - soldierVector.x, 2) + pow(hVector.z - soldierVector.z, 2));
        }
    }
    return (std::make_pair(ret, dist));
}

Gauntlet::Event* Gauntlet::Runner::runAway(std::shared_ptr<Entity> const &s,
                                           std::pair<std::shared_ptr<Gauntlet::Entity>, float> const &ret) const
{
    Gauntlet::Model *model = s->getPtr<Gauntlet::Model>();
    Gauntlet::Model *retModel = ret.first->getPtr<Gauntlet::Model>();

    if (!model ||
        !retModel)
        return nullptr;

    auto const &actualX = model->dirVec.x;
    auto const &actualZ = model->dirVec.z;

    auto dirX = (AI::calculDir(retModel->node->getPosition().x,
                               model->node->getPosition().x));
    auto dirZ = (AI::calculDir(retModel->node->getPosition().z,
                               model->node->getPosition().z));

    dirX *= -1.0;
    dirZ *= -1.0;
    if (dirX != actualX ||
        dirZ != actualZ)
    {
        auto *event = new Gauntlet::MoveEvent;
        if (dirX == -1.0f)
            event->type.push_back(Gauntlet::MoveEvent::Type::LEFT);
        else if (dirX == 1.0f)
            event->type.push_back(Gauntlet::MoveEvent::Type::RIGHT);
        if (dirZ == -1.0f)
            event->type.push_back(Gauntlet::MoveEvent::Type::UP);
        else if (dirZ == 1.0f)
            event->type.push_back(Gauntlet::MoveEvent::Type::DOWN);
        return (event);
    }
    return (nullptr);
}

Gauntlet::Event* Gauntlet::PriestScript::makeAction(std::shared_ptr<Entity> const &s,
                                                    std::vector<std::shared_ptr<Gauntlet::Entity>> const &heroes)
{
    auto retEvil = this->Gauntlet::IBaseFighter::chooseTarget(s, this->refOnArmy);

    if (retEvil.second < 15.0 && retEvil.second != 0.0 && retEvil.second != -1.0)
    {
        return (this->runAway(s, retEvil));
    }

    auto retGood = this->chooseTarget(s, heroes);
    if (retGood.first)
    {
          return (this->HitOrRun(retGood, s));
    }
      return (this->HitOrRun(retEvil, s));
}

Gauntlet::Event* Gauntlet::AssassinScript::makeAction(std::shared_ptr<Entity> const &s,
                                                      std::vector<std::shared_ptr<Gauntlet::Entity>> const &)
{
    auto retEvil = this->chooseTarget(s, this->refOnArmy);

    if (retEvil.second < 10.0 && retEvil.second != 0.0 && retEvil.second != -1.0)
    {
        return (this->runAway(s, retEvil));
    }
    return (this->HitOrRun(retEvil, s));
}
