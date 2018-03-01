//
// Created by puentes on 11/06/17.
//

#include "Menu/GameMenu.hpp"

Gauntlet::GameMenu::GameMenu()
	: IMenu(Gauntlet::MenuType::GAME_MENU),
	  _root(nullptr),
	  _menuEntries(),
	  _idx(0)
{
  CEGUI::WindowManager	&winMgr = CEGUI::WindowManager::getSingleton();

  this->_root = winMgr.loadLayoutFromFile("GameMenu.layout");
  auto menu = this->_root->getChild("Menu");
  for (unsigned int id = 0; id < 2; id++)
    this->_menuEntries.push_back(menu->getChild(200 + id)->getChild(0));

  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(this->_root);

  this->setActive(false);
}

Gauntlet::GameMenu::~GameMenu()
{

}

void		Gauntlet::GameMenu::updateMenu()
{
}

void		Gauntlet::GameMenu::takeEvent(Gauntlet::Event const &event)
{
  switch (event._type)
    {
      case (Gauntlet::EventType::MENU) :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::HUD, true);
      Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::GAME_MENU, false);
      break;
      case (Gauntlet::EventType::MOVE) :
    	{
	      auto const &move = static_cast<MoveEvent const &>(event);
        /* segfault ici, pas de front */
          if (move.type.size() > 0)
          {
              if (move.type.front() == MoveEvent::Type::UP &&
                  this->_idx > 0)
                  this->_idx--;
              else if (move.type.front() == MoveEvent::Type::DOWN &&
                       this->_idx + 1 < this->_menuEntries.size())
                  this->_idx += 1;
              this->updateButtonSize();
          }
	}
      break;
      case (Gauntlet::EventType::ENTER) :
	this->validateMenu();
      break;
      default:
	break;
    }
}

void		Gauntlet::GameMenu::show(bool isShowed)
{
  if (isShowed)
    {
      this->_root->show();
      this->_idx = 0;
      this->updateButtonSize();
    }
  else
    this->_root->hide();
}

void		Gauntlet::GameMenu::updateButtonSize()
{
  this->_menuEntries[this->_idx]->setProperty("Font", "Runic-MT-20");
  if (this->_idx > 0)
    this->_menuEntries[this->_idx - 1]->setProperty("Font", "Runic-MT-18");
  if (this->_idx < this->_menuEntries.size() - 1)
    this->_menuEntries[this->_idx + 1]->setProperty("Font", "Runic-MT-18");
}

void		Gauntlet::GameMenu::validateMenu() const
{
  switch(this->_idx)
    {
      case 0 :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::HUD, true);
      Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::GAME_MENU, false);
      break;
      case 1 :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::MAIN_MENU, true);
      Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::GAME_MENU, false);
      Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::HUD, false);
      Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::MAIN_MENU);
      break;
      default :
	break;
    }
}