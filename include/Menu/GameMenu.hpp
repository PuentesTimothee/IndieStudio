//
// Created by puentes on 11/06/17.
//

#ifndef INDIE_GAMEMENU_HPP
#define INDIE_GAMEMENU_HPP

#include <CEGUI/CEGUI.h>

#include "CoreGame.hpp"
#include "Menu/IMenu.hpp"

namespace	Gauntlet
{
  class		GameMenu : public	Gauntlet::IMenu
  {
   private:
    CEGUI::Window			*_root;
    std::vector<CEGUI::Window*>		_menuEntries;
    unsigned int 			_idx;

    void 				validateMenu() const;
    void 				updateButtonSize();
   public:
   GameMenu();
    virtual ~GameMenu();

   void					updateMenu();
   void					takeEvent(Gauntlet::Event const &event);
   void					show(bool isShowed);
  };
}

#endif //INDIE_GAMEMENU_HPP
