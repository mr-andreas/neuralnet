#include <iostream>
#include <vector>

#include "gfx.h"

using namespace std;

typedef struct {
  int inputCount;
  
  unsigned int threshold;
  unsigned int weights[4];
} neuron_t;

int oldmain(int argc, char **argv) {
    neuron_t hiddenLayer[4];
    neuron_t outputLayer[2];
  
    std::cout << "Hello, world!" << std::endl;
    return 0;
}

int main(int argc, char **argv) {
  srand(time(NULL));
  
  sdlgamestate_t g;
  Gamestate gs(1024, 768);
  g.gamestate = &gs;
  
  for(int i = 0; i < 40; i++) {
    Mine m;
    m.posx = rand()%gs.boardWidth;
    m.posy = rand()%gs.boardHeight;
    
    gs.mines.push_back(m);
  }
  
  for(int i = 0; i < 20; i++) {
    Sweeper s;
    s.posx = rand()%gs.boardWidth;
    s.posy = rand()%gs.boardHeight;
    
    gs.sweepers.push_back(s);
  }
  
  return sdlMainLoop(&g);
}
