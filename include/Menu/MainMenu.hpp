//
// Created by puentes on 12/06/17.
//

#ifndef INDIE_MAINMENU_HPP
#define INDIE_MAINMENU_HPP

#include <CEGUI/CEGUI.h>
#include "Menu/IMenu.hpp"

namespace Gauntlet
{
  class MainMenu: public IMenu
  {
   private:
    class	MainSelect: public IMenu
    {
     private:
      CEGUI::Window			*_root;
      CEGUI::Window			*_cursor;

      std::vector<CEGUI::Window*>	_menuEntries;

      unsigned int			_idx;

      void 				validateMenu();
      void 				updateButtonSize();
     public:
      MainSelect(CEGUI::Window *root);
      virtual ~MainSelect();

      virtual void			updateMenu();
      virtual void			setActive(bool active);
      virtual void			show(bool isShowed);
      virtual void			takeEvent(Gauntlet::Event const &event);
    };

    class	PlayerSelect: public IMenu
    {
     private:
      CEGUI::Window			*_root;

      CEGUI::Window			*_label;
      CEGUI::Window			*_left;
      CEGUI::Window			*_right;
      unsigned int			_playerNum;

      void				updatePlayer();
     public:
      PlayerSelect(CEGUI::Window *root);
      virtual ~PlayerSelect();

      virtual void			updateMenu();
      virtual void			setActive(bool active);
      virtual void			show(bool isShowed);
      virtual void			takeEvent(Gauntlet::Event const &event);
    };

    class	HighScore: public IMenu
    {
     private:
      CEGUI::Window			*_root;
      std::vector<CEGUI::Window*>	_scoreEntries;

     public:
      HighScore(CEGUI::Window *root);
      virtual ~HighScore();

      virtual void			updateMenu();
      virtual void			setActive(bool active);
      virtual void			show(bool isShowed);
      virtual void			takeEvent(Gauntlet::Event const &event);
    };

    class	Settings: public IMenu
    {
     private:
      CEGUI::Window			*_root;
      CEGUI::Window			*_cursor;
      std::vector<CEGUI::Window*>	_optionEntries;
      unsigned int			_idx;

      void				validateMenu();
      void 				updateButtonSize();
      void				handleMoveMenu(Gauntlet::MoveEvent const &move);
      void				updateSound(bool up);
     public:
      Settings(CEGUI::Window *root);
      virtual ~Settings();

      virtual void			updateMenu();
      virtual void			setActive(bool active);
      virtual void			show(bool isShowed);
      virtual void			takeEvent(Gauntlet::Event const &event);
    };

    CEGUI::Window			*_root;
   public:
    MainMenu();
    virtual ~MainMenu();

    virtual void			updateMenu();
    virtual void			takeEvent(Gauntlet::Event const &event);
    virtual void			show(bool isShowed);
  };
}

#endif //INDIE_MAINMENU_HPP
