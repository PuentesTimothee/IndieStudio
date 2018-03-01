//
// Created by puentes on 18/05/17.
//

#include "Systems/Input/KeyListener.hpp"
#include "CoreGame.hpp"

std::array<Gauntlet::Action, 4>			Gauntlet::Action::S_UP =
	{
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_UP, "Go up", Gauntlet::Action::SubType::UP),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_Z, "Go up", Gauntlet::Action::SubType::UP),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_Y, "Go up", Gauntlet::Action::SubType::UP),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_O, "Go up", Gauntlet::Action::SubType::UP)
	};

std::array<Gauntlet::Action, 4>			Gauntlet::Action::S_DOWN =
	{
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_DOWN, "Go down", Gauntlet::Action::SubType::DOWN),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_S, "Go down", Gauntlet::Action::SubType::DOWN),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_H, "Go down", Gauntlet::Action::SubType::DOWN),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_L, "Go down", Gauntlet::Action::SubType::DOWN)
	};

std::array<Gauntlet::Action, 4>			Gauntlet::Action::S_LEFT =
	{
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_LEFT, "Go left", Gauntlet::Action::SubType::LEFT),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_Q, "Go left", Gauntlet::Action::SubType::LEFT),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_G, "Go left", Gauntlet::Action::SubType::LEFT),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_K, "Go left", Gauntlet::Action::SubType::LEFT)
	};

std::array<Gauntlet::Action, 4>			Gauntlet::Action::S_RIGHT =
	{
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_RIGHT, "Go right", Gauntlet::Action::SubType::RIGHT),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_D, "Go right", Gauntlet::Action::SubType::RIGHT),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_J, "Go right", Gauntlet::Action::SubType::RIGHT),
		Gauntlet::Action(Gauntlet::EventType::MOVE, OIS::KC_M, "Go right", Gauntlet::Action::SubType::RIGHT)
	};

std::array<Gauntlet::Action, 4>			Gauntlet::Action::S_ATTACK =
	{
		Gauntlet::Action(Gauntlet::EventType::ATTACK, OIS::KC_SPACE, "Attack"),
		Gauntlet::Action(Gauntlet::EventType::ATTACK, OIS::KC_E, "Attack"),
		Gauntlet::Action(Gauntlet::EventType::ATTACK, OIS::KC_U, "Attack"),
		Gauntlet::Action(Gauntlet::EventType::ATTACK, OIS::KC_P, "Attack")
	};

std::array<Gauntlet::Action, 4>			Gauntlet::Action::S_DASH =
	{
		Gauntlet::Action(Gauntlet::EventType::DASH, OIS::KC_N, "Dash"),
		Gauntlet::Action(Gauntlet::EventType::DASH, OIS::KC_A, "Dash"),
		Gauntlet::Action(Gauntlet::EventType::DASH, OIS::KC_T, "Dash"),
		Gauntlet::Action(Gauntlet::EventType::DASH, OIS::KC_I, "Dash")
	};

Gauntlet::Action			Gauntlet::Action::S_MENU =
		Gauntlet::Action(Gauntlet::EventType::MENU, OIS::KC_ESCAPE, "Menu");

Gauntlet::Action			Gauntlet::Action::S_ENTER =
		Gauntlet::Action(Gauntlet::EventType::ENTER, OIS::KC_RETURN, "Enter");

Gauntlet::Action::Action(Gauntlet::EventType paramType,
			 OIS::KeyCode paramBinding,
			 std::string paramDesc,
			 Gauntlet::Action::SubType paramSubtype)
	: type(paramType),
	  subtype(paramSubtype),
	  binding(paramBinding),
	  desc(paramDesc)
{
}

Gauntlet::Action::Action(Gauntlet::Action const &other)
	: type(other.type),
	  subtype(other.subtype),
	  binding(other.binding),
	  desc(other.desc)
{
}

Gauntlet::Action&			Gauntlet::Action::operator=(const Gauntlet::Action &other)
{
  if (&other != this)
    {
      this->type = other.type;
      this->subtype = other.subtype;
      this->binding = other.binding;
      this->desc = other.desc;
    }
  return (*this);
}

