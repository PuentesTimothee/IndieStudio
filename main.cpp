//
// main.cpp for Indie in /home/Mymy/Modules/C++/cpp_indie_studio
// 
// Made by My-Lan Aragon
// Login   <Mymy@epitech.net>
// 
// Started on  Wed May  3 14:06:57 2017 My-Lan Aragon
// Last update Thu May 11 15:42:53 2017 Mymy Aragon
//

#include <iostream>
#include "CoreGame.hpp"

int	main(int, char **, char **env)
{
  if (env == nullptr || *env == nullptr)
    {
      std::cerr << "Pas d'env !" << std::endl;
      return (1);
    }
  try
 {
      Gauntlet::CoreGame::core = std::make_unique<Gauntlet::CoreGame>();
      Gauntlet::CoreGame::core->go();
   }
catch (std::exception const& e)
  {
      std::cerr << e.what() << std::endl;
  }
  return (0);
}
