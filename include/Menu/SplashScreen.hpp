//
// Created by mymy on 16/06/17.
//

#ifndef INDIE_SPLASHSCREEN_HPP
#define INDIE_SPLASHSCREEN_HPP

#include <CEGUI/CEGUI.h>
#include <CoreGame.hpp>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "IMenu.hpp"

namespace Gauntlet
{
  class SplashScreen : public Gauntlet::IMenu
  {
    CEGUI::Window			*_root;
    bool                                hasUpdateOnce;
   public:
    SplashScreen();
    virtual ~SplashScreen() {};

    virtual void			show(bool isShowed);
    virtual void                        updateMenu();
  };
}


#endif //INDIE_SPLASHSCREEN_HPP
