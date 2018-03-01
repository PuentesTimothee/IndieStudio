//
// Created by puentes on 18/05/17.
//

#ifndef INDIE_INPUTMANAGER_HPP
#define INDIE_INPUTMANAGER_HPP

#include <Ogre.h>
#include <OIS/OIS.h>

#include "Systems/System.hpp"
#include "Systems/Input/KeyListener.hpp"

namespace Gauntlet
{
  class InputManager : public Gauntlet::System
  {
   private:
      OIS::InputManager						*_OISMgr;
      OIS::Keyboard						*_keyboard;
      std::vector<OIS::JoyStick*>   				_joysticks;
      Gauntlet::KeyListener         			   	*_keyboardListener;
      std::array<std::unique_ptr<Gauntlet::KeyListener>, 4>	_player;

    static int const						_MAX_PLAYER = 4;
    unsigned int						_id;
   public:

    InputManager(Ogre::RenderWindow *win);
    ~InputManager();

    void 		getInputEvent();

    bool		isKeyDown(OIS::KeyCode kc);

    void		registerEntityAsPlayer(std::shared_ptr<Gauntlet::Entity> const& player);

    void		unregisterEntity(Gauntlet::Entity* ent);
    virtual void	takeEvent(Gauntlet::Event const &event) override ;
    void		destroyAllEntity();
      void      resetId();
  };
};

#endif //INDIE_INPUTMANAGER_HPP
