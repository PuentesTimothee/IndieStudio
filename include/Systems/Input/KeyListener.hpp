//
// Created by puentes on 18/05/17.
//

#ifndef INDIE_PLAYERCONTROL_HPP
#define INDIE_PLAYERCONTROL_HPP

#include <Ogre.h>

#include <OIS/OIS.h>

#include <string>

#include "Entity/Entity.hpp"
#include "Event/Event.hpp"

namespace Gauntlet
{
    enum class ButtonJoystick : int
    {
        A = 0,
        B = 1,
        X = 2,
        Y = 3,
        L = 4,
        R = 5,
        SELECT = 6,
        START = 7,
    };

    enum DirectionPov : int
    {
        CENTERED  = 0x00000000,
        NORTH     = 0x00000001,
        SOUTH     = 0x00000010,
        EAST      = 0x00000100,
        WEST      = 0x00001000
    };

  struct Action
  {
   public:
    enum SubType : int
    {
      DEFAULT,
      UP,
      DOWN,
      LEFT,
      RIGHT
    };

    Gauntlet::EventType		type;
    Gauntlet::Action::SubType 	subtype;
    OIS::KeyCode		binding;
    std::string			desc;

    Action(Gauntlet::EventType paramType,
	   OIS::KeyCode paramBinding,
	   std::string paramDesc,
	   Gauntlet::Action::SubType subType = Gauntlet::Action::DEFAULT);

    Action(Action const &other);

    Action &operator=(Action const &other);

    bool operator==(Action const &other) const
    { return (this->type == other.type &&
      		this->subtype == other.subtype); };

    bool operator==(Gauntlet::EventType type) const
    { return (this->type == type); };

    static std::array<Gauntlet::Action, 4>	S_UP;
    static std::array<Gauntlet::Action, 4>	S_LEFT;
    static std::array<Gauntlet::Action, 4>	S_RIGHT;
    static std::array<Gauntlet::Action, 4>	S_DOWN;
    static std::array<Gauntlet::Action, 4>	S_ATTACK;
    static std::array<Gauntlet::Action, 4>	S_DASH;
    static Gauntlet::Action			S_MENU;
    static Gauntlet::Action			S_ENTER;
  };

  class KeyListener : public OIS::KeyListener, public OIS::JoyStickListener
  {
   private:
    std::array<std::vector<Action>, 4>			_binding;
    std::shared_ptr<Gauntlet::Entity>			_player;
    std::array<std::shared_ptr<Gauntlet::Entity>, 4>	_playerKeyboard;
    std::array<std::vector<Action>, 4>			_actionsPile;

      Gauntlet::MoveEvent			*		getMoveInput(size_t num_player);
   public:

      KeyListener(OIS::JoyStick *joystick,
                  std::shared_ptr<Gauntlet::Entity> const& player);
      KeyListener(OIS::Keyboard *keyboard);

    void	addPlayerKeyboard(std::shared_ptr<Gauntlet::Entity> const &player, int id);
    void	removePlayerKeyboard(Gauntlet::Entity* &ent);
    void	removeAllPlayerKeyboard();
    bool	isOnEnt(Gauntlet::Entity* ent);

    virtual ~KeyListener() {};

    //KeyBoard
      bool		keyPressed(const OIS::KeyEvent &arg);
      bool		keyReleased(const OIS::KeyEvent &arg);

    //Joystick
      bool povMoved(const OIS::JoyStickEvent &e, int pov);
      bool axisMoved(const OIS::JoyStickEvent &, int);
      bool sliderMoved(const OIS::JoyStickEvent, int) {return true;};
      bool buttonPressed(const OIS::JoyStickEvent &e, int button);
      bool buttonReleased(const OIS::JoyStickEvent &e, int button);
  };
}

#endif //INDIE_PLAYERCONTROL_HPP
