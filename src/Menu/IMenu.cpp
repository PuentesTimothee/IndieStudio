//
// Created by puentes on 11/06/17.
//

#include "Menu/IMenu.hpp"

Gauntlet::IMenu::IMenu(Gauntlet::MenuType menuType, bool active)
	: _menuType(menuType),
	  _active(active)
{

}

void		Gauntlet::IMenu::setActive(bool active)
{
  this->_active = active;
  this->show(active);
}

bool		Gauntlet::IMenu::getActive() const
{
  return (this->_active);
}

void		Gauntlet::IMenu::takeEvent(Gauntlet::Event const &event)
{
  for (auto & subMenu : this->_subMenus)
    {
      if (subMenu->getActive())
	subMenu->takeEvent(event);
    }
}

void		Gauntlet::IMenu::updateMenu()
{
  for (auto & subMenu : this->_subMenus)
    {
      if (subMenu->getActive())
	subMenu->updateMenu();
    }
}

void		Gauntlet::IMenu::show(bool)
{
}

Gauntlet::IMenu	*Gauntlet::IMenu::getMenu(Gauntlet::MenuType menuType)
{
  if (this->_menuType == menuType)
    return (this);

  for (auto & subMenu : this->_subMenus)
    {
      Gauntlet::IMenu	*tmp;
      if ((tmp = subMenu->getMenu(menuType)) != nullptr)
	return (tmp);
    }
  return (nullptr);
}

bool		Gauntlet::IMenu::setActiveMenu(Gauntlet::MenuType menuType, bool active)
{
  if (this->_menuType == menuType)
    {
      this->setActive(active);
      return (true);
    }
  for (auto & subMenu : this->_subMenus)
    {
      if (subMenu->getMenu(menuType))
	{
	  subMenu->setActive(active);
	  subMenu->setActiveMenu(menuType, active);
	  return (true);
	}
    }
  return (false);
}

bool		Gauntlet::IMenu::showMenu(Gauntlet::MenuType menuType, bool show)
{
  if (this->_menuType == menuType)
    {
      this->show(show);
      return (true);
    }
  for (auto & subMenu : this->_subMenus)
    {
      if (subMenu->getMenu(menuType))
	{
	  subMenu->show(show);
	  return (true);
	}
    }
  return (false);
}
