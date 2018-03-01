//
// endGame.hpp for  in /home/myriam/Projet/cpp_indie_studio
// 
// Made by Myriam
//

#ifndef ENDGAME_HPP_
# define ENDGAME_HPP_

# include <CEGUI/CEGUI.h>
# include <CEGUI/RendererModules/Ogre/Renderer.h>
# include "Menu/IMenu.hpp"

namespace	Gauntlet
{
  class		EndGame : public Gauntlet::IMenu
  {
  public:
    EndGame();
    virtual ~EndGame();

    void		takeEvent(Gauntlet::Event const &event);
    void	 	show(bool isShowed);
    void		victoryScreen();
    void		defeatScreen();
      void		updateMenu();

  private:
    CEGUI::Window	*_rootDefeat;
    CEGUI::Window       *_rootVictory;
    CEGUI::Window       *_root;
  };
}

#endif
