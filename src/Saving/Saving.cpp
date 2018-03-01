//
// Created by mymy on 29/05/17.
//

#include <CoreGame.hpp>
#include "Systems/Saving/Saving.hpp"

void    Gauntlet::Saving::takeEvent(Gauntlet::Event const &event)
{
  if (event._type == EventType::VICTORY || event._type == EventType::DEFEAT)
      this->saveScore();
}

void    Gauntlet::Saving::saveScore() const
{
  std::ifstream		f("../saving/scores.txt");
  Json::Value scores(Json::arrayValue);

  if (!f.is_open())
    {
      std::ofstream ofs("../saving/scores.txt");
      Json::Value root;
      scores.append(CoreGame::core->score);
      root["score"] = scores;
      ofs << root;
      ofs.close();
    }
  else
    {
      f >> scores;
      f.close();
      scores["score"].append(CoreGame::core->score);
      std::ofstream ofs("../saving/scores.txt",  std::ios::out | std::ios::trunc);
      ofs << scores;
      ofs.close();
    }
}

void	Gauntlet::Saving::fillScores(std::vector<int> &scores)
{
  std::ifstream f("../saving/scores.txt");
  Json::Value scoresJson(Json::arrayValue);

  if (f.is_open())
    {
      f >> scoresJson;
      f.close();
      for (auto it = scoresJson["score"].begin(); it != scoresJson["score"].end(); ++it)
	{
	  int sc = (*it).asInt();
	  scores.push_back(sc);
	}
    }
}