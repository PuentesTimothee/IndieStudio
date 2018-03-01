//
// WindowManager.hpp for Indie studio in /home/mymy/Modules/C++/cpp_indie_studio/include
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May  9 19:04:19 2017 Mymy Aragon
// Last update Thu May 11 16:25:07 2017 Mymy Aragon
//

#ifndef WINDOW_MANAGER_HPP_
# define WINDOW_MANAGER_HPP_

#include <Ogre.h>
#include <OIS/OIS.h>
#include <memory>

#include "Systems/Animation/AnimationManager.hpp"
#include "Systems/Input/InputManager.hpp"

namespace Gauntlet
{
  class	WindowManager : public System, public Ogre::FrameListener, Ogre::WindowEventListener
  {
   private:
      Ogre::RenderWindow				*win;
      Ogre::SceneManager				*sceneMgr;
    
      Gauntlet::AnimationManager&			animationManager;

      bool _quit;

  public:
    WindowManager(Ogre::RenderWindow *win,
		  Ogre::SceneManager *sceneMgr,
		  Gauntlet::AnimationManager& animationManager);
    ~WindowManager();

      virtual void		takeEvent(Gauntlet::Event const &event) override ;

   private:
      void		windowClosed(Ogre::RenderWindow *rw);
      bool		frameRenderingQueued(const Ogre::FrameEvent &evt);
  };
}

#endif /* !WINDOW_MANAGER_HPP_ */
