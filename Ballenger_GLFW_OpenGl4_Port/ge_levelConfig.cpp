#include "ge_levelConfig.h"

LevelConfig::LevelConfig(){}
LevelConfig::~LevelConfig(){}


void LevelConfig::LoadLevel(int level)
{
    std::ifstream f("Levels/level01.json");
    json data = json::parse(f);

    auto ballengerLevelConfig = data.template get<LevelFile::BallengerLevelConfig>();
    CurrentLevel = ballengerLevelConfig.get_level();
    CurrentStage = CurrentLevel.get_stages().at(0); // TODO: this might be null sometimes
}