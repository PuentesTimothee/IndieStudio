//
// Created by benito on 01/06/17.
//

#include <CoreGame.hpp>
#include "Movement/MovementManager.hpp"

void		Gauntlet::MovementMgr::takeEvent(Gauntlet::Event const &event)
{
  switch (event._type)
    {
      case (Gauntlet::EventType::DASH) :
	this->handleDash(event);
	return;
      case (Gauntlet::EventType::MOVE) :
	this->handleMove(event);
      case (Gauntlet::EventType::IDLE) :
      case (Gauntlet::EventType::ATTACK) :
      this->handleOther(event);
      return;
      case (Gauntlet::EventType::DESTROY):
	this->destroyEntity(event._entities[0]);
      return;
      default :
	return;
    }
}

void			Gauntlet::MovementMgr::handleMove(Gauntlet::Event const &event) const
{
  auto const		&revent = static_cast<Gauntlet::MoveEvent const &>(event);

  Gauntlet::Model	*model = revent._entities[0]->getPtr<Gauntlet::Model>();

  if (!model)
    return ;
  model->dirVec.z = 0;
  model->dirVec.y = 0;
  model->dirVec.x = 0;
  for (auto const &t : revent.type)
    {
      switch (t)
    	{
	      case Gauntlet::MoveEvent::Type::UP:
	        model->dirVec.z = -1;
        	break;
	      case Gauntlet::MoveEvent::Type::DOWN:
	        model->dirVec.z = 1;
	        break;
	      case Gauntlet::MoveEvent::Type::LEFT:
	        model->dirVec.x = -1;
	        break;
	      case Gauntlet::MoveEvent::Type::RIGHT:
	        model->dirVec.x = 1;
        	break;
    	  case Gauntlet::MoveEvent::Type::CUSTOM:
	        model->dirVec = revent.customDir;
	        break;
    	}
    }
  model->dirVec.normalise();
}

void			Gauntlet::MovementMgr::destroyEntity(std::shared_ptr<Gauntlet::Entity> const& entity)
{
  if (entity->type == Gauntlet::Entity::Type::HERO)
    return ;
  auto found = std::remove_if(this->_entity.begin(), this->_entity.end(),
			      [entity](Gauntlet::MovementData const &obj)
			      { return (entity.get() == obj.entity); });
  if (found != this->_entity.end())
    this->_entity.erase(found, this->_entity.end());
}

void			Gauntlet::MovementMgr::addEntity(Gauntlet::Entity *entity)
{
  auto			model = entity->getPtr<Gauntlet::Model>();
  auto			stats = entity->getPtr<Gauntlet::Stats>();
  auto			state = entity->getPtr<Gauntlet::State>();
  this->_entity.emplace_back(entity, model, stats, state);
}

void			Gauntlet::MovementMgr::updateSpeed()
{
  for (auto & entity : this->_entity)
    {
      Ogre::Vector3	speed;
      if (entity.stats && entity.model)
	{
	  entity.model->body->setOrientation(entity.model->getDiretion());
	  switch (entity.state->type)
	    {
	      case (Gauntlet::State::Type::DASH) :
		speed = entity.model->dirVec * 50 * entity.stats->moveSpeed;
	      break;
	      case (Gauntlet::State::Type::MOVING) :
		speed = entity.model->dirVec * 10 * entity.stats->moveSpeed;
	      break;
	      default:
		speed = Ogre::Vector3::ZERO;
	      break;
	    }

	  if (entity.timer > 0 &&
		  entity.state->type == Gauntlet::State::Type::DASH)
	    {
	      entity.timer = entity.timer - Gauntlet::CoreGame::core->frameRate;
	      if (entity.timer <= 0)
		{
		  entity.timer = 0;
		  entity.state->type = Gauntlet::State::Type::IDLE;
		}
	    }

	  entity.model->body->setLinearVelocity(speed);
	}
    }
}

void		Gauntlet::MovementMgr::handleDash(Gauntlet::Event const &event)
{
  for (auto & entity : this->_entity)
    {
      if (entity.entity == event._entities[0].get())
	entity.timer = 0.25;
    }
}

void		Gauntlet::MovementMgr::handleOther(Gauntlet::Event const &event)
{
  for (auto & entity : this->_entity)
    {
      if (entity.entity == event._entities[0].get())
	entity.timer = 0;
    }
}

void		Gauntlet::MovementMgr::destroyAllEntity()
{
  this->_entity.clear();
}

Gauntlet::MovementData::MovementData(Gauntlet::Entity *entity1,
				     Gauntlet::Model *model1,
				     Gauntlet::Stats *stats1,
				     Gauntlet::State *state1)
	: entity(entity1),
	  state(state1),
	  stats(stats1),
	  model(model1),
	  timer(-1)
{
}
