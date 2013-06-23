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
  sdlgamestate_t g;
  Gamestate gs(640, 480);
  g.gamestate = &gs;
  
  gs.sweepers.push_back(Sweeper());
  gs.sweepers[0].posx = 320;
  gs.sweepers[0].posy = 240;
  
  return sdlMainLoop(&g);
}
