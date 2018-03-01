//
// Hud.hpp for  in /home/myriam/Projet/cpp_indie_studio
// 
// Made by Myriam
//

#ifndef HUD_HPP_
# define HUD_HPP_

# include <CEGUI/CEGUI.h>
# include <CEGUI/RendererModules/Ogre/Renderer.h>
# include <memory>

# include "Menu/IMenu.hpp"
# include "Components/Stats.hpp"
# include "Entity/Entity.hpp"

namespace	Gauntlet
{
  struct 	PlayerHudData
  {
    PlayerHudData(CEGUI::Window *life,
		  CEGUI::Window *stamina,
		  Gauntlet::Entity *hero);

    CEGUI::Window	*life;
    CEGUI::Window	*stamina;
    Gauntlet::Entity	*hero;
    Gauntlet::Stats	*stats;
  };

  class		Hud : public	Gauntlet::IMenu
  {
  public:
    Hud(std::vector<std::shared_ptr<Gauntlet::Entity> > const &heroes);
    virtual ~Hud();

    void					updateMenu();
    void					takeEvent(Gauntlet::Event const &event);
    void					show(bool isShowed);
    void 					setActive(bool active);
    void					initStats(std::vector<std::shared_ptr<Entity>> const &heroes);
    void					bossHud(Gauntlet::Event const &event);
   private:
    CEGUI::Window				*_root;
    std::vector<Gauntlet::PlayerHudData>	_player;
    CEGUI::Window				*_score;

    std::string					getNewBar(int value) const;
    std::string					getNewBarBoss(int value) const;
    CEGUI::Window				*_text;
    std::string					levelstr;
    void					newLevel();
  };
}

#endif
