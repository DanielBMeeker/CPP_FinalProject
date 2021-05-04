#ifndef COMPLETEGAME_H
#define COMPLETEGAME_H
#include "game.h"

class CompleteGame : public Game
{
private:
    double price;
    string name;
    string console;
    long long upc;
public:
    CompleteGame(double price, string name, string console, long long upc);
    double getPrice();
};

#endif // COMPLETEGAME_H
