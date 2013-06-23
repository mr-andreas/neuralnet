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

typedef struct {
  int posx, posy;
} Mine;

class Gamestate {
public:
  Gamestate(int boardWidth, int boardHeight);
  
  int boardWidth, boardHeight;
  
  std::vector<Sweeper> sweepers;
  std::vector<Mine> mines;
};

void doTurn(Gamestate *gs);

#endif
