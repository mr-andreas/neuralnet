#include "gamestate.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Sweeper::Sweeper() {
  int posx = 0;
  int posy = 0;
}

Gamestate::Gamestate(int boardWidth, int boardHeight) {
  this->boardWidth  = boardWidth;
  this->boardHeight = boardHeight;
}

void moveSweeper(Gamestate *gs, Sweeper &sweeper) {
  vector<double> vals(4);
  vals[0] = 0.0;
  vals[1] = 0.0;
  vals[3] = 0.0;
  vals[4] = 0.0;
  vector<double> output = sweeper.brain.Update(vals);
  
  double lTrack, rTrack;
//   lTrack = rand() / ((double)RAND_MAX/2) - 1.0;
//   rTrack = rand() / ((double)RAND_MAX/2) - 1.0;
  
  lTrack = output[0];
  rTrack = output[1];
  
  double rotForce = lTrack - rTrack;
  if(rotForce < -0.3) rotForce = -0.3;
  if(rotForce > 0.3) rotForce = 0.3;

  sweeper.rotation += rotForce;
  
  double speed = lTrack + rTrack; 

  //update Look At 
  double vLookAtX = cos(sweeper.rotation);
  double vLookAtY = -sin(sweeper.rotation);

  //update position
  sweeper.posx += vLookAtX * speed;
  sweeper.posy += vLookAtY * speed;
  
//   printf(
//     "Rotation: %f speed %f pos %d,%d lookat %f,%f degress %f\n", sweeper.rotation, speed, 
//     (int)sweeper.posx, (int)sweeper.posy, vLookAtX, vLookAtY, sweeper.rotation*180.0/M_PI
//   );
}

void moveSweepers(Gamestate *gs) {
  for(std::vector<Sweeper>::iterator i = gs->sweepers.begin(); i != gs->sweepers.end(); i++) {
    moveSweeper(gs, *i);
  }
}

void doTurn(Gamestate* gs) {
  moveSweepers(gs);
}
