#ifndef LOOSEGAME_H
#define LOOSEGAME_H
#include "game.h"


class LooseGame : public Game
{
private:
    double price;
    string name;
    string console;
    long long upc;
public:
    LooseGame(double price, string name, string console, long long upc);
    double getPrice();
};

#endif // LOOSEGAME_H
