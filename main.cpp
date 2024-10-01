/*
#include <iostream>
#include "Game.h"
int main() {
    Game* game = new Game();
    game->run();
    return 0;
}
*/

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"

using namespace std;


#include "Game.h"
#include "Scripts.h"

int main() {
    srand(time(0));
    Game* game = new Game();
    game->run();

}
