#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <vector>
#include "CNeuralNet.h"
#include "CGenAlg.h"

class Sweeper {
public:
  Sweeper();
  
  double posx, posy;
  
  // Rotation, value between 0 and 1
  double rotation;
  
  CNeuralNet brain;
  
  int minesSweeped;
  
  // Resets fitness
  void reset();
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
  
  CGenAlg *genAlg;
  vector<SGenome> population;
  
  void initGenAlg();
};

void doTurn(Gamestate *gs);
void brainTransplant(Gamestate *gs);

#endif
