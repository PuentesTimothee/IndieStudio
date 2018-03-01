//
// Created by mymy on 16/06/17.
//

#include "Menu/SplashScreen.hpp"

Gauntlet::SplashScreen::SplashScreen() :
	IMenu(Gauntlet::MenuType::SPLASHSCREEN),
	_root(nullptr),
	hasUpdateOnce(false)
{
  CEGUI::WindowManager	&mgr = CEGUI::WindowManager::getSingleton();

  this->_root = mgr.loadLayoutFromFile("SplashScreen.layout");

  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(this->_root);

  this->setActive(false);
}

void            Gauntlet::SplashScreen::updateMenu()
{
  if (!this->hasUpdateOnce)
    {
      this->hasUpdateOnce = true;
    }
  else
    {
      std::this_thread::sleep_for(std::chrono::seconds(3));
      Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::MAIN_MENU);
      Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::SPLASHSCREEN, false);
      Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::MAIN_MENU, true);
    }
}

void		Gauntlet::SplashScreen::show(bool isShowed)
{
  if (isShowed)
    {
      this->_root->show();
    }
  else
    this->_root->hide();
}