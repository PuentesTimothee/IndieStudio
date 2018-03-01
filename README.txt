Pour installer ogre (1.9):

NE PAS ETRE SUR BLINUX !!!!

https://github.com/OancaAndrei/ogre_build
	./install_dependencies.sh
	git clone https://github.com/OGRECave/ogre
	in build.sh
	   replace line par "make -DCMAKE_BUILD_TYPE=Release -DOGRE_BUILD_SAMPLES=TRUE .."
	./build.sh
	cd ogre
	mkdir build
	cd build
	cmake ..
	make -j2
	sudo make install
	/!\ DONE /!\
	
Dépendances:
 - Ogre (affichage)
 - SFML (son)
 - bullet (physique)
 - OIS (touches)
 - CEGUI (menu/hud)
