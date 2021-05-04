#include "loosegame.h"

LooseGame::LooseGame(double price, string name, string console, long long upc)
    : Game(name, console, upc),
      price(price), name(name), console(console), upc(upc)
{

}

double LooseGame::getPrice() {
    return price;
}
