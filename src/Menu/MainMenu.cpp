//
// Created by puente	s on 12/06/17.
//

#include "Menu/MainMenu.hpp"
#include "CoreGame.hpp"

Gauntlet::MainMenu::MainMenu()
	: IMenu(Gauntlet::MenuType::MAIN_MENU),
	  _root(nullptr)
{
  CEGUI::WindowManager	&winMgr = CEGUI::WindowManager::getSingleton();

  this->_root = winMgr.loadLayoutFromFile("MainMenu.layout");
  this->_subMenus.emplace_back(new Gauntlet::MainMenu::PlayerSelect(this->_root->getChild("Menu")));
  this->_subMenus.emplace_back(new Gauntlet::MainMenu::MainSelect(this->_root->getChild("Menu")));
  this->_subMenus.emplace_back(new Gauntlet::MainMenu::Settings(this->_root->getChild("Menu")));
  this->_subMenus.emplace_back(new Gauntlet::MainMenu::HighScore(this->_root->getChild("Menu")));

  this->setActiveMenu(Gauntlet::MenuType::MAIN_SELECT, true);
  Gauntlet::CoreGame::core->addEvent(EventType::MENU);
  this->setActiveMenu(Gauntlet::MenuType::PLAYER_SELECT, false);
  this->setActiveMenu(Gauntlet::MenuType::HIGHSCORE, false);
  this->setActive(false);

  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(this->_root);

  this->setActive(false);
}

Gauntlet::MainMenu::~MainMenu()
{

}

void		Gauntlet::MainMenu::takeEvent(Gauntlet::Event const &event)
{
  for (auto & subMenu : this->_subMenus)
    {
      if (subMenu->getActive())
	subMenu->takeEvent(event);
    }
}

void		Gauntlet::MainMenu::updateMenu()
{
  for (auto &subMenu : this->_subMenus)
    {
      if (subMenu->getActive())
	subMenu->updateMenu();
    }
}

void		Gauntlet::MainMenu::show(bool isShowed)
{
  if (isShowed)
    {
      this->setActiveMenu(Gauntlet::MenuType::HIGHSCORE, false);
      this->setActiveMenu(Gauntlet::MenuType::PLAYER_SELECT, false);
      this->setActiveMenu(Gauntlet::MenuType::SETTINGS, false);
      this->setActiveMenu(Gauntlet::MenuType::MAIN_SELECT, true);
      this->_root->show();
    }
  else
    {
      this->_root->hide();
      this->setActiveMenu(Gauntlet::MenuType::HIGHSCORE, false);
      this->setActiveMenu(Gauntlet::MenuType::PLAYER_SELECT, false);
      this->setActiveMenu(Gauntlet::MenuType::SETTINGS, false);
      this->setActiveMenu(Gauntlet::MenuType::MAIN_SELECT, true);
    }
}

Gauntlet::MainMenu::PlayerSelect::PlayerSelect(CEGUI::Window *root)
	: IMenu(Gauntlet::MenuType::PLAYER_SELECT),
	  _root(nullptr),
	  _label(nullptr),
	  _left(nullptr),
	  _right(nullptr),
	  _playerNum(1)
{
  CEGUI::WindowManager	&winMgr = CEGUI::WindowManager::getSingleton();

  this->_root = winMgr.loadLayoutFromFile("PlayerSelect.layout");
  root->addChild(this->_root);

  this->_label = this->_root->getChild("PlayerNumber")->getChild("Label");

  this->_left = this->_root->getChild("CursorLeft");
  this->_right = this->_root->getChild("CursorRight");
  this->setActive(false);
}

Gauntlet::MainMenu::PlayerSelect::~PlayerSelect()
{
}

void		Gauntlet::MainMenu::PlayerSelect::updateMenu()
{
}

void		Gauntlet::MainMenu::PlayerSelect::show(bool isShowed)
{
  if (isShowed)
    this->_root->show();
  else
    this->_root->hide();
}

void		Gauntlet::MainMenu::PlayerSelect::takeEvent(Gauntlet::Event const &event)
{
  switch (event._type)
    {
      case (Gauntlet::EventType::MENU) :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::MAIN_SELECT, true);
      Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::MENU);
      this->setActive(false);
      break;
      case (Gauntlet::EventType::ENTER) :
	Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::NEW_GAME);
      break;
      case (Gauntlet::EventType::MOVE) :
	{
	  auto const &move = static_cast<MoveEvent const &>(event);
	  if ((move.type.front() == MoveEvent::Type::DOWN ||
	       move.type.front() == MoveEvent::Type::LEFT) && this->_playerNum> 1)
	    this->_playerNum--;
	  else if ((move.type.front() == MoveEvent::Type::DOWN ||
		    move.type.front() == MoveEvent::Type::RIGHT) &&
		   this->_playerNum < 4)
	      this->_playerNum++;
	this->updatePlayer();
	}
      break;
      default:
	break;
    }
}

void		Gauntlet::MainMenu::PlayerSelect::setActive(bool active)
{
  IMenu::setActive(active);
}