Gauntlet::KeyListener::KeyListener(OIS::Keyboard *keyboard)
	: _binding(),
	  _playerKeyboard()
{
  keyboard->setEventCallback(this);
}

void Gauntlet::KeyListener::addPlayerKeyboard(std::shared_ptr<Gauntlet::Entity> const &player, int id)
{
  std::vector<Gauntlet::Action> actions;

  actions.push_back(Gauntlet::Action::S_UP[id]);
  actions.push_back(Gauntlet::Action::S_DOWN[id]);
  actions.push_back(Gauntlet::Action::S_LEFT[id]);
  actions.push_back(Gauntlet::Action::S_RIGHT[id]);
  actions.push_back(Gauntlet::Action::S_ATTACK[id]);
  actions.push_back(Gauntlet::Action::S_DASH[id]);

  actions.push_back(Gauntlet::Action::S_MENU);
  actions.push_back(Gauntlet::Action::S_ENTER);

  this->_binding[id] = actions;
  this->_playerKeyboard[id] = player;
}

Gauntlet::KeyListener::KeyListener(OIS::JoyStick *joystick,
                                   std::shared_ptr<Gauntlet::Entity> const& player)
        : _player(player)
{
    joystick->setEventCallback(this);
}

bool Gauntlet::KeyListener::povMoved(const OIS::JoyStickEvent &e, int pov)
{
    Gauntlet::DirectionPov dir;

    dir = static_cast< Gauntlet::DirectionPov >(e.state.mPOV[pov].direction);

    if (dir == Gauntlet::DirectionPov::CENTERED)
      Gauntlet::CoreGame::core->addEvent(Gauntlet::EventType::IDLE, this->_player);
    else
    {
	Gauntlet::Event *event = new Gauntlet::MoveEvent();
        if (dir & Gauntlet::DirectionPov::EAST)
            static_cast<Gauntlet::MoveEvent *>(event)->type.push_back(Gauntlet::MoveEvent::Type::RIGHT);
        if (dir & Gauntlet::DirectionPov::NORTH)
            static_cast<Gauntlet::MoveEvent *>(event)->type.push_back(Gauntlet::MoveEvent::Type::UP);
        if (dir & Gauntlet::DirectionPov::SOUTH)
            static_cast<Gauntlet::MoveEvent *>(event)->type.push_back(Gauntlet::MoveEvent::Type::DOWN);
        if (dir & Gauntlet::DirectionPov::WEST)
            static_cast<Gauntlet::MoveEvent *>(event)->type.push_back(Gauntlet::MoveEvent::Type::LEFT);
	event->_entities.push_back(this->_player);
	Gauntlet::CoreGame::events.push_back(std::shared_ptr<Gauntlet::Event>(event));
    }

    return (true);
}

bool Gauntlet::KeyListener::axisMoved(const OIS::JoyStickEvent&, int)
{
    return (true);
}

bool Gauntlet::KeyListener::buttonPressed(const OIS::JoyStickEvent &e, int button)
{
    Gauntlet::ButtonJoystick buttonJoystick;
    Gauntlet::EventType eventType;

    buttonJoystick = static_cast<Gauntlet::ButtonJoystick>(button);
    if (!e.state.mButtons[button])
        return (false);
    switch (buttonJoystick)
    {
	case (Gauntlet::ButtonJoystick::A) :
	  if (CoreGame::core->isMenuOn)
	    eventType = Gauntlet::EventType::ENTER;
	  else
	    eventType = Gauntlet::EventType::ATTACK;
	break;
	case (Gauntlet::ButtonJoystick::B) :
	  eventType = Gauntlet::EventType::DASH;
	break;
	case (Gauntlet::ButtonJoystick::START) :
	  eventType = Gauntlet::EventType::MENU;
	break;
	default:
	  eventType = Gauntlet::EventType::IDLE;
	break;
    }
  Gauntlet::CoreGame::core->addEvent(eventType, this->_player);
  return (true);
}

bool Gauntlet::KeyListener::buttonReleased(const OIS::JoyStickEvent &, int)
{
    return (true);
}

