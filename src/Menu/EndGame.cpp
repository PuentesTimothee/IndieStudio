//
// endGame.cpp for  in /home/myriam/Projet/cpp_indie_studio
// 
// Made by Myriam
//

#include <CoreGame.hpp>
#include "Menu/EndGame.hpp"

Gauntlet::EndGame::EndGame()
        : IMenu(Gauntlet::MenuType::ENDGAME),
	  _rootDefeat(nullptr),
	  _rootVictory(nullptr),
	  _root(nullptr)
{
  CEGUI::WindowManager	&winMgr = CEGUI::WindowManager::getSingleton();

  this->_rootVictory = winMgr.loadLayoutFromFile("Victory.layout");
  this->_rootDefeat = winMgr.loadLayoutFromFile("Defeat.layout");

  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(this->_rootDefeat);
  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(this->_rootVictory);
  this->_rootDefeat->hide();
  this->_rootVictory->hide();
  this->_root = this->_rootDefeat;
  this->show(false);
}

Gauntlet::EndGame::~EndGame()
{

}

void			Gauntlet::EndGame::takeEvent(Gauntlet::Event const &event)
{
  switch (event._type)
    {
      case (Gauntlet::EventType::MENU) :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::MAIN_MENU, true);
      Gauntlet::CoreGame::core->addEvent(EventType::MAIN_MENU);
      Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::ENDGAME, false);
      Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::HUD, false);
      break;
      case (Gauntlet::EventType::VICTORY):
	this->victoryScreen();
      break;
      case (Gauntlet::EventType::DEFEAT):
	this->defeatScreen();
      break;
      default:
	break;
    }
}

void            Gauntlet::EndGame::victoryScreen()
{
  this->_root = _rootVictory;
  this->_rootDefeat->hide();
  this->_root->show();
}

void            Gauntlet::EndGame::defeatScreen()
{
  this->_root = _rootDefeat;
  this->_rootVictory->hide();
  this->_root->show();
}

void            Gauntlet::EndGame::show(bool isShowed)
{
  if (isShowed)
    {
      this->_root->show();
    }
  else
    this->_root->hide();
}

void            Gauntlet::EndGame::updateMenu()
{

}