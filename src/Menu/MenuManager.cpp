//
// menu.cpp for  in /home/myriam/Projet/cpp_indie_studio/menu
// 
// Made by Myriam
//

#include <CoreGame.hpp>
#include "Menu/MenuManager.hpp"

Gauntlet::MenuManager::MenuManager()
	: mRenderer(),
	  _root(nullptr)
{
  this->mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

  CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

  CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");
  CEGUI::SchemeManager::getSingleton().createFromFile("Gauntlet.scheme");

  CEGUI::WindowManager	&winMgr = CEGUI::WindowManager::getSingleton();

  this->_root = winMgr.createWindow("DefaultWindow", "Root");
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(this->_root);
}

Gauntlet::MenuManager::~MenuManager()
{
  for (auto & menu : this->_menus)
    menu.reset();

  CEGUI::OgreRenderer::destroy(static_cast<CEGUI::OgreRenderer&>(*mRenderer));
}

void			Gauntlet::MenuManager::takeEvent(Event const &event)
{
  switch (event._type)
    {
      case (Gauntlet::EventType::VICTORY) :
	this->setActiveMenu(Gauntlet::MenuType::ENDGAME, true);
      break;
      case (Gauntlet::EventType::DEFEAT) :
	this->setActiveMenu(Gauntlet::MenuType::ENDGAME, true);
      break;
      default:
	break;
    }
  for (auto &menu : this->_menus)
    {
      if (menu->getActive())
	menu->takeEvent(event);
    }
}


void			Gauntlet::MenuManager::updateMenu()
{
  for (auto &menu : this->_menus)
    {
      if (menu->getActive())
	menu->updateMenu();
    }
}

void			Gauntlet::MenuManager::addHud(std::vector<std::shared_ptr<Gauntlet::Entity> > const &heroes)
{
  Gauntlet::IMenu	*hud;

  if ((hud = this->getMenu(Gauntlet::MenuType::HUD)) != nullptr)
    static_cast<Gauntlet::Hud*>(hud)->initStats(heroes);
  else
    this->_menus.emplace_back(new Gauntlet::Hud(heroes));
}

void			Gauntlet::MenuManager::addGameMenu()
{
  if (this->getMenu(Gauntlet::MenuType::GAME_MENU) == nullptr)
    this->_menus.emplace_back(new Gauntlet::GameMenu());
}

void			Gauntlet::MenuManager::addEndGame()
{
  if (this->getMenu(Gauntlet::MenuType::ENDGAME) == nullptr)
    this->_menus.emplace_back(new Gauntlet::EndGame());
}

void			Gauntlet::MenuManager::addMainMenu()
{
  if (this->getMenu(Gauntlet::MenuType::MAIN_MENU) == nullptr)
    this->_menus.emplace_back(new Gauntlet::MainMenu());
}

void                    Gauntlet::MenuManager::addSplashScreen()
{
  if (this->getMenu(Gauntlet::MenuType::SPLASHSCREEN) == nullptr)
    this->_menus.emplace_back(new Gauntlet::SplashScreen());
}

bool			Gauntlet::MenuManager::setActiveMenu(Gauntlet::MenuType const &menuType, bool active)
{
  bool 			isMenuOn;

  switch (menuType)
    {
      case (Gauntlet::MenuType::HUD) :
	isMenuOn = false;
      break;
      default:
	isMenuOn = true;
      break;
    }

  for (auto & subMenu : this->_menus)
    {
      if (subMenu->getMenu(menuType))
	{
	  subMenu->setActive(active);
	  subMenu->setActiveMenu(menuType, active);
	  if (active)
	    Gauntlet::CoreGame::core->isMenuOn = isMenuOn;
	  return (true);
	}
    }
  return (false);
}

bool				Gauntlet::MenuManager::showMenu(Gauntlet::MenuType const &menuType, bool show)
{
  for (auto & menu : this->_menus)
    {
      if (menu->getMenuType() == menuType)
	{
	  menu->show(show);
	  return (true);
	}
    }
  return (false);
}

Gauntlet::IMenu			*Gauntlet::MenuManager::getMenu(Gauntlet::MenuType const &menuType)
{
  for (auto & menu : this->_menus)
    if (menu->getMenuType() == menuType)
      return (menu.get());
  return (nullptr);
}