#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <vector>

class Sweeper {
public:
  Sweeper();
  
  int posx, posy;
};

class Gamestate {
public:
  Gamestate(int boardWidth, int boardHeight);
  
  int boardWidth, boardHeight;
  
  std::vector<Sweeper> sweepers;
};

#endif
