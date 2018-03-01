//
// Created by puentes on 18/05/17.
//

#include "Systems/Input/InputManager.hpp"

Gauntlet::InputManager::InputManager(Ogre::RenderWindow *win)
	: _OISMgr(nullptr),
	  _keyboard(nullptr),
	  _joysticks(0),
	  _keyboardListener(nullptr),
      _id(0)
{
    OIS::ParamList	plist;
    size_t		windowHandle = 0;
    std::ostringstream	windowHandleStr;

    win->getCustomAttribute("WINDOW", &windowHandle);
    windowHandleStr << windowHandle;
    plist.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

    this->_OISMgr = OIS::InputManager::createInputSystem(plist);
    this->_keyboard = static_cast<OIS::Keyboard *>(this->_OISMgr->createInputObject(OIS::OISKeyboard, true));
    if (this->_OISMgr->getNumberOfDevices(OIS::OISJoyStick) > 0)
    {
        this->_joysticks.resize(this->_OISMgr->getNumberOfDevices(OIS::OISJoyStick));
        for (std::vector<OIS::JoyStick *>::iterator it = this->_joysticks.begin();
             it < this->_joysticks.end();
             ++it)
        {
            (*it) = static_cast<OIS::JoyStick *>(this->_OISMgr->createInputObject(OIS::OISJoyStick, true));
        }
    }
    this->_keyboardListener = new Gauntlet::KeyListener(this->_keyboard);
}

Gauntlet::InputManager::~InputManager()
{
  this->_OISMgr->destroyInputObject(this->_keyboard);
  OIS::InputManager::destroyInputSystem(this->_OISMgr);
}

bool		Gauntlet::InputManager::isKeyDown(OIS::KeyCode kc)
{
  return (this->_keyboard->isKeyDown(kc));
}

void		Gauntlet::InputManager::getInputEvent()
{
    this->_keyboard->capture();
    if (this->_joysticks.size() > 0)
    {
        for (std::vector<OIS::JoyStick *>::iterator it = this->_joysticks.begin();
             it != this->_joysticks.end();
             ++it)
        {
            (*it)->capture();
        }
    }
}

void		Gauntlet::InputManager::takeEvent(Gauntlet::Event const &evt)
{
  if (evt._type == Gauntlet::EventType::DESTROY && evt._entities[0]->type != Entity::Type::HERO)
    this->unregisterEntity(evt._entities[0].get());
}

void Gauntlet::InputManager::resetId()
{
    _id = 0;
}

void		Gauntlet::InputManager::registerEntityAsPlayer(std::shared_ptr<Gauntlet::Entity> const& player)
{
  if (_id >= this->_MAX_PLAYER)
  {
      return;
  }

  if (this->_joysticks.size() > _id)
    this->_player[_id].reset(new Gauntlet::KeyListener(this->_joysticks[_id], player));
  this->_keyboardListener->addPlayerKeyboard(player, _id);
  ++_id;
}

void		Gauntlet::InputManager::unregisterEntity(Gauntlet::Entity* ent)
{
  int 		a = 0;
  for (auto & player : this->_player)
    {
      if (player && player->isOnEnt(ent))
	{
        this->_joysticks[a]->setEventCallback(nullptr);
	  player.reset();
	}
      a++;
    }
  this->_keyboardListener->removePlayerKeyboard(ent);
}

void		Gauntlet::InputManager::destroyAllEntity()
{
  for (auto & player : this->_player)
    player.reset();
  for (auto & joystick : this->_joysticks)
    joystick->setEventCallback(nullptr);
  this->_keyboardListener->removeAllPlayerKeyboard();
}
