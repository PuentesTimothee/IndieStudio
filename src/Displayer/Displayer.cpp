//
// Displayer.cpp for Indie studio in /home/mymy/Modules/C++/cpp_indie_studio/src/Displayer
// 
// Made by Mymy Aragon
// Login   <my-lan.aragon@epitech.eu>
// 
// Started on  Tue May  9 16:33:04 2017 Mymy Aragon
// Last update Fri Jun  9 15:14:18 2017 Myriam
//

#include <Components/Model.hpp>
#include <CoreGame.hpp>
#include "Systems/Displayer/Displayer.hpp"

Gauntlet::Displayer::Displayer() :
		root(new Ogre::Root("plugins.cfg", "ogre.cfg")),
		rs(this->root->getRenderSystemByName("OpenGL Rendering Subsystem")),
		window(nullptr),
		sceneMgr(this->root->createSceneManager(Ogre::ST_GENERIC)),
		camera(nullptr),
		viewPort(nullptr)
{
  /*
   *  INIT OGRE
   */
  this->root->setRenderSystem(this->rs);
  this->rs->setConfigOption("Full Screen", "Yes");
    this->window = root->initialise(true, "Gauntlet");
  this->setupResources();

  /*
   *  SCENE
   */
  this->setupCamera();
  this->setupBackground();

  this->createGround();
}

Gauntlet::Displayer::~Displayer()
{

}


void			Gauntlet::Displayer::setupResources()
{
  Ogre::ConfigFile	cf;

  cf.load("resources.cfg");

  Ogre::ConfigFile::SectionIterator	seci = cf.getSectionIterator();
  Ogre::String				secName, typeName, archName;

  while (seci.hasMoreElements())
    {
      secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator i;
      for (i = settings->begin(); i != settings->end(); ++i)
	{
	  typeName = i->first;
	  archName = i->second;
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
	}
    }

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void			Gauntlet::Displayer::setupCamera()
{
  this->camera = this->sceneMgr->createCamera("MainCam");
  this->camera->setPosition(0, 140, 100);
  this->camera->lookAt(0, 0, 0);
  this->camera->setNearClipDistance(5);
}

void			Gauntlet::Displayer::setupBackground()
{
  this->viewPort = this->window->addViewport(this->camera);
  this->viewPort->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
  this->camera->setAspectRatio(Ogre::Real(this->viewPort->getActualWidth()) /
				 Ogre::Real(this->viewPort->getActualHeight()));
  this->sceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));

  this->sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}

bool			Gauntlet::Displayer::isOpen()
{
  Ogre::WindowEventUtilities::messagePump();
  return (!this->window->isClosed());
}

Ogre::SceneNode		*Gauntlet::Displayer::createLight(Ogre::SceneNode *node,
								 Ogre::Vector3 const &offset,
								 const Ogre::ColourValue &colorDif,
								 const Ogre::ColourValue &colorSpec,
								 float power,
								 Ogre::Light* &lightRet,
								 Ogre::Light::LightTypes const &type)
{
  lightRet = this->sceneMgr->createLight();
  lightRet->setType(type);
  switch (type)
    {
      case (Ogre::Light::LT_DIRECTIONAL) :
	lightRet->setDirection(Ogre::Vector3::ZERO - offset);
      break;
      case (Ogre::Light::LT_POINT) :
	lightRet->setAttenuation(power,
				 0,
				 1.0f / (power * power),
				 1.0f / (power * power));
	break;
      default :
      break;
    }
  lightRet->setSpecularColour(colorSpec);
  lightRet->setDiffuseColour(colorDif);
  lightRet->detachFromParent();
  Ogre::SceneNode *lightNode = node->createChildSceneNode(offset);
  lightNode->attachObject(lightRet);
  return (lightNode);
}


Ogre::SceneNode		*Gauntlet::Displayer::createEntity(std::string const &path,
								  std::string const &name,
								  std::string const &matName,
								  bool hasShadow)
{
  Ogre::Entity		*entity = this->sceneMgr->createEntity(name.c_str(), path.c_str());
  Ogre::SceneNode	*node = this->sceneMgr->getRootSceneNode()->createChildSceneNode(name + "Node");

  if (!matName.empty())
    entity->setMaterialName(matName);
  if (hasShadow && !entity->hasEdgeList())
    {
      entity->getMesh()->setAutoBuildEdgeLists(true);
      entity->getMesh()->buildEdgeList();
    }
  entity->setCastShadows(hasShadow);
  node->attachObject(entity);


  return (node);
}

void			Gauntlet::Displayer::deleteEntity(Ogre::SceneNode *node, Ogre::Entity *ent)
{
  node->detachObject(ent);
  this->sceneMgr->destroyEntity(ent);
  this->sceneMgr->destroySceneNode(node);
}

void			Gauntlet::Displayer::deleteLight(Ogre::SceneNode *node, Ogre::Light *light)
{
  node->detachObject(light);
  this->sceneMgr->destroyLight(light);
  this->sceneMgr->destroySceneNode(node);
}

void			Gauntlet::Displayer::startRendering()
{
  this->root->startRendering();
}

void			Gauntlet::Displayer::createGround()
{
  Ogre::Plane		plane(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("groundMesh",
						Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
						plane,
						225, 225,
						10, 10,
						true,
						1, 10, 10,
						Ogre::Vector3::UNIT_Z);

}

void			Gauntlet::Displayer::addFrameListener(Gauntlet::WindowManager *winMgr)
{
  this->root->addFrameListener(winMgr);
}

void			Gauntlet::Displayer::takeEvent(const Gauntlet::Event &event)
{
  Gauntlet::Model	*model;

  for (auto & ent : event._entities)
    {
      if ((model = ent->getPtr<Gauntlet::Model>()) != nullptr)
	{
	  //model->body->setOrientation(Ogre::Quaternion(Ogre::Math::ACos(model->dirVec.dotProduct(Ogre::Vector3::UNIT_X)) *
	//						       ((model->dirVec.z >= 0) ? (-1) : (1)),
	//					       Ogre::Vector3::UNIT_Y));
	}

    }
}