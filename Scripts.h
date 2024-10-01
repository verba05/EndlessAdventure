//
// Created by verba on 25.07.2024.
//

#ifndef TESTGAME_SCRIPTS_H
#define TESTGAME_SCRIPTS_H

#include <string>
#include <vector>
#include "Player.h"

class Scripts {
public:
    static void pause();
    static int menuScriptWithMessage(std::vector<std::string> menuItems, std::string message);
    static int menuScriptWithoutMessage(std::vector<std::string> menuItems);
    static void savePlayerToJson(const Player &player);
    static Player *loadPlayerFromJson(std::string nickname);
    static std::vector<std::string> getAllSavedPlayers();
};


#endif //TESTGAME_SCRIPTS_H
