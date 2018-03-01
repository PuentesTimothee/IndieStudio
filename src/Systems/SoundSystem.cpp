//
// sound.cpp for  in /home/myriam/Projet/cpp_indie_studio
// 
// Made by Myriam
// Login   <myriam.cholet@epitech.eu>
// 
// Started on  Wed May 10 16:00:41 2017 Myriam
// Last update Wed Jun  7 14:14:34 2017 Benito
//

#include <CoreGame.hpp>
#include <Entity/Character/Valkyrie.hpp>
#include "Systems/Sound/SoundSystem.hpp"
#include "Components/Sound.hpp"
#include "File/ManageFile.hpp"

const std::string Gauntlet::SoundSystem::musicByLevelPath = "../audio/music/in_game";
const std::string Gauntlet::SoundSystem::musicForMenuPath = "../audio/music/menu";
const std::string Gauntlet::SoundSystem::musicForDefeatPath = "../audio/music/defeat";
const std::string Gauntlet::SoundSystem::musicForVictoryPath = "../audio/music/victory";
const std::string Gauntlet::SoundSystem::soundPath = "../audio/sfx";

Gauntlet::SoundSystem::SoundSystem()
{
    soundVolume = 100.0;
    musicVolume = 80.0;
    std::string dir(Gauntlet::SoundSystem::soundPath);

    std::vector<std::string> files;
    ManageFile::listFiles(dir, files);
    for (auto const& f : files)
    {
        try
        {
            _soundBuffers[f].first = this->loadBuffer(f);
            _soundBuffers[f].second.setBuffer(_soundBuffers[f].first);
        }
        catch (Gauntlet::SoundSystem::SoundNotFound const& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    playing = nullptr;
    counter = 0;
    for (unsigned int i = 0 ; i != Gauntlet::CoreGame::levels ; ++i)
    {
        files.clear();
        dir = Gauntlet::SoundSystem::musicByLevelPath;
        auto key = std::to_string(i + 1);
        dir += "/level" + key;
	this->loadDirOfMusic(dir, files, _musicBuffers);
    }
    files.clear();
    this->loadDirOfMusic(Gauntlet::SoundSystem::musicForMenuPath, files, _mainMenu);
    files.clear();
    this->loadDirOfMusic(Gauntlet::SoundSystem::musicForDefeatPath, files, _defeat);
    files.clear();
    this->loadDirOfMusic(Gauntlet::SoundSystem::musicForVictoryPath, files, _victory);
}

void            Gauntlet::SoundSystem::playSound(std::string const& name)
{
     _soundBuffers[name].second.play();
}

void            Gauntlet::SoundSystem::loadDirOfMusic(std::string const& dir,
                                                      std::vector<std::string>& files,
                                                      std::vector< std::unique_ptr<sf::Music> >& vec) const
{
    ManageFile::listFiles(dir, files);
    std::for_each(files.begin(), files.end(), [this, &vec](std::string const &file) {
        auto m = std::make_unique<sf::Music>();
        if (m->openFromFile(file)) {
            vec.push_back(std::move(m));
        }
        else
            std::cerr << "failed to load music " << file << std::endl;
    });
}

void           Gauntlet::SoundSystem::handleMove(std::shared_ptr<Gauntlet::Entity> const &entity)
{
    auto&      s = _soundBuffers[entity->get<Gauntlet::Sound>().move];
    s.second.play();
    s.second.setLoop(true);
    s.second.setVolume(this->soundVolume);
}

void           Gauntlet::SoundSystem::handleIdle(std::shared_ptr<Gauntlet::Entity> const &entity)
{
    auto&      s = _soundBuffers[entity->get<Gauntlet::Sound>().move];

    s.second.stop();
}

void           Gauntlet::SoundSystem::handleAttack(std::shared_ptr<Gauntlet::Entity> const &entity)
{
  _soundBuffers[entity->get<Gauntlet::Sound>().attack].second.play();
  _soundBuffers[entity->get<Gauntlet::Sound>().attack].second.setVolume(this->soundVolume);
}

void           Gauntlet::SoundSystem::handleDestroy(std::shared_ptr<Gauntlet::Entity> const &entity)
{
  _soundBuffers[entity->get<Gauntlet::Sound>().death].second.play();
  _soundBuffers[entity->get<Gauntlet::Sound>().death].second.setVolume(this->soundVolume);
}

void           Gauntlet::SoundSystem::handleCollision(std::shared_ptr<Gauntlet::Entity> const&)
{

}

void Gauntlet::SoundSystem::stopMusic()
{
    if (this->playing)
    {
        playing->stop();
        playing = nullptr;
    }
}

void Gauntlet::SoundSystem::handleMenu()
{
    this->stopMusic();
    if (this->_mainMenu.size() > 0)
    {
        this->_mainMenu.front()->play();
        this->_mainMenu.front()->setLoop(true);
        playing = this->_mainMenu.front().get();
        playing->setVolume(this->musicVolume);
    }
}

void		Gauntlet::SoundSystem::handleLevelEnd()
{
    if (this->_victory.size() > 0 && this->playing == this->_victory.front().get())
        return ;
    this->stopMusic();
    if (counter < _musicBuffers.size())
    {
        this->_musicBuffers[counter]->play();
        playing = this->_musicBuffers[counter].get();
        playing->setVolume(this->musicVolume);
    }
    ++counter;
}

void             Gauntlet::SoundSystem::setSoundVolume(float volume)
{
    if (volume <= 100.0)
        soundVolume = volume;
}

void             Gauntlet::SoundSystem::setMusicVolume(float volume)
{
    if (volume <= 100.0)
    {
        musicVolume = volume;
        if (this->playing) {
            playing->setVolume(volume);
        }
    }
}

float     Gauntlet::SoundSystem::getSoundVolume() const
{
    return (soundVolume);
}

float     Gauntlet::SoundSystem::getMusicVolume() const
{
    return (musicVolume);
}

void				Gauntlet::SoundSystem::handleNewGame()
{
  this->stopMusic();
  this->counter = 0;
  this->handleLevelEnd();
}

void Gauntlet::SoundSystem::handleDefeat()
{
    this->stopMusic();
    if (this->_defeat.size() > 0)
    {
        this->_defeat.front()->play();
        playing = this->_defeat.front().get();
        playing->setVolume(this->musicVolume);
    }
}

void Gauntlet::SoundSystem::handleVictory()
{
    this->stopMusic();
    if (this->_victory.size() > 0)
    {
        this->_victory.front()->play();
        playing = this->_victory.front().get();
        playing->setVolume(this->musicVolume);
    }
}

void Gauntlet::SoundSystem::handleBoss(std::shared_ptr<Gauntlet::Entity> const &entity)
{
    _soundBuffers[entity->get<Gauntlet::Sound>().death].second.play();
    _soundBuffers[entity->get<Gauntlet::Sound>().death].second.setVolume(this->soundVolume);
}

void            Gauntlet::SoundSystem::takeEvent(Gauntlet::Event const &event)
{
    try
    {
        switch (event._type) {
            case EventType::ATTACK :
                this->handleAttack(event._entities.front());
                break;
            case EventType::MOVE :
                this->handleMove(event._entities.front());
                break;
            case EventType::COLLISION :
                this->handleCollision(event._entities.front());
                break;
            case EventType::IDLE :
                this->handleIdle(event._entities.front());
                break;
	        case EventType::DESTROY :
        	    this->handleDestroy(event._entities.front());
        	    break;
            case EventType::LEVEL_END :
                this->handleLevelEnd();
                break;
            case EventType::NEW_GAME :
                this->handleNewGame();
                break;
            case EventType::MAIN_MENU :
                this->handleMenu();
                break;
    	    case EventType::DEFEAT :
                this->handleDefeat();
    	        this->counter = 0;
    	        break;
	        case EventType::VICTORY :
                this->handleVictory();
	            this->counter = 0;
                break;
            case EventType::SPAWN_BOSS:
                this->handleBoss(event._entities.front());
                break;
            default:
              break;
        }
    }
    catch (std::runtime_error const&) {}
}

sf::SoundBuffer			Gauntlet::SoundSystem::loadBuffer(std::string const& path)
{
  sf::SoundBuffer	    buffer;

  if (!buffer.loadFromFile(path))
  {
      throw Gauntlet::SoundSystem::SoundNotFound(path);
  }
  else
  {
      std::cout << path << " load success : " << path << std::endl;
  }
  return (buffer);
}
