//
// Displayer.hpp for Indie Sutdio in /home/mymy/Modules/C++/cpp_indie_studio/include
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May  9 16:23:20 2017 Mymy Aragon
// Last update Tue May 23 17:54:40 2017 Mymy Aragon
//

#ifndef DISPLAYER_HPP_
# define DISPLAYER_HPP_

#include <Ogre.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreWindowEventUtilities.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreMath.h>

#include "WindowManager.hpp"
#include "Systems/Animation/AnimationManager.hpp"

namespace Gauntlet
  {
   class				        Displayer : public System
    {
     Ogre::Root					*root;
     Ogre::RenderSystem				*rs;
     Ogre::RenderWindow				*window;
     Ogre::SceneManager				*sceneMgr;
     Ogre::Camera				*camera;
     Ogre::Viewport				*viewPort;

     Ogre::Light				*gloablLight;
     Ogre::SceneNode				*gloablLightNode;

    void			setupResources();
     void			setupCamera();
     void			setupBackground();

    public:
     Displayer();
     ~Displayer();

     bool			isOpen();

     void			createGround();
     Ogre::SceneNode		*createEntity(std::string const &,
						  std::string const &,
						  std::string const &matName = "",
						  bool hasShadow = true);
     Ogre::SceneNode		*createLight(Ogre::SceneNode *node,
						 Ogre::Vector3 const & offset,
						 Ogre::ColourValue const & colorDif,
						 Ogre::ColourValue const & colorSpec,
						 float power,
						 Ogre::Light* &lightRet,
						 Ogre::Light::LightTypes const &lightType = Ogre::Light::LT_POINT);
     void     		       	deleteEntity(Ogre::SceneNode *node, Ogre::Entity *ent);
     void     		       	deleteLight(Ogre::SceneNode *node, Ogre::Light *light);

      void			startRendering(void);

      Ogre::SceneManager	*getSceneManager() const { return (this->sceneMgr); };
      Ogre::RenderWindow	*getRenderWindow() const { return (this->window); };

     void			takeEvent(Gauntlet::Event const &event);

     void			 addFrameListener(Gauntlet::WindowManager *windMgr);
  };
}

#endif /* !DISPLAYER_HPP_ */
