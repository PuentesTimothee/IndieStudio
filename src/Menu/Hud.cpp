//
// Hud.cpp for  in /home/myriam/Projet/cpp_indie_studio
// 
// Made by Myriam
//

#include "CoreGame.hpp"
#include "Menu/Hud.hpp"

Gauntlet::Hud::Hud(std::vector<std::shared_ptr<Gauntlet::Entity> > const &heroes)
	: IMenu(Gauntlet::MenuType::HUD),
	  _root(nullptr),
	  _player(),
	  _score(nullptr),
	  _text(nullptr),
	  levelstr("Level I")
{
  CEGUI::WindowManager	&mgr = CEGUI::WindowManager::getSingleton();

  this->_root = mgr.loadLayoutFromFile("GameHUD.layout");
  this->_score = this->_root->getChild("ScoreBox")->getChild("Score");
  this->_text = this->_root->getChild("LevelText");
  this->initStats(heroes);
  
  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(this->_root);

  this->setActive(false);
  this->show(false);
}

Gauntlet::Hud::~Hud()
{
  
}

std::string	Gauntlet::Hud::getNewBar(int value) const
{
  std::string	str = "{{0, ";
  std::string	end = "}, {0, 10}}";

  str += std::to_string(value);
  str += end;
  return (str);
}

void			Gauntlet::Hud::initStats(std::vector<std::shared_ptr<Gauntlet::Entity>> const &heroes)
{
  CEGUI::Window		*life;
  CEGUI::Window		*stamina;
  uint 			compt = 0;

  this->_player.clear();

  for (auto const & hero : heroes)
    {
      stamina = this->_root->getChild(compt)->getChild("StaminaBar");
      life = this->_root->getChild(compt)->getChild("LifeBar");
      this->_player.emplace_back(life, stamina, hero.get());
      compt++;
    }
}

void			Gauntlet::Hud::updateMenu()
{
  for (auto const & hero : this->_player)
    {
      hero.life->setProperty("Size",
			     getNewBar((140 * hero.stats->life) / hero.stats->lifeMax));
      hero.stamina->setProperty("Size",
				getNewBar((140 * hero.stats->stamina) / hero.stats->staminaMax));
    }
  this->_score->setProperty("Text", std::to_string(Gauntlet::CoreGame::score));
}

void			Gauntlet::Hud::takeEvent(Gauntlet::Event const &event)
{
  if (Gauntlet::CoreGame::core->isMenuOn)
    return ;

  switch (event._type)
    {
    case (Gauntlet::EventType::MENU):
      Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::GAME_MENU, true);
      break;
    case (Gauntlet::EventType::LEVEL_END):
      this->newLevel();
      break;
    default:
      break;
    }
}

void Gauntlet::Hud::show(bool isShowed)
{
  if (isShowed)
    {
      this->_root->show();
    }
  else
    this->_root->hide();
}

Gauntlet::PlayerHudData::PlayerHudData(CEGUI::Window *paramLife,
				       CEGUI::Window *paramStamina,
				       Gauntlet::Entity *paramHero)
	: life(paramLife),
	  stamina(paramStamina),
	  hero(paramHero),
	  stats(nullptr)
{
  this->stats = this->hero->getPtr<Gauntlet::Stats>();
}

void		Gauntlet::Hud::newLevel()
{
  this->levelstr += "I";
  this->_text->setProperty("Text", this->levelstr);
}

void		Gauntlet::Hud::setActive(bool active)
{
  if (!active)
    {
      this->levelstr = "Level I";
      this->_text->setProperty("Text", this->levelstr);
    }
  IMenu::setActive(active);
}
