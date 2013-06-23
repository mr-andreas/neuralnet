#include "gamestate.h"

#include <stdlib.h>

Sweeper::Sweeper() {
  int posx = 0;
  int posy = 0;
}

Gamestate::Gamestate(int boardWidth, int boardHeight) {
  this->boardWidth  = boardWidth;
  this->boardHeight = boardHeight;
}
