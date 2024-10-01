//
// Created by verba on 25.07.2024.
//

#include <conio.h>
#include <iostream>
#include <fstream>
#include "Scripts.h"
#include "json.hpp"
#include "Item.h"
#include "Player.h"

using namespace std;
using json = nlohmann::json;

int Scripts::menuScriptWithoutMessage(std::vector<std::string> menuItems) {
    int selectedItem = 0;
    char key;

    while (true) {
        system("cls");

        for (int i = 0; i < menuItems.size(); i++) {
            if (i == selectedItem) {
                cout << "> " << menuItems[i] << " <" << endl;
            } else {
                cout << "  " << menuItems[i] << endl;
            }
        }

        key = _getch();

        if (key == 72) {
            if (selectedItem > 0) {
                selectedItem--;
            }
        } else if (key == 80) {
            if (selectedItem < menuItems.size() - 1) {
                selectedItem++;
            }
        } else if (key == '\r') {
            system("cls");
            return selectedItem;
        }
    }
}

int Scripts::menuScriptWithMessage(std::vector<std::string> menuItems, std::string message) {
    int selectedItem = 0;
    char key;

    while (true) {
        system("cls");
        cout << message + '\n';
        for (int i = 0; i < menuItems.size(); i++) {
            if (i == selectedItem) {
                cout << "> " << menuItems[i] << " <" << endl;
            } else {
                cout << "  " << menuItems[i] << endl;
            }
        }

        key = _getch();

        if (key == 72) {
            if (selectedItem > 0) {
                selectedItem--;
            }
        } else if (key == 80) {
            if (selectedItem < menuItems.size() - 1) {
                selectedItem++;
            }
        } else if (key == '\r') {
            system("cls");
            return selectedItem;
        }
    }
}

void Scripts::pause() {
    std::cout << "Press Enter to continue.\n";
    while(true){
        char key = _getch();
        if(key == '\r'){
            system("cls");
            break;
        }
    }
}

json serializeItem(const Item* item) {
    if (item == nullptr) {
        return nullptr;
    }
    return {
            {"kind", item->kind},
            {"price", item->price},
            {"value", item->value}
    };
}

Item* deserializeItem(const json& j) {
    if (j.is_null()) {
        return nullptr;
    }
    return new Item(static_cast<KindOfItem>(j.at("kind").get<int>()), j.at("price").get<int>(), j.at("value").get<int>());
}

void Scripts::savePlayerToJson(const Player& player) {
    std::ifstream fileIn("saves.json");
    json j;

    if (fileIn.is_open()) {
        fileIn >> j;
        fileIn.close();
    }

    if (!j.is_array()) {
        j = json::array();
    }
    json playerJson;
    playerJson["nickname"] = player.nickname;
    playerJson["monstersKilled"] = player.monstersKilled;
    playerJson["numberOfKilledKobolds"] = player.numberOfKilledKobolds;
    playerJson["numberOfKilledGoblin"] = player.numberOfKilledGoblin;
    playerJson["numberOfKilledDemons"] = player.numberOfKilledDemons;
    playerJson["numberOfKilledOrks"] = player.numberOfKilledOrks;
    playerJson["numberOfGatheredCoins"] = player.numberOfSpendCoins;
    playerJson["numberOfTakenDamage"] = player.numberOfTakenDamage;
    playerJson["numberOfMadeDamage"] = player.numberOfMadeDamage;
    playerJson["currentHitPoints"] = player.currentHitPoints;
    playerJson["maxHitPoints"] = player.maxHitPoints;
    playerJson["attackPower"] = player.atackPower;
    playerJson["head"] = serializeItem(player.head);
    playerJson["hand"] = serializeItem(player.hand);
    playerJson["body"] = serializeItem(player.body);
    playerJson["inventory"] = json::array();

    for (const Item* item : player.inventory) {
        playerJson["inventory"].push_back(serializeItem(item));
    }

    playerJson["numberOfCoins"] = player.numberOfCoins;

    bool playerFound = false;
    for (auto& existingPlayer : j) {
        if (existingPlayer["nickname"] == player.nickname) {
            existingPlayer = playerJson;
            playerFound = true;
            break;
        }
    }
    if (!playerFound) {
        j.push_back(playerJson);
    }

    std::ofstream file("saves.json");
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    }
}



Player* Scripts::loadPlayerFromJson(string nickname) {
    std::ifstream file("saves.json");
    json j;
    if (file.is_open()) {
        file >> j;
        file.close();
    }

    Player *player;

    for (const auto& item : j.items()) {
        if(item.value().at("nickname").get<string>() == nickname){
            player = new Player(item.value().at("nickname").get<std::string>());
            player->monstersKilled = item.value().at("monstersKilled").get<unsigned int>();
            player->numberOfKilledKobolds = item.value().at("numberOfKilledKobolds").get<unsigned int>();
            player->numberOfKilledGoblin = item.value().at("numberOfKilledGoblin").get<unsigned int>();
            player->numberOfKilledDemons = item.value().at("numberOfKilledDemons").get<unsigned int>();
            player->numberOfKilledOrks = item.value().at("numberOfKilledOrks").get<unsigned int>();
            player->numberOfSpendCoins = item.value().at("numberOfGatheredCoins").get<unsigned int>();
            player->numberOfTakenDamage = item.value().at("numberOfTakenDamage").get<unsigned int>();
            player->numberOfMadeDamage = item.value().at("numberOfMadeDamage").get<unsigned int>();
            player->currentHitPoints = item.value().at("currentHitPoints").get<int>();
            player->maxHitPoints = item.value().at("maxHitPoints").get<int>();
            player->atackPower = item.value().at("attackPower").get<int>();
            player->head = deserializeItem(item.value().at("head"));
            player->hand = deserializeItem(item.value().at("hand"));
            player->body = deserializeItem(item.value().at("body"));

            player->inventory.clear();
            for (const auto& item_json : item.value().at("inventory")) {
                player->inventory.push_back(deserializeItem(item_json));
            }

            player->numberOfCoins = item.value().at("numberOfCoins").get<unsigned int>();
            break;
        }
    }

    return player;
}


std::vector<std::string> Scripts::getAllSavedPlayers(){
    std::ifstream file("saves.json");
    json j;
    if (file.is_open()) {
        file >> j;
        file.close();
    }

    vector<string>playersNicknames;

    for (const auto& item : j.items()) {
        playersNicknames.push_back(item.value().at("nickname").get<string>());
    }
    return playersNicknames;
}