//
// Made by benito
//

#ifndef MANAGE_FILE_HPP
# define MANAGE_FILE_HPP

#include <iostream>
#include <fstream>
#include <vector>

class		ManageFile
{
private:
  std::string	_fileName;
public:
  ManageFile() {};
  ManageFile(std::string const&);
  ~ManageFile();
  std::string		readFile() const;
  std::string		readFifo() const;
  void			writeFile(std::string const&) const;
  void			openFile(std::string const&);
  static std::string	readStdin();
  static void listFiles(std::string const&,
                        std::vector<std::string>&);
};

# endif //MANAGE_FILE_HPP
