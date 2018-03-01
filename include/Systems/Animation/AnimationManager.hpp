//
// Created by puentes on 10/05/17.
//

#ifndef ANIMATIONMANAGER_HPP
# define ANIMATIONMANAGER_HPP

# include <Ogre.h>
# include <OgreRoot.h>
# include <OgreSceneManager.h>

# include <vector>
# include <algorithm>
#include <Components/EntityState.hpp>

# include "Systems/System.hpp"

namespace Gauntlet
{
  struct Animation;

  class AnimationManager  : public Gauntlet::System
  {
   private:
    Ogre::SceneManager			*_sceneManager;
    std::vector<Gauntlet::Animation*>	_animationVector;
   public:
    AnimationManager(Ogre::SceneManager *sceneManager);
    ~AnimationManager(void);

    void				animate(Gauntlet::Animation *animation);
    void				clearAll();
    void				clear(Gauntlet::Animation *animation);
    void				clear(Gauntlet::Entity *ent);
    void				addAnimation(Gauntlet::Animation *animation);
    void				render(Ogre::Real const &time);

    virtual void			takeEvent(Gauntlet::Event const &event) override ;

    void				animationAttack(Gauntlet::Animation *anim, Gauntlet::State *state, double speed);
    void				animationRun(Gauntlet::Animation *anim, Gauntlet::State *state, double speed);
    void				animationIdle(Gauntlet::Animation *anim, Gauntlet::State *state);
    void				animationDefault(Gauntlet::Animation *anim, Gauntlet::State *state);
    void				animationDead(Gauntlet::Animation *anim, Gauntlet::State *state);
    void                                animationRevive(Gauntlet::Animation *anim);
  };
};

#endif //ANIMATIONMANAGER_HPP
