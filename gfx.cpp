#include "gfx.h"

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
  
  SDL_BlitSurface(g->bitmaps.sweeper, &source, g->screen, &destination);
}

void plotSweepers(sdlgamestate_t *g) {
  const std::vector<Sweeper> &s(g->gamestate->sweepers);
  
  for(std::vector<Sweeper>::const_iterator i = s.begin(); i != s.end(); i++) {
    plotSweeper(g, *i);
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
}

int sdlMainLoop(sdlgamestate_t *g) {
  init(g);

  SDL_Event event;
  bool gameRunning = true;

  while (gameRunning) {
    if (SDL_PollEvent(&event)) { 
      if (event.type == SDL_QUIT) {
        gameRunning = false;
      }
    }

    plotSweepers(g);
    
    SDL_Flip(g->screen);
  }

  SDL_FreeSurface(g->bitmaps.sweeper);
  SDL_Quit();
  
  return 0;
}