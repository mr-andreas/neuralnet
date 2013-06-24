#include "gfx.h"

#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_timer.h>
#include <math.h>

const int FRAMES_PER_SECOND = 60;
const int FRAMERATE_IN_MS = 1000/FRAMES_PER_SECOND;
const int REPOPULATE_ON_FRAME = 60*FRAMES_PER_SECOND;
const char* WINDOW_TITLE = "SDL Start";

void plotSweeper(sdlgamestate_t *g, const Sweeper &sweeper) {
  // Part of the bitmap that we want to draw
  SDL_Rect source;
  source.x = 0;
  source.y = 0;
  source.w = 32;
  source.h = 32;

  // Part of the screen we want to draw the sprite to
  SDL_Rect destination;
  destination.x = sweeper.posx-16;
  destination.y = sweeper.posy-16;
  destination.w = 32;
  destination.h = 32;
  
  SDL_Surface *rotated = rotozoomSurface(g->bitmaps.sweeper, sweeper.rotation*180.0/M_PI-90.0, 0.5, 1);
  SDL_BlitSurface(rotated, &source, g->screen, &destination);
  
  SDL_FreeSurface(rotated);
}

void plotSweepers(sdlgamestate_t *g) {
  const std::vector<Sweeper> &s(g->gamestate->sweepers);
  
  for(std::vector<Sweeper>::const_iterator i = s.begin(); i != s.end(); i++) {
    if(i->dead) continue;
    
    plotSweeper(g, *i);
  }
}

void plotMines(const sdlgamestate_t *g) {
  const std::vector<Mine> &s(g->gamestate->mines);
  
  for(std::vector<Mine>::const_iterator i = s.begin(); i != s.end(); i++) {
    if(i->deleted) continue;
    
    // Part of the bitmap that we want to draw
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 5;
    source.h = 5;

    // Part of the screen we want to draw the sprite to
    SDL_Rect destination;
    destination.x = i->posx-2;
    destination.y = i->posy-2;
    destination.w = 20;
    destination.h = 20;
    
    SDL_BlitSurface(g->bitmaps.mine, &source, g->screen, &destination);
  }
}

void plotBullets(const sdlgamestate_t *g) {
  const std::list<Bullet> &s(g->gamestate->bullets);
  
  for(std::list<Bullet>::const_iterator i = s.begin(); i != s.end(); i++) {
    // Part of the bitmap that we want to draw
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 3;
    source.h = 3;

    // Part of the screen we want to draw the sprite to
    SDL_Rect destination;
    destination.x = i->posx-1;
    destination.y = i->posy-1;
    destination.w = 3;
    destination.h = 3;
    
    SDL_BlitSurface(g->bitmaps.bullet, &source, g->screen, &destination);
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
  g->bitmaps.bullet = IMG_Load("/home/ante/dev/neuralnet/res/bullet.png");
}

int sdlMainLoop(sdlgamestate_t *g) {
  init(g);

  SDL_Event event;
  bool gameRunning = true;
  int plotPause = 0;
  unsigned int startTime, endTime;
  unsigned int frameCounter = 0;
  int delay;

  while (gameRunning) {
    startTime = SDL_GetTicks();
    
    if (SDL_PollEvent(&event)) { 
      if (event.type == SDL_QUIT) {
        gameRunning = false;
      }
      
      if(event.type == SDL_KEYUP) {
        if(event.key.keysym.sym == 'q') {
          gameRunning = false;
        }
        
        if(plotPause) {
          plotPause = 0;
        } else {
          if(event.key.keysym.sym == 'n') {
            plotPause = 1;
          } else {
            plotPause = 2;
          }
        }
      }
    }

    SDL_FillRect(g->screen, NULL, SDL_MapRGB(g->screen->format, 255, 255, 255));
    
    if(frameCounter++ % REPOPULATE_ON_FRAME == 0) {
      printf("Transplanting brains\n");
      brainTransplant(g->gamestate);
      randomize(g->gamestate);
      if(plotPause == 1)
        plotPause = 0;
    }
    
    doTurn(g->gamestate);
    if(!plotPause) {
      plotMines(g);
      plotBullets(g);
      plotSweepers(g);
    
      SDL_Flip(g->screen);
      
      endTime = SDL_GetTicks();
    
      delay = FRAMERATE_IN_MS - (endTime - startTime);
      if(delay > 0)
        SDL_Delay(delay);
    }
  }

  SDL_FreeSurface(g->bitmaps.sweeper);
  SDL_Quit();
  
  return 0;
}