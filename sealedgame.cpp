#include "sealedgame.h"

SealedGame::SealedGame(double price, string name, string console, long long upc)
    : Game(name, console, upc),
      price(price), name(name), console(console), upc(upc)
{

}
double SealedGame::getPrice() {
    return price;
}
