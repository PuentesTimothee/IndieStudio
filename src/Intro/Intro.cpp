//
// Intro.cpp for  in /home/myriam/Projet/cpp_indie_studio
// 
// Made by Myriam
//

#include <CoreGame.hpp>
#include "Intro/Intro.hpp"

Gauntlet::Intro::Intro()
{
  this->mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
  
  CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
  
  CEGUI::Window* Intro = mgr.createWindow("TaharezLook/StaticImage", "Background");

  Intro->setPosition(CEGUI::UVector2(CEGUI::UDim(0.350, 0), CEGUI::UDim(0.1, 0)));
  MenuBackground->setSize(CEGUI::USize(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.45, 0)));
}

Gauntlet::Intro::~Intro()
{
  CEGUI::OgreRenderer::destroy(static_cast<CEGUI::OgreRenderer&>(*mRenderer));
}

void		Gauntlet::Intro::takeEvent(Event const &event)
{
  if (event._type == EventType::ENTER)
    {
      // Launch Game/Menu
    }
}
