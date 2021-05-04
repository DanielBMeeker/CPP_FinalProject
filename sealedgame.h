#ifndef SEALEDGAME_H
#define SEALEDGAME_H
#include "game.h"


class SealedGame : public Game
{
private:
    double price;
    string name;
    string console;
    long long upc;
public:
    SealedGame(double price, string name, string console, long long upc);
    double getPrice();
};

#endif // SEALEDGAME_H
