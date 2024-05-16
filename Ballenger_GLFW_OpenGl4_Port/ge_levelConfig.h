#pragma once

#include "Globals.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include "ge_levelFile.h"

using json = nlohmann::json;



class LevelConfig
{
public:
	LevelConfig();
	~LevelConfig();

    void LoadLevel(int level);

    LevelFile::Level CurrentLevel;
private:

};