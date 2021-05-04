#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;


class Game
{
private:
    string name;
    string console;
    long long upc;
public:
    Game(string name, string console, long long upc);
};

#endif // GAME_H
