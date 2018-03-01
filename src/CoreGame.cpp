//
// Core.cpp for Indie Studio in /home/mymy/Modules/C++/cpp_indie_studio/src/Core
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May  9 17:15:34 2017 Mymy Aragon
// Last update Fri Jun 16 11:13:41 2017 benito
//

#include <Systems/Displayer/WindowManager.hpp>
#include <Entity/Collectable/Meat.hpp>
#include <Entity/Collectable/Icecream.hpp>
#include <Entity/Collectable/Coin.hpp>
#include "CoreGame.hpp"

const unsigned int Gauntlet::CoreGame::levels = 3;

std::unique_ptr<Gauntlet::CoreGame>		Gauntlet::CoreGame::core = nullptr;
std::vector<std::shared_ptr<Gauntlet::Event> >	Gauntlet::CoreGame::events;
bool                            		Gauntlet::CoreGame::isMenuOn = true;
int                             		Gauntlet::CoreGame::score = 0;
unsigned int					Gauntlet::CoreGame::numberOfPlayer = 1;

Ogre::Real			Gauntlet::CoreGame::frameRate;

Gauntlet::CoreGame::CoreGame()
	: _displayer(),
	  _collisionMgr(nullptr),
	  _winMgr(nullptr),
	  _animationMgr(this->_displayer.getSceneManager()),
	  _soundMgr(),
	  _inputMgr(nullptr),
	  _rp(),
	  _mvmMgr(),
	  _mapLoader(),
	  _lootMgr(),
	  _menuManager(),
	  _ai(),
	  _savingMgr(),
      gen(rd())
{
  this->_winMgr.reset(new Gauntlet::WindowManager(this->_displayer.getRenderWindow(),
					      this->_displayer.getSceneManager(),
					      this->_animationMgr));
  this->_displayer.addFrameListener(this->_winMgr.get());
  this->_inputMgr.reset(new Gauntlet::InputManager(this->_displayer.getRenderWindow()));
  this->_collisionMgr.reset(new Gauntlet::CollisionManager(this->_displayer.getSceneManager()));

  this->score = 0;
}

Gauntlet::CoreGame::~CoreGame()
{
}

void		Gauntlet::CoreGame::go()
{
  this->_menuManager.addSplashScreen();
  this->_menuManager.addMainMenu();
  this->_menuManager.setActiveMenu(Gauntlet::MenuType::SPLASHSCREEN, true);

  this->addPlayer<Gauntlet::Entity>();

  this->_displayer.startRendering();

}

template <typename PlayerClass>
void		Gauntlet::CoreGame::addPlayer(bool ia)
{
  std::shared_ptr<Gauntlet::Entity>	player = EntityFactory::create<PlayerClass>();
  this->_entities.push_back(player);
  if (!ia)
    this->_inputMgr->registerEntityAsPlayer(player);
  else
    this->_ai.addPlayer(player);
  this->_heroes.push_back(player);
}

void		Gauntlet::CoreGame::initGame()
{
  this->_mapLoader.loadNextMap();
  this->_menuManager.addGameMenu();
  this->_menuManager.addEndGame();

  this->_inputMgr->resetId();

  unsigned int c = 0;
  this->addPlayer<Gauntlet::Warrior>(this->numberOfPlayer <= c++);
  this->addPlayer<Gauntlet::Valkyrie>(this->numberOfPlayer <= c++);
  this->addPlayer<Gauntlet::Priest>(this->numberOfPlayer <= c++);
  this->addPlayer<Gauntlet::Assassin>(this->numberOfPlayer <= c++);

  this->_menuManager.addHud(this->_heroes);
}

