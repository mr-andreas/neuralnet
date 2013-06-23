#ifndef _GFX_H
#define _GFH_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "gamestate.h"

typedef struct {
  Gamestate *gamestate;
  
  SDL_Surface *screen;
  struct {
    SDL_Surface *sweeper;
  } bitmaps;
  
  
} sdlgamestate_t;

int sdlMainLoop(sdlgamestate_t *g);

#endif
