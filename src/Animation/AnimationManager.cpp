//
// Created by puentes on 10/05/17.
//

#include "Systems/Animation/AnimationManager.hpp"
#include "CoreGame.hpp"

Gauntlet::AnimationManager::AnimationManager(Ogre::SceneManager *sceneManager)
	: _sceneManager(sceneManager)
{
}

Gauntlet::AnimationManager::~AnimationManager(void)
{
}

void			Gauntlet::AnimationManager::animate(Gauntlet::Animation *animation)
{

  Ogre::AnimationState *ogreAnim = animation->getState();

  ogreAnim->setEnabled(true);
  ogreAnim->setLoop(animation->loop);

  if (!animation->loop)
    ogreAnim->setTimePosition(0);
  return;
}



void			Gauntlet::AnimationManager::render(Ogre::Real const &time)
{
  Ogre::AnimationState*	ogreAnim;

  for (auto &anim : this->_animationVector)
    {
      if ((ogreAnim = anim->getState()) != nullptr)
	ogreAnim->addTime(Ogre::Real(time * anim->speed));
    }
}

void			Gauntlet::AnimationManager::clearAll()
{
  this->_animationVector.clear();
}

void			Gauntlet::AnimationManager::clear(Gauntlet::Animation *animation)
{
  auto a = std::find(this->_animationVector.begin(),
					 this->_animationVector.end(),
					 animation);
  if (this->_animationVector.end() != a)
    {
      this->_animationVector.erase(a);
    }
}

void			Gauntlet::AnimationManager::clear(Gauntlet::Entity *ent)
{
  Gauntlet::Animation	*anim = ent->getPtr<Gauntlet::Animation>();

  if (anim)
    this->clear(anim);
}

void			Gauntlet::AnimationManager::takeEvent(Gauntlet::Event const &event)
{
  Gauntlet::Animation	*anim;
  Gauntlet::State	*state;
  Gauntlet::Stats       *stats;
  Gauntlet::Weapon      *weapon;


  if (event._entities.empty())
    return;

  state = event._entities[0]->getPtr<Gauntlet::State>();
  anim = event._entities[0]->getPtr<Gauntlet::Animation>();
  stats = event._entities[0]->getPtr<Gauntlet::Stats>();
  weapon = event._entities[0]->getPtr<Gauntlet::Weapon>();

  switch (event._type)
    {
      case (Gauntlet::EventType::ATTACK) :
	if (anim && state && weapon)
	  this->animationAttack(anim, state, weapon->attackSpeed);
      break;
      case (Gauntlet::EventType::MOVE) :
	if (anim && state && stats)
	  this->animationRun(anim, state, stats->moveSpeed);
      break;
      case (Gauntlet::EventType::DESTROY) :
	if (event._entities[0]->type != Entity::Type::HERO)
	  this->clear(event._entities[0].get());
	else if (anim && state)
	  this->animationDead(anim, state);
	break;
      case (Gauntlet::EventType::REVIVE) :
	if (anim)
	  this->animationRevive(anim);
      default:
	if (anim && state)
	  this->animationDefault(anim, state);
      break;
    }
}

void		Gauntlet::AnimationManager::animationAttack(Gauntlet::Animation *anim, Gauntlet::State *, double speed)
{
  anim->setAnimation("attack", false, speed);
  this->animate(anim);
}

void		Gauntlet::AnimationManager::animationRun(Gauntlet::Animation *anim, Gauntlet::State *, double speed)
{
  anim->setAnimation("run", true, speed);
  this->animate(anim);
}

void		Gauntlet::AnimationManager::animationIdle(Gauntlet::Animation *anim, Gauntlet::State *)
{
  anim->setAnimation("idle", true);
  this->animate(anim);
}

void		Gauntlet::AnimationManager::animationDefault(Gauntlet::Animation *anim, Gauntlet::State *state)
{
  if (state->type == Gauntlet::State::Type::IDLE)
    {
      anim->setAnimation("idle", true);
      this->animate(anim);
    }
}

void            Gauntlet::AnimationManager::animationRevive(Gauntlet::Animation *anim)
{
  anim->setAnimation("revive", false);
  this->animate(anim);
}

void		Gauntlet::AnimationManager::animationDead(Gauntlet::Animation *anim, Gauntlet::State *state)
{
  if (state->type == Gauntlet::State::Type::DEAD)
    {
      anim->setAnimation("death", false);
      this->animate(anim);
    }
}

void		Gauntlet::AnimationManager::addAnimation(Gauntlet::Animation *animation)
{
  this->_animationVector.push_back(animation);
}