void		Gauntlet::CoreGame::gameTurn()
{
  this->_inputMgr->getInputEvent();

  if (!isMenuOn)
    {
      this->_collisionMgr->updateSimulation();

      this->_collisionMgr->getCollision();
      this->_ai.play(_heroes);
      this->_attackMgr.updateTrajectorys();
    }

  /*
  *	Treat Event
  */
  std::vector<std::shared_ptr<Gauntlet::Event> > copyEvent = this->events;
  this->events.clear();
  if (!copyEvent.empty())
  for (auto & event : copyEvent)
    {
      auto &ref = *(event.get());

      if (!isMenuOn && this->isAllowedToEvent(event))
	{
	  this->_attackMgr.takeEvent(ref);
	  this->_rp.takeEvent(ref);
	  this->_mvmMgr.takeEvent(ref);
	  this->_animationMgr.takeEvent(ref);
	  this->_winMgr->takeEvent(ref);
	  this->_inputMgr->takeEvent(ref);
	  this->_ai.takeEvent(ref);
	  this->_lootMgr.takeEvent(ref);
	  this->_mapLoader.takeEvent(ref);
	}

      this->_soundMgr.takeEvent(ref);
      this->_savingMgr.takeEvent(ref);

      this->_winMgr->takeEvent(ref);
      this->_displayer.takeEvent(ref);
      this->_menuManager.takeEvent(ref);
      if (ref._type == Gauntlet::EventType::DESTROY && ref._entities[0]->type != Entity::Type::HERO)
          this->destroyEntity(ref._entities[0].get());
      if (ref._type == Gauntlet::EventType::NEW_GAME)
	{
	  this->newGame();
	  break;
	}
    }
  if (!isMenuOn)
    {
      this->_mvmMgr.updateSpeed();
      this->_rp.checkGameState(this->_entities);
    }

  /*Render*/
  this->_menuManager.updateMenu();
  this->_animationMgr.render(this->frameRate);
}

void		Gauntlet::CoreGame::addEntity(std::shared_ptr<Gauntlet::Entity> const &e)
{
  this->_entities.push_back(e);
}

void		Gauntlet::CoreGame::destroyAllEntity()
{
  this->_animationMgr.clearAll();
  this->_mvmMgr.destroyAllEntity();
  this->_attackMgr.destroyAllEntity();
  this->_ai.destroyAllEnt();
  this->_inputMgr->destroyAllEntity();

  EntityFactory::destroyAll();
  this->_heroes.clear();
  this->_entities.clear();
  this->score = 0;
}

void		Gauntlet::CoreGame::destroyEntity(Gauntlet::Entity* ent)
{
  EntityFactory::destroy(ent);
  this->_entities.erase(std::remove_if(
	  this->_entities.begin(), this->_entities.end(),
	  [ent](std::shared_ptr<Gauntlet::Entity> & obj)
	  { return (ent == obj.get()); }),
		    this->_entities.end());
}

bool		Gauntlet::CoreGame::isAllowedToEvent(const std::shared_ptr<Gauntlet::Event> &evt) const
{
  switch (evt->_type)
    {
      case Gauntlet::EventType::ATTACK_END :
    	return (true);
      case Gauntlet::EventType::COLLISION :
    	return (true);
      case Gauntlet::EventType::MENU :
	    return (true);

      case Gauntlet::EventType::SAVE :
	    return (true);
      case Gauntlet::EventType::LOAD :
	    return (true);
      case Gauntlet::EventType::DESTROY :
	    return (true);
      case Gauntlet::EventType::QUIT :
	    return (true);
      case Gauntlet::EventType::REVIVE :
	    return (true);
      default :
	    break;
    }
  Gauntlet::State	*state;

  if (evt->_entities.size() != 0 &&
	  (state = evt->_entities[0]->getPtr<Gauntlet::State>()) != nullptr)
    {
      switch (state->type)
    	{
    	  case (Gauntlet::State::Type::DASH) :
	        return (false);
	      case (Gauntlet::State::Type::ATTACK) :
	        return (false);
    	  case (Gauntlet::State::Type::DEAD) :
	        return (false);
          default:
	        break;
    	}
    }
  return (true);
}

void Gauntlet::CoreGame::addEvent(Gauntlet::EventType type, std::shared_ptr<Gauntlet::Entity> const &ent1,
                                  std::shared_ptr<Gauntlet::Entity> const &ent2)
{
    Gauntlet::Event *event = new Gauntlet::Event(type);
    if (ent1)
        event->_entities.emplace_back(ent1);
    if (ent2)
        event->_entities.emplace_back(ent2);
    this->events.emplace_back(event);
}

void		Gauntlet::CoreGame::newGame()
{
  this->destroyAllEntity();
  this->_mapLoader.restartGame();
  this->initGame();
  this->getMenuMgr().setActiveMenu(Gauntlet::MenuType::MAIN_MENU, false);
  this->getMenuMgr().setActiveMenu(Gauntlet::MenuType::HUD, true);
}
