//
// Created by puentes on 19/05/17.
//

#include <CoreGame.hpp>
#include "Components/Animation.hpp"

Gauntlet::Animation::Animation(Ogre::Entity *paramEntity)
	: ent(paramEntity),
	  actualAnim("idle"),
	  entName(paramEntity->getName()),
	  on(false),
	  loop(false),
	  speed(1)
{
  Gauntlet::CoreGame::core->getAnimationMgr().addAnimation(this);
}

Gauntlet::Animation::~Animation()
{
}


Ogre::AnimationState*		Gauntlet::Animation::getState() const
{
  return this->ent->getAnimationState(this->actualAnim);
}

void				Gauntlet::Animation::setAnimation(std::string name, bool repeat, double speed)
{
    if (this->on)
        this->getState()->setEnabled(false);
    else
      this->on = true;
    this->actualAnim = name;
    this->loop = repeat;
    this->speed = speed;
}
