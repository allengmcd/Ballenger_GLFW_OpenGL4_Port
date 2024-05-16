#include "ge_levelConfig.h"

LevelConfig::LevelConfig(){}
LevelConfig::~LevelConfig(){}


void LevelConfig::LoadLevel(int level)
{
    std::ifstream f("../../../../Levels/level01.json");
    json data = json::parse(f);

    auto welcomeBracket = data.template get<LevelFile::Welcome>();
    CurrentLevel = welcomeBracket.get_level();
}