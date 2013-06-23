#include "gfx.h"

#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_timer.h>
#include <math.h>

const int FRAMES_PER_SECOND = 60;
const int FRAMERATE_IN_MS = 1000/FRAMES_PER_SECOND;
const char* WINDOW_TITLE = "SDL Start";

void plotSweeper(sdlgamestate_t *g, const Sweeper &sweeper) {
  // Part of the bitmap that we want to draw
  SDL_Rect source;
  source.x = 0;
  source.y = 0;
  source.w = 65;
  source.h = 44;

  // Part of the screen we want to draw the sprite to
  SDL_Rect destination;
  destination.x = sweeper.posx;
  destination.y = sweeper.posy;
  destination.w = 65;
  destination.h = 44;
  
  SDL_Surface *rotated = rotozoomSurface(g->bitmaps.sweeper, sweeper.rotation*180.0/M_PI-90.0, 1, 1);
  SDL_BlitSurface(rotated, &source, g->screen, &destination);
  
  SDL_FreeSurface(rotated);
}

void plotSweepers(sdlgamestate_t *g) {
  const std::vector<Sweeper> &s(g->gamestate->sweepers);
  
  for(std::vector<Sweeper>::const_iterator i = s.begin(); i != s.end(); i++) {
    plotSweeper(g, *i);
  }
}

void plotMines(const sdlgamestate_t *g) {
  const std::vector<Mine> &s(g->gamestate->mines);
  
  for(std::vector<Mine>::const_iterator i = s.begin(); i != s.end(); i++) {
    // Part of the bitmap that we want to draw
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 20;
    source.h = 20;

    // Part of the screen we want to draw the sprite to
    SDL_Rect destination;
    destination.x = i->posx;
    destination.y = i->posy;
    destination.w = 20;
    destination.h = 20;
    
    SDL_BlitSurface(g->bitmaps.mine, &source, g->screen, &destination);
  }
}

void init(sdlgamestate_t *g) {
  SDL_Init( SDL_INIT_VIDEO );

  g->screen = SDL_SetVideoMode(
    g->gamestate->boardWidth, g->gamestate->boardHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF 
  ); 
  SDL_WM_SetCaption( WINDOW_TITLE, 0 );

  g->bitmaps.sweeper = IMG_Load("/home/ante/dev/neuralnet/res/sweeper.png");
  if(!g->bitmaps.sweeper) {
    printf("No bitmap :(\n");
    exit(1);
  }
  g->bitmaps.mine = IMG_Load("/home/ante/dev/neuralnet/res/mine.png");
}

int sdlMainLoop(sdlgamestate_t *g) {
  init(g);

  SDL_Event event;
  bool gameRunning = true;
  unsigned int startTime, endTime;

  while (gameRunning) {
    startTime = SDL_GetTicks();
    
    if (SDL_PollEvent(&event)) { 
      if (event.type == SDL_QUIT) {
        gameRunning = false;
      }
    }

    SDL_FillRect(g->screen, NULL, SDL_MapRGB(g->screen->format, 255, 255, 255));
    doTurn(g->gamestate);
    plotMines(g);
    plotSweepers(g);
    
    SDL_Flip(g->screen);
    
    endTime = SDL_GetTicks();
    
    SDL_Delay(FRAMERATE_IN_MS - (endTime - startTime));
  }

  SDL_FreeSurface(g->bitmaps.sweeper);
  SDL_Quit();
  
  return 0;
}