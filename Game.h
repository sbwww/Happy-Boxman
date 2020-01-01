#pragma once
#include "GameMap.h"
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory.h>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "Timer.h"
#define OK 1
#define ERROR -1
#define OVERFLOW -1
#define SURRENDER -2
typedef int Status;
#define WINDOW_NAME "Box Man"
#define QUIT -1

class Game : virtual protected Game_Map {
  public:
    Game(){};
    ~Game(){};
    Status Play(Timer& timer);

  protected:
    Status Push(int ch);
    bool Judge(void);
    std::stack<state> stk;
    bool is_game_finished;
};

class Random_Game : virtual public Game, virtual protected Random_Game_Map {
  public:
    Random_Game(int height = 10, int length = 10)
        : Game(), Random_Game_Map(height, length){};
    ~Random_Game(){};
    Status Play(Timer& timer);

  protected:
};

class Normal_Game : virtual public Game, virtual protected Normal_Game_Map {
  public:
    Normal_Game(int game_num = 1) : Game(), Normal_Game_Map(game_num){};
    ~Normal_Game(){};

  protected:
};
