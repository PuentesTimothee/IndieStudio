
project(Indie)
cmake_minimum_required(VERSION 2.6)
if(WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		$ENV{OGRE_HOME}/Samples/include
	)
endif(WIN32)

if(UNIX)
    set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/")
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -g3")
endif(UNIX)

if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_CXX_FLAGS "--std=c++14 ${CMAKE_CXX_FLAGS}")
else ()
    set (CMAKE_CXX_STANDARD 14)
endif ()

set(PROJECT_CMAKE_SCRIPT cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/${PROJECT_CMAKE_SCRIPT})
include_directories ("./include/")
include_directories ("./json/")

if(UNIX)
    include_directories (SYSTEM "/usr/share/OGRE/Samples/Common/include/")
endif(UNIX)

find_package(OGRE REQUIRED)
include_directories (SYSTEM ${OGRE_INCLUDE_DIRS})

find_package(Bullet REQUIRED)
include_directories (SYSTEM ${BULLET_INCLUDE_DIRS})

find_package(OIS REQUIRED)

find_package(CEGUI REQUIRED COMPONENTS OGRE)
if(NOT CEGUI_FOUND)
  message(SEND_ERROR "Failed to find CEGUI.")
endif()
message(STATUS ${CEGUI_INCLUDE_DIRS})
include_directories(SYSTEM ${CEGUI_INCLUDE_DIRS})

# Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
  if (WIN32 OR APPLE)
    set(Boost_USE_STATIC_LIBS TRUE)
  else ()
    # Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
    set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
  endif ()
  if (MINGW)
    # this is probably a bug in CMake: the boost find module tries to look for
    # boost libraries with name libboost_*, but CMake already prefixes library
    # search names with "lib". This is the workaround.
    set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
  endif ()
  set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
  # Components that need linking (NB does not include header-only components like bind)
  set(OGRE_BOOST_COMPONENTS thread date_time)
  find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
  if (NOT Boost_FOUND)
    # Try again with the other type of libs
    set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
    find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
  endif()
  find_package(Boost COMPONENTS system QUIET)

  # Set up referencing of Boost
  include_directories(SYSTEM ${Boost_INCLUDE_DIR})
  add_definitions(-DBOOST_ALL_NO_LIB)
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()

SET(SOURCES
        main.cpp

        src/Factory/Factory.cpp
    	src/Entity/Entity.cpp
        src/CustomMath.cpp

        src/Animation/AnimationManager.cpp

        src/Displayer/Displayer.cpp
        src/Displayer/WindowManager.cpp

        src/CoreGame.cpp

        src/Components/Model.cpp
        src/Components/Animation.cpp
        src/Components/EntityState.cpp
        src/Components/Stats.cpp
        src/Components/Weapon.cpp
        src/Components/PowerUpStats.cpp
        src/Components/AIScript
        src/Components/LightSource.cpp

        src/Entity/Character/Pig.cpp
        src/Entity/Character/Warrior.cpp
        src/Entity/Character/Priest.cpp
        src/Entity/Character/Valkyrie.cpp
        src/Entity/Character/Assassin.cpp
        src/Entity/Character/Boss.cpp
        src/Entity/Character/MiniBoss.cpp

        src/Entity/Environement/Torch.cpp
        src/Entity/Environement/Wall.cpp
        src/Entity/Environement/Ground.cpp

        src/Entity/Effect/Attack.cpp
        src/Entity/Effect/DistAttack.cpp
        src/Entity/Effect/ZoneDistAttack.cpp
        src/Entity/Effect/CaCAttack.cpp
        src/Entity/Effect/HealAttack.cpp

        src/Entity/Collectable/Icecream.cpp
        src/Entity/Collectable/Coin.cpp
        src/Entity/Collectable/Meat.cpp
        src/Entity/Collectable/Donuts.cpp

        src/Entity/Destroyable/Chest.cpp
        src/Entity/Destroyable/Crate.cpp
        src/Entity/Destroyable/Vase.cpp

        src/Input/InputManager.cpp
        src/Input/KeyListener.cpp

        src/Collision/CollisionManager.cpp
        src/Collision/OgreMotionState.cpp
        src/Collision/CollisionBody.cpp
        src/Collision/HitBox.cpp
        src/Collision/CollisionObject.cpp
        src/Collision/CollisionConvertion.cpp
        src/Collision/CollisionCallBack.cpp

        src/Systems/SoundSystem.cpp

        src/Event/Event.cpp
        src/File/ManageFile.cpp

        src/Menu/IMenu.cpp
        src/Menu/MenuManager.cpp
        src/Menu/GameMenu.cpp
        src/Menu/EndGame.cpp
        src/Menu/MainMenu.cpp
        src/Menu/SplashScreen.cpp
	
        src/RP/RP.cpp

        src/AI/AI.cpp

        src/Saving/Saving.cpp

        src/Movement/MovementMgr.cpp

        src/Attack/AttackManager.cpp

        src/Map/MapLoader.cpp

        src/Loot/LootManager.cpp

        src/Menu/Hud.cpp
        src/Entity/Collectable/Ananas.cpp
	src/Entity/Collectable/Hamburger.cpp
	src/Entity/Character/Ghost.cpp

        json/jsoncpp.cpp
	)

add_executable (Indie WIN32 ${SOURCES})

target_link_libraries(Indie
  ${OGRE_LIBRARIES}
  ${OGRE_Overlay_LIBRARIES}
  ${OIS_LIBRARY}
  ${BOOST_LIBRARIES}

  ${BULLET_LIBRARIES}

  ${OgreBullet_LIBRARIES}
  
  -lboost_system
  -lsfml-audio
  ${CEGUI_LIBRARIES}
  ${CEGUI_OgreRenderer_LIBRARIES})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
 
# post-build copy for win32
if(WIN32 AND NOT MINGW)
	add_custom_command( TARGET Indie PRE_BUILD
		COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
	add_custom_command( TARGET Indie POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
endif(MINGW OR UNIX)
 
if(WIN32)
 
	install(TARGETS Indie
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/Media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
        # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
        # so you'll have to change that to make it work with 1.7.1
	install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
   # as of sdk 1.7.2 we need to copy the boost dll's as well
   # because they're not linked statically (it worked with 1.7.1 though)
   install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
      ${Boost_THREAD_LIBRARY_RELEASE}
      DESTINATION bin
      CONFIGURATIONS Release RelWithDebInfo
   )
 
   install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
      ${Boost_THREAD_LIBRARY_DEBUG}
      DESTINATION bin
      CONFIGURATIONS Debug
   )
endif(WIN32)

if(UNIX)
 
	install(TARGETS Indie
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/build/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/build/plugins.cfg
		${CMAKE_SOURCE_DIR}/build/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)

    include(CPack)

endif(UNIX)
