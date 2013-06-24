#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <vector>
#include <list>
#include "CNeuralNet.h"
#include "CGenAlg.h"

class Sweeper {
public:
  Sweeper();
  
  double posx, posy;
  
  // Rotation, counted in radians
  double rotation;
  
  CNeuralNet brain;
  
  int minesSweeped;
  bool dead;
  int turnsLeftToAvilableShot;
  int sweepersShot;
  int shotsLeft;
  
  // Resets fitness
  void reset();
};

class Mine {
public:
  Mine();
  
  int posx, posy;
  bool deleted;
  
  void reset();
};

typedef struct {
  int posx, posy;
  
  // Rotation, counted in radians
  double rotation;
  
  Sweeper *shooter;
} Bullet;

class Gamestate {
public:
  Gamestate(int boardWidth, int boardHeight);
  
  int boardWidth, boardHeight;
  
  std::vector<Sweeper> sweepers;
  std::vector<Mine> mines;
  std::list<Bullet> bullets;
  
  CGenAlg *genAlg;
  vector<SGenome> population;
  
  void initGenAlg();
};

void doTurn(Gamestate *gs);
void randomize(Gamestate *gs);
void brainTransplant(Gamestate *gs);

#endif
