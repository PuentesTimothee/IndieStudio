//
// Core.hpp for Indie in /home/mymy/Modules/C++/cpp_indie_studio/include
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May  9 17:17:55 2017 Mymy Aragon
// Last update Fri Jun  9 18:11:16 2017 Myriam
//

#ifndef CORE_GAME_HPP_
# define CORE_GAME_HPP_

#include <random>
#include <thread>
#include <chrono>
#include "Systems/Attack/AttackManager.hpp"
#include "Systems/Displayer/Displayer.hpp"
#include "Systems/Sound/SoundSystem.hpp"
#include "Systems/Map/MapLoader.hpp"
#include "Systems/Loot/LootManager.hpp"
#include "Systems/Saving/Saving.hpp"
#include "RP/RP.hpp"
#include "AI/AI.hpp"
#include "Movement/MovementManager.hpp"

#include "Entity/Entity.hpp"
#include "Entity/Character/Pig.hpp"
#include "Entity/Environement/Wall.hpp"
#include "Entity/Environement/Ground.hpp"

#include "Factory/Factory.hpp"
#include "Systems/Collision/CollisionManager.hpp"
#include "Menu/MenuManager.hpp"
#include "Menu/Hud.hpp"

namespace	Gauntlet
{
  class		CoreGame
  {
    Gauntlet::Displayer							_displayer;
    std::unique_ptr<Gauntlet::CollisionManager>				_collisionMgr;
    std::unique_ptr<Gauntlet::WindowManager>				_winMgr;
    Gauntlet::AnimationManager						_animationMgr;
    Gauntlet::SoundSystem						_soundMgr;
    std::unique_ptr<Gauntlet::InputManager>				_inputMgr;
    Gauntlet::RP						        _rp;
    Gauntlet::MovementMgr						_mvmMgr;
    Gauntlet::AttackManager						_attackMgr;
    Gauntlet::MapLoader							_mapLoader;
    Gauntlet::LootManager						_lootMgr;
    Gauntlet::MenuManager						_menuManager;
    Gauntlet::AI						        _ai;
    Gauntlet::Saving                            			_savingMgr;

    std::vector<std::shared_ptr<Entity>>		_entities;
    std::vector<std::shared_ptr<Entity>>		_heroes;

   public:
    static std::vector<std::shared_ptr<Gauntlet::Event> >	events;
    static bool							isMenuOn;
    static int							score;
    static const unsigned int					levels;
    static unsigned int						numberOfPlayer;

  public:
    CoreGame();
    ~CoreGame();

    Gauntlet::Displayer&		getDisplayer() { return (this->_displayer); }
    Gauntlet::CollisionManager&		getCollisionMgr() { return (*this->_collisionMgr.get()); }
    Gauntlet::MovementMgr&		getMovementMgr() { return (this->_mvmMgr); }
    Gauntlet::AnimationManager&		getAnimationMgr() { return (this->_animationMgr); }
    Gauntlet::MenuManager&		getMenuMgr() { return (this->_menuManager); }
    Gauntlet::SoundSystem&		getSoundMgr() { return (this->_soundMgr); }

    std::vector<std::shared_ptr<Gauntlet::Entity>> const& getEntities() const { return (this->_entities); };

    void 		newGame();
    void		go();
    void		gameTurn();

    void		addEntity(std::shared_ptr<Gauntlet::Entity> const&);
    void		destroyEntity(Gauntlet::Entity* ent);
    void		destroyAllEntity();

    void 		addEvent(Gauntlet::EventType type,
                           std::shared_ptr<Gauntlet::Entity> const& ent1 = nullptr,
                           std::shared_ptr<Gauntlet::Entity> const& ent2 = nullptr);

    bool		isAllowedToEvent(std::shared_ptr<Gauntlet::Event> const &evt) const;

    void 		initGame();
    template <typename PlayerClass>
    void 		addPlayer(bool ia = false);

    std::random_device                  rd;
    std::default_random_engine          gen;


    static Ogre::Real			frameRate;
    static std::unique_ptr<CoreGame> 	core;
  };
}

#endif /* !CORE_GAME_HPP_ */
