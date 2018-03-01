//
// ManageFile.cpp for plazza in /home/benito/rendu/cpp/cpp_plazza/sources
//
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Mon Apr 17 10:56:47 2017 benito
// Last update Sun Apr 30 00:17:34 2017 Pierre Zawadil
//

#include <stdexcept>
#ifdef __unix__
#include <dirent.h>
#elif _WIN32
#include <Windows.h>
#endif
#include <cstring>
#include <string>
#include "File/ManageFile.hpp"

ManageFile::ManageFile(std::string const& file) : _fileName(file)
{}

ManageFile::~ManageFile()
{}

#ifdef __unix__
void ManageFile::listFiles(std::string const& path, std::vector<std::string> &files)
{
  DIR *dpdf;
  struct dirent *epdf;

  dpdf = opendir(path.c_str());
  if (dpdf != NULL)
  {
    while ((epdf = readdir(dpdf)) != NULL)
    {
      if (epdf->d_type == DT_DIR && strstr(epdf->d_name, "..") == NULL && strstr(epdf->d_name,".") == NULL)
      {
        std::cout << "tryin "<< path + "/" + epdf->d_name + "/" << std::endl;
        listFiles(path + "/" + epdf->d_name + "/", files);
      }
      if (epdf->d_type == DT_REG)
      {
        files.push_back(path + epdf->d_name);
      }
    }
  }
  closedir(dpdf);
}
#elif _WIN32
void ManageFile::listFiles(std::string const& path, std::vector<std::string> &files)
{
	HANDLE _hfind;
	WIN32_FIND_DATA FindFileData;

	_hfind = FindFirstFile(path.c_str(), &FindFileData);
	if (_hfind != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(_hfind, &FindFileData))
			{
				if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && 
					strstr(FindFileData.cFileName, "..") == NULL && 
					strstr(FindFileData.cFileName, ".") == NULL)
					{
						std::cout << "tryin " << path + "/" + FindFileData.cFileName + "/" << std::endl;
						listFiles(path + "/" + FindFileData.cFileName + "/", files);
					}
				if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_NORMAL)
					{
						files.push_back(path + FindFileData.cFileName);
					}
			}
		}
	FindClose(_hfind);
}

#endif
std::string		ManageFile::readFile() const
{
  std::ifstream		f(_fileName.c_str());
  std::string		buffer;

  if (!f.is_open())
    throw std::runtime_error("Couldn't open file " + _fileName);
  f.seekg(0, std::ios::end);
  buffer.resize(f.tellg());
  f.seekg(0);
  f.read((char *)buffer.data(), buffer.size());
  f.close();
  return (buffer);
}

std::string		ManageFile::readFifo() const
{
  std::ifstream		f(_fileName.c_str());
  std::string		buffer;
  std::string		line;

  if (!f.is_open())
    throw std::runtime_error("Couldn't open file " + _fileName);
#ifdef __unix__
  while (std:: getline(f, line))
    buffer += line;
#elif _WIN32
  while (getline(f, line))
	  buffer += line;
#endif
  return (buffer);

}

std::string		ManageFile::readStdin()
{
  std::string		buffer;

#ifdef __unix__
  std::getline(std::cin, buffer);
#elif _WIN32
  getline(std::cin, buffer);
#endif
  if (std::cin.eof())
    throw std::runtime_error("");
  if (buffer == "")
    return (" ");
  return (buffer);
}

void		ManageFile::writeFile(std::string const& buffer) const
{
  std::ofstream f(_fileName.c_str());

  if (f.is_open())
    {
      f.write(buffer.data(), buffer.size());
      f.close();
    }
}

void		ManageFile::openFile(std::string const& file)
{
  _fileName = file;
}
