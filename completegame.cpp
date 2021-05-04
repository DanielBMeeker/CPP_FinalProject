#include "completegame.h"

CompleteGame::CompleteGame(double price, string name, string console, long long upc)
    : Game(name, console, upc),
      price(price), name(name), console(console), upc(upc)
{

}
double CompleteGame::getPrice() {
    return price;
}