void		Gauntlet::MainMenu::PlayerSelect::updatePlayer()
{
  this->_label->setText("Player: " + std::to_string(this->_playerNum));
  Gauntlet::CoreGame::numberOfPlayer = this->_playerNum;
}

Gauntlet::MainMenu::MainSelect::MainSelect(CEGUI::Window *root)
	: IMenu(Gauntlet::MenuType::MAIN_SELECT),
	  _root(nullptr),
	  _cursor(nullptr),
	  _menuEntries(),
	  _idx(0)
{
  CEGUI::WindowManager	&winMgr = CEGUI::WindowManager::getSingleton();

  this->_root = winMgr.loadLayoutFromFile("MainSelect.layout");
  root->addChild(this->_root);

  for (unsigned int id = 0; id < 4; id++)
    this->_menuEntries.push_back(this->_root->getChild(id));
  this->_cursor = this->_root->getChild(101);

  this->setActive(false);
}

Gauntlet::MainMenu::MainSelect::~MainSelect()
{
}

void		Gauntlet::MainMenu::MainSelect::updateMenu()
{
}

void		Gauntlet::MainMenu::MainSelect::show(bool isShowed)
{
  if (isShowed)
    {
      this->_idx = 0;
      this->updateButtonSize();
      this->_root->show();
    }
  else
    this->_root->hide();
}

void		Gauntlet::MainMenu::MainSelect::takeEvent(Gauntlet::Event const &event)
{
  switch (event._type)
    {
      case (Gauntlet::EventType::MOVE) :
	{
	  auto const &move = static_cast<MoveEvent const &>(event);
	  if (move.type.front() == MoveEvent::Type::UP &&
	      this->_idx > 0)
	    this->_idx--;
	  else if (move.type.front() == MoveEvent::Type::DOWN &&
		    this->_idx + 1 < this->_menuEntries.size())
	      this->_idx += 1;
	  this->updateButtonSize();
	}
      break;
      case (Gauntlet::EventType::ENTER) :
	this->validateMenu();
      break;
      default:
	break;
    }
}

void		Gauntlet::MainMenu::MainSelect::validateMenu()
{
  switch(this->_idx)
    {
      case 0 :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::PLAYER_SELECT, true);
      this->setActive(false);
      break;
      case 1 :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::SETTINGS, true);
      this->setActive(false);
	break;
      case 2 :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::HIGHSCORE, true);
      this->setActive(false);
      break;
      case 3 :
	Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::QUIT);
      break;
      default :
	break;
    }
}

void		Gauntlet::MainMenu::MainSelect::updateButtonSize()
{
  for (auto & entry : this->_menuEntries)
    {
      entry->setProperty("Font", "Runic-MT-20");
      entry->setProperty("NormalTextColour", "FF000000");
    }

  this->_menuEntries[this->_idx]->setProperty("Font", "Runic-MT-28");
  this->_menuEntries[this->_idx]->setProperty("NormalTextColour", "FFFFFFFF");
  this->_cursor->setArea(this->_menuEntries[this->_idx]->getArea());
}

void		Gauntlet::MainMenu::MainSelect::setActive(bool active)
{
  this->_active = active;
  this->show(active);
}

Gauntlet::MainMenu::HighScore::HighScore(CEGUI::Window *root)
	: IMenu(Gauntlet::MenuType::HIGHSCORE),
	  _root(nullptr),
	  _scoreEntries()
{
  CEGUI::WindowManager	&winMgr = CEGUI::WindowManager::getSingleton();

  this->_root = winMgr.loadLayoutFromFile("HighScore.layout");
  root->addChild(this->_root);

  for (unsigned int id = 1; id < 10; id++)
    this->_scoreEntries.push_back(this->_root->getChild(id));
  this->setActive(false);
}

Gauntlet::MainMenu::HighScore::~HighScore()
{

}

void		Gauntlet::MainMenu::HighScore::updateMenu()
{
  try
    {
      std::vector<int> score;
      unsigned int c = 0;

      Gauntlet::Saving::fillScores(score);
      std::sort(score.begin(), score.end(), std::greater<int>());
      for (auto const &scoreEntry : this->_scoreEntries)
	{
	  if (c < score.size())
	    scoreEntry->setProperty("Text", std::to_string(score[c]));
	  else
	    scoreEntry->setProperty("Text", "");
	  c++;
	}
    }
  catch (std::exception const & e)
    {
      std::cerr << e.what() << std::endl;
    }
}

void		Gauntlet::MainMenu::HighScore::setActive(bool active)
{
  this->_active = active;
  this->show(active);
}

void		Gauntlet::MainMenu::HighScore::show(bool isShowed)
{
  if (isShowed)
    this->_root->show();
  else
    this->_root->hide();
}

void		Gauntlet::MainMenu::HighScore::takeEvent(Gauntlet::Event const &event)
{
  switch (event._type)
    {
      case (Gauntlet::EventType::MENU) :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::MAIN_SELECT, true);
      this->setActive(false);
      break;
      default:
	break;
    }
}

