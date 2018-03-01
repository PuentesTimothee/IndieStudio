//
// Created by puentes on 11/06/17.
//

#ifndef INDIE_IMENU_HPP
#define INDIE_IMENU_HPP

#include "Event/Event.hpp"

namespace Gauntlet
{
  enum		MenuType : int
  {
    DEFAULT = 0,
    MAIN_MENU,
    MAIN_SELECT,
    PLAYER_SELECT,
    HIGHSCORE,
    SETTINGS,
    GAME_MENU,
    HUD,
    ENDGAME,
    SPLASHSCREEN
  };

  class IMenu
  {
   protected:
    Gauntlet::MenuType					_menuType;
    std::vector<std::unique_ptr<Gauntlet::IMenu> >	_subMenus;
    bool						_active;

   public:
    Gauntlet::MenuType 	getMenuType() const { return (this->_menuType); };

    IMenu(Gauntlet::MenuType menuType, bool active = false);
    virtual ~IMenu() {};

    virtual void 		updateMenu();
    virtual void 		show(bool isShowed = true);

    virtual void 		takeEvent(Gauntlet::Event const &);
    virtual Gauntlet::IMenu	*getMenu(Gauntlet::MenuType menuType);
    virtual bool		setActiveMenu(Gauntlet::MenuType menuType, bool active);

    virtual bool		getActive() const;
    virtual void		setActive(bool active);
    virtual bool 		showMenu(Gauntlet::MenuType menuType, bool show);
  };
}

#endif //INDIE_IMENU_HPP
