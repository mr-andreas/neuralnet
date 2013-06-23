#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <vector>
#include "CNeuralNet.h"

class Sweeper {
public:
  Sweeper();
  
  double posx, posy;
  
  // Rotation, value between 0 and 1
  double rotation;
  
  CNeuralNet brain;
};

class Gamestate {
public:
  Gamestate(int boardWidth, int boardHeight);
  
  int boardWidth, boardHeight;
  
  std::vector<Sweeper> sweepers;
};

void doTurn(Gamestate *gs);

#endif