Gauntlet::MainMenu::Settings::Settings(CEGUI::Window *root)
	: IMenu(Gauntlet::MenuType::SETTINGS),
	  _root(nullptr),
	  _cursor(nullptr),
	  _optionEntries(),
	  _idx(0)
{
  CEGUI::WindowManager	&winMgr = CEGUI::WindowManager::getSingleton();

  this->_root = winMgr.loadLayoutFromFile("Settings.layout");
  root->addChild(this->_root);

  this->_cursor = this->_root->getChild("Cursor");

  for (unsigned int id = 0; id < 3; id++)
    this->_optionEntries.push_back(this->_root->getChild(100 + id));
  this->setActive(false);
}

Gauntlet::MainMenu::Settings::~Settings()
{

}

void		Gauntlet::MainMenu::Settings::updateMenu()
{
  int		actualVol;

  actualVol = (Gauntlet::CoreGame::core->getSoundMgr().getMusicVolume());
  this->_root->getChild(10)->getChild(2)->setProperty("Text", std::to_string(actualVol));
  this->_root->getChild(10)->getChild(1)->getChild(101)->setSize(CEGUI::USize(CEGUI::UDim(actualVol / 100.0f, 0),
									       CEGUI::UDim(1, 0)));

  actualVol = (Gauntlet::CoreGame::core->getSoundMgr().getSoundVolume());
  this->_root->getChild(11)->getChild(2)->setProperty("Text", std::to_string(actualVol));
  this->_root->getChild(11)->getChild(1)->getChild(101)->setSize(CEGUI::USize(CEGUI::UDim(actualVol / 100.0f, 0),
									       CEGUI::UDim(1, 0)));
}

void		Gauntlet::MainMenu::Settings::setActive(bool active)
{
  this->_active = active;
  this->show(active);
}

void		Gauntlet::MainMenu::Settings::show(bool isShowed)
{
  if (isShowed)
    {
      this->_root->show();
      this->_idx = 0;
    }
  else
    this->_root->hide();
}

void		Gauntlet::MainMenu::Settings::takeEvent(Gauntlet::Event const &event)
{

  switch (event._type)
    {
      case (Gauntlet::EventType::MOVE) :
	this->handleMoveMenu(static_cast<MoveEvent const &>(event));
      break;
      case (Gauntlet::EventType::ENTER) :
	this->validateMenu();
      break;
      default:
	break;
    }
}

void	Gauntlet::MainMenu::Settings::handleMoveMenu(Gauntlet::MoveEvent const & move)
{
  switch (move.type.front())
    {
      case (MoveEvent::Type::UP):
	if (this->_idx <= 0)
	  return;
      this->_idx--;
      this->updateButtonSize();
      return;
      case (MoveEvent::Type::DOWN):
	if (this->_idx + 1 >= this->_optionEntries.size())
	return ;
      this->_idx += 1;
      this->updateButtonSize();
      return;
      case (MoveEvent::Type::LEFT):
	this->updateSound(false);
	return ;
      case (MoveEvent::Type::RIGHT):
	this->updateSound(true);
	return ;
      default :
      return ;
    }
}

void		Gauntlet::MainMenu::Settings::validateMenu()
{
  switch(this->_idx)
    {
      case 2 :
	Gauntlet::CoreGame::core->getMenuMgr().setActiveMenu(Gauntlet::MenuType::MAIN_SELECT, true);
      this->setActive(false);
      break;
      default :
	break;
    }
}

void		Gauntlet::MainMenu::Settings::updateButtonSize()
{
  for (auto & entry : this->_optionEntries)
    {
      entry->setProperty("Font", "Runic-MT-20");
      entry->setProperty("NormalTextColour", "FF000000");
    }

  this->_optionEntries[this->_idx]->setProperty("Font", "Runic-MT-28");
  this->_optionEntries[this->_idx]->setProperty("NormalTextColour", "FFFFFFFF");
  this->_cursor->setArea(this->_optionEntries[this->_idx]->getArea());
}

void		Gauntlet::MainMenu::Settings::updateSound(bool up)
{
  int	 	actualVol;

  switch (this->_idx)
    {
      case (0) :
	actualVol = Gauntlet::CoreGame::core->getSoundMgr().getMusicVolume();
      actualVol += ((up) ? (10) : (-10));
      if (actualVol < 0)
	actualVol = 0;
      if (actualVol > 100)
	actualVol = 100;
      Gauntlet::CoreGame::core->getSoundMgr().setMusicVolume(actualVol);
      break;
      case (1) :
	actualVol = Gauntlet::CoreGame::core->getSoundMgr().getSoundVolume();
      actualVol += ((up) ? (10) : (-10));
      if (actualVol < 0)
	actualVol = 0;
      if (actualVol > 100)
	actualVol = 100;
      Gauntlet::CoreGame::core->getSoundMgr().setSoundVolume(actualVol);
      break;
      default:
	break;
    }
}
