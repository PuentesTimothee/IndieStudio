//
// KeyListener.cpp for Indie studio in /home/mymy/Modules/C++/cpp_indie_studio/src/Displayer
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May  9 19:15:59 2017 Mymy Aragon
// Last update Mon Jun 12 09:57:47 2017 benito
//

#include <CEGUI/System.h>
#include "Systems/Displayer/WindowManager.hpp"
#include "CoreGame.hpp"

Gauntlet::WindowManager::WindowManager(Ogre::RenderWindow *win,
				       Ogre::SceneManager *sceneMgr,
				       Gauntlet::AnimationManager& animationManagerOri)
	: win(win),
	  sceneMgr(sceneMgr),
	  animationManager(animationManagerOri),
      _quit(false)
{
}

Gauntlet::WindowManager::~WindowManager()
{
  Ogre::WindowEventUtilities::removeWindowEventListener(this->win, this);
  this->windowClosed(this->win);
}

void		Gauntlet::WindowManager::windowClosed(Ogre::RenderWindow *)
{
}

bool		Gauntlet::WindowManager::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
  if (this->win->isClosed() || this->_quit)
    return (false);

  Gauntlet::CoreGame::frameRate = evt.timeSinceLastFrame;

  CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
  Gauntlet::CoreGame::core->gameTurn();
  return (true);
}


void		Gauntlet::WindowManager::takeEvent(Gauntlet::Event const &event)
{
    if (event._type == Gauntlet::EventType::QUIT) {
        this->_quit = true;
    }
}

