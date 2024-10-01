#include "Monster.h"
#include <cstdlib>
#include <ctime>

Monster::Monster(MonsterRace race) {
    this->nameOfMonster = race;
    int hasSomething = rand()%2;
    if(hasSomething == 1)
        inventory.push_back(new Item(static_cast<KindOfItem>(rand() % 8)));

    numberOfCoins = rand() % 21 + 1;

    switch(race){
        case Goblin:
            this->maxHitPoints = 20;
            this->atackPower = 5;
            break;
        case Ork:
            this->maxHitPoints = 65;
            this->atackPower = 7;
            break;
        case Demon:
            this->maxHitPoints = 80;
            this->atackPower = 10;
            break;
        case Kobold:
            this->maxHitPoints = 40;
            this->atackPower = 6;
            break;
    }

    this->currentHitPoints = this->maxHitPoints;

    switch (nameOfMonster){
        case Goblin:
            nameOfMonsterString = "Goblin";
            break;
        case Kobold:
            nameOfMonsterString  = "Kobold";
            break;
        case Ork:
            nameOfMonsterString  = "Ork";
            break;
        case Demon:
            nameOfMonsterString  = "Demon";
    }
}