bool			Gauntlet::KeyListener::keyPressed(const OIS::KeyEvent &arg)
{
  size_t i;
  size_t size = this->_binding.size();

  i = 0;
  while (i != size)
    {
      for (auto &action : this->_binding[i])
	{
	  if (action.binding == arg.key &&
	      std::find(this->_actionsPile[i].begin(), this->_actionsPile[i].end(), action)
	      == this->_actionsPile[i].end())
	    {
	      this->_actionsPile[i].push_back(action);

	      Gauntlet::Event *event = nullptr;

	      if (action.type == Gauntlet::EventType::MOVE)
		event = this->getMoveInput(i);
	      else
		event = new Gauntlet::Event(action.type);

	      event->_entities.push_back(this->_playerKeyboard[i]);

	      Gauntlet::CoreGame::events.push_back(std::shared_ptr<Gauntlet::Event>(event));
	      return (true);
	    }
	}
      i = i + 1;
    }

  if (arg.key == OIS::KC_ESCAPE)
    {
      auto event = std::make_shared<Gauntlet::Event>(Gauntlet::EventType::MENU);
      Gauntlet::CoreGame::events.push_back(event);
    }
  return (true);
}

bool			Gauntlet::KeyListener::keyReleased(const OIS::KeyEvent &arg)
{
  size_t i;
  size_t size = this->_binding.size();

  i = 0;
  while (i != size)
    {
        for (auto &action : this->_binding[i])
        {
            if (action.binding == arg.key)
            {
                this->_actionsPile[i].erase(std::remove(this->_actionsPile[i].begin(),
                                                    this->_actionsPile[i].end(),
                                                    action),
                                        this->_actionsPile[i].end());
                if (action.type == Gauntlet::EventType::MOVE &&
                    std::find(this->_actionsPile[i].begin(), this->_actionsPile[i].end(), Gauntlet::EventType::MOVE)
                    == this->_actionsPile[i].end())
                {
                    auto event = std::make_shared<Gauntlet::Event>(Gauntlet::EventType::IDLE);

                    event->_entities.push_back(this->_playerKeyboard[i]);
                    Gauntlet::CoreGame::events.push_back(event);
                }
                else if (action.type == Gauntlet::EventType::MOVE)
                {
                    auto *event = this->getMoveInput(i);

                    event->_entities.push_back(this->_playerKeyboard[i]);
                    Gauntlet::CoreGame::events.push_back(std::shared_ptr<Gauntlet::Event>(event));
                }
            }
        }
        i = i + 1;
    }

  return (true);
}

Gauntlet::MoveEvent			*Gauntlet::KeyListener::getMoveInput(size_t num_player)
{
  auto const& entity = this->_playerKeyboard[num_player];

  auto event = new Gauntlet::MoveEvent();
  event->_entities.push_back(entity);
  for (auto const& action : this->_actionsPile[num_player])
    {
      switch (action.subtype)
    	{
    	  case (Gauntlet::Action::SubType::UP) :
	        event->type.push_back(Gauntlet::MoveEvent::Type::UP);
	        break;
          case (Gauntlet::Action::SubType::DOWN) :
            event->type.push_back(Gauntlet::MoveEvent::Type::DOWN);
	        break;
	      case (Gauntlet::Action::SubType::LEFT) :
            event->type.push_back(Gauntlet::MoveEvent::Type::LEFT);
	        break;
	      case (Gauntlet::Action::SubType::RIGHT) :
            event->type.push_back(Gauntlet::MoveEvent::Type::RIGHT);
	        break;
          default:
	        break;
    	}
    }
    return (event);
}

void		Gauntlet::KeyListener::removePlayerKeyboard(Gauntlet::Entity* &ent)
{
  int 		a = 0;
  for (auto &player : this->_playerKeyboard)
    {
      if (player.get() == ent)
	{
	  this->_binding[a].clear();
	  player.reset();
	}
      a++;
    }
}

void		Gauntlet::KeyListener::removeAllPlayerKeyboard()
{
  for (auto &player : this->_playerKeyboard)
    player.reset();
  for (auto &binding : this->_binding)
    binding.clear();
  this->_player.reset();
}

bool		Gauntlet::KeyListener::isOnEnt(Gauntlet::Entity* ent)
{
  return (this->_player.get() == ent);
}