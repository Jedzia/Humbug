#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SDL.h"

//----------------------------------------------------------

// A set of very useful macros that you will find in most
// code that I write whether I use them in a program or
// not.

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define abs(a) (((a)<0) ? -(a) : (a))
#define sign(a) (((a)<0) ? -1 : (a)>0 ? 1 : 0)

//----------------------------------------------------------

// The following code implements a Bresenham line drawing
// algorithm. There are 4 separate routines each optimized
// for one of the four pixel depths supported by SDL. SDL
// supports many pixel formats, but but all of those
// formats fit into 8, 16, 24, and 32 bit fields.

//----------------------------------------------------------

// Draw lines in 8 bit surfaces.

static void line8(SDL_Surface *s, 
                  int x1, int y1, 
                  int x2, int y2, 
                  Uint32 color)
{
  int d;
  int x;
  int y;
  int ax;
  int ay;
  int sx;
  int sy;
  int dx;
  int dy;

  Uint8 *lineAddr;
  Sint32 yOffset;

  dx = x2 - x1;  
  ax = abs(dx) << 1;  
  sx = sign(dx);

  dy = y2 - y1;  
  ay = abs(dy) << 1;  
  sy = sign(dy);
  yOffset = sy * s->pitch;

  x = x1;
  y = y1;

  lineAddr = ((Uint8 *)(s->pixels)) + (y * s->pitch);
  if (ax>ay)
  {                      /* x dominant */
    d = ay - (ax >> 1);
    for (;;)
    {
      *(lineAddr + x) = (Uint8)color;

      if (x == x2)
      {
        return;
      }
      if (d>=0)
      {
        y += sy;
        lineAddr += yOffset;
        d -= ax;
      }
      x += sx;
      d += ay;
    }
  }
  else
  {                      /* y dominant */
    d = ax - (ay >> 1);
    for (;;)
    {
      *(lineAddr + x) = (Uint8)color;

      if (y == y2)
      {
        return;
      }
      if (d>=0) 
      {
        x += sx;
        d -= ay;
      }
      y += sy;
      lineAddr += yOffset;
      d += ax;
    }
  }
}

//----------------------------------------------------------

// Draw lines in 16 bit surfaces. Note that 12 and 15 bit
// pixels formats are stored in 16 bit fields.

static void line16(SDL_Surface *s, 
                   int x1, int y1, 
                   int x2, int y2, 
                   Uint32 color)
{
  int d;
  int x;
  int y;
  int ax;
  int ay;
  int sx;
  int sy;
  int dx;
  int dy;

  Uint8 *lineAddr;
  Sint32 yOffset;

  dx = x2 - x1;  
  ax = abs(dx) << 1;  
  sx = sign(dx);

  dy = y2 - y1;  
  ay = abs(dy) << 1;  
  sy = sign(dy);
  yOffset = sy * s->pitch;

  x = x1;
  y = y1;

  lineAddr = ((Uint8 *)s->pixels) + (y * s->pitch);
  if (ax>ay)
  {                      /* x dominant */
    d = ay - (ax >> 1);
    for (;;)
    {
      *((Uint16 *)(lineAddr + (x << 1))) = (Uint16)color;

      if (x == x2)
      {
        return;
      }
      if (d>=0)
      {
        y += sy;
        lineAddr += yOffset;
        d -= ax;
      }
      x += sx;
      d += ay;
    }
  }
  else
  {                      /* y dominant */
    d = ax - (ay >> 1);
    for (;;)
    {
      *((Uint16 *)(lineAddr + (x << 1))) = (Uint16)color;

      if (y == y2)
      {
        return;
      }
      if (d>=0) 
      {
        x += sx;
        d -= ay;
      }
      y += sy;
      lineAddr += yOffset;
      d += ax;
    }
  }
}

//----------------------------------------------------------

// Draw lines in 24 bit surfaces. 24 bit surfaces require
// special handling because the pixels don't fall on even
// address boundaries. Instead of being able to store a
// single byte, word, or long you have to store 3
// individual bytes. As a result 24 bit graphics is slower
// than the other pixel sizes.

static void line24(SDL_Surface *s, 
                   int x1, int y1, 
                   int x2, int y2, 
                   Uint32 color)
{
  int d;
  int x;
  int y;
  int ax;
  int ay;
  int sx;
  int sy;
  int dx;
  int dy;

  Uint8 *lineAddr;
  Sint32 yOffset;

#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
  color <<= 8;
#endif

  dx = x2 - x1;  
  ax = abs(dx) << 1;  
  sx = sign(dx);

  dy = y2 - y1;  
  ay = abs(dy) << 1;  
  sy = sign(dy);
  yOffset = sy * s->pitch;

  x = x1;
  y = y1;

  lineAddr = ((Uint8 *)(s->pixels)) + (y * s->pitch);
  if (ax>ay)
  {                      /* x dominant */
    d = ay - (ax >> 1);
    for (;;)
    {
      Uint8 *p = (lineAddr + (x * 3));
      memcpy(p, &color, 3);

      if (x == x2)
      {
        return;
      }
      if (d>=0)
      {
        y += sy;
        lineAddr += yOffset;
        d -= ax;
      }
      x += sx;
      d += ay;
    }
  }
  else
  {                      /* y dominant */
    d = ax - (ay >> 1);
    for (;;)
    {
      Uint8 *p = (lineAddr + (x * 3));
      memcpy(p, &color, 3);

      if (y == y2)
      {
        return;
      }
      if (d>=0) 
      {
        x += sx;
        d -= ay;
      }
      y += sy;
      lineAddr += yOffset;
      d += ax;
    }
  }
}

//----------------------------------------------------------

// Draw lines in 32 bit surfaces. Note that this routine
// ignores alpha values. It writes them into the surface if
// they are included in the pixel, but does nothing else
// with them.

static void line32(SDL_Surface *s, 
                   int x1, int y1, 
                   int x2, int y2, 
                   Uint32 color)
{
  int d;
  int x;
  int y;
  int ax;
  int ay;
  int sx;
  int sy;
  int dx;
  int dy;

  Uint8 *lineAddr;
  Sint32 yOffset;

  dx = x2 - x1;  
  ax = abs(dx) << 1;  
  sx = sign(dx);

  dy = y2 - y1;  
  ay = abs(dy) << 1;  
  sy = sign(dy);
  yOffset = sy * s->pitch;

  x = x1;
  y = y1;

  lineAddr = ((Uint8 *)(s->pixels)) + (y * s->pitch);
  if (ax>ay)
  {                      /* x dominant */
    d = ay - (ax >> 1);
    for (;;)
    {
      *((Uint32 *)(lineAddr + (x << 2))) = (Uint32)color;

      if (x == x2)
      {
        return;
      }
      if (d>=0)
      {
        y += sy;
        lineAddr += yOffset;
        d -= ax;
      }
      x += sx;
      d += ay;
    }
  }
  else
  {                      /* y dominant */
    d = ax - (ay >> 1);
    for (;;)
    {
      *((Uint32 *)(lineAddr + (x << 2))) = (Uint32)color;

      if (y == y2)
      {
        return;
      }
      if (d>=0) 
      {
        x += sx;
        d -= ay;
      }
      y += sy;
      lineAddr += yOffset;
      d += ax;
    }
  }
}

//----------------------------------------------------------

// Examine the depth of a surface and select a line drawing
// routine optimized for the bytes/pixel of the surface.

static void line(SDL_Surface *s, 
                 int x1, int y1, 
                 int x2, int y2, 
                 Uint32 color)
{
  switch (s->format->BytesPerPixel)
  {
  case 1:
    line8(s, x1, y1, x2, y2, color);
    break;
  case 2:
    line16(s, x1, y1, x2, y2, color);
    break;
  case 3:
    line24(s, x1, y1, x2, y2, color);
    break;
  case 4:
    line32(s, x1, y1, x2, y2, color);
    break;
  }
}

//----------------------------------------------------------

// sweepLine animates a line on a surface based on the
// elapsed time.

class sweepLine
{
private:
  SDL_Surface *s;             // The surface to draw on.
  Uint32 color;               // The color of the line.
  int last;                   // last time update() was
                              // called.
  int maxx;                   // Maximum valid X value.
  int maxy;                   // Maximum valid Y value.
  float x1, y1;               // The current location
  float dx1, dy1;             // and velocity of the line
  float x2, y2;               // end points.
  float dx2, dy2;

  // movePoint computes the new location of a point based
  // on its initial location, its velocity, and the elapsed
  // time.

  void movePoint(float &x, float &y, 
                 float &dx, float &dy,
                 int dt)
  {
    // Compute the new X location.

    x += (dx * dt);

    // If the X value is off of the screen, move it back on
    // and reverse the velocity in the X direction.

    if (x >= maxx)
    {
      x = maxx;
      dx = -dx;
    }
    else if (x <= 0)
    {
      x = 0;
      dx = -dx;
    }

    // Same thing for Y.
    y += (dy * dt);
    if (y >= maxy)
    {
      y = maxy;
      dy = -dy;
    }
    else if (y <= 0)
    {
      y = 0;
      dy = -dy;
    }
  }

public:

  // sweepLine animates a line on a surface. It is
  // initialized with a pointer to the surface to draw the
  // line on, a pixel value that specifies the color of the
  // line, the current time, and the initial locations of
  // the line end points and their velocities. Velocities
  // are specified in pixels/millisecond.

  // This method initializes the class and forces the end
  // points of the lines to be inside the boundaries of the
  // surface. If it didn't do that the line drawing code
  // would try to write outside of the surface and crash
  // the program.

  sweepLine(SDL_Surface *s, 
            Uint32 color,
            int time,
            float x1,  float y1,
            float dx1, float dy1,
            float x2,  float y2,
            float dx2, float dy2): 
    s(s),
    color(color),
    last(time),
    x1(x1), y1(y1),
    dx1(dx1), dy1(dy1),
    x2(x2), y2(y2),
    dx2(dx2), dy2(dy2)
  {

    // Set the values of maxx and maxy to one less than the
    // width and height. Doing that makes clipping easier
    // to code.

    maxx = 0;
    maxy = 0;

    if (NULL != s)
    {
      maxx = s->w - 1;
      maxy = s->h - 1;
    }

    // Force the line end points onto the screen.

    x1 = max(x1, 0);
    y1 = max(y1, 0);

    x2 = max(x2, 0);
    y2 = max(y2, 0);

    x1 = min(x1, maxx);
    y1 = min(y1, maxy);

    x2 = min(x2, maxx);
    y2 = min(y2, maxy);
  }

  void update(long now)
  {
    int dt = now - last;
    last = now;

    // Update the locations of the line end points.

    movePoint(x1, y1, dx1, dy1, dt);
    movePoint(x2, y2, dx2, dy2, dt);

    // Draw the line at its new location.

    line(s, 
         (int)x1, (int)y1, 
         (int)x2, (int)y2, 
         color);
  }

};

//----------------------------------------------------------

// gameTime keeps track of game time as opposed to real
// time. Game time can start and stop and even change its
// speed while real time just keeps ticking along.

class gameTime
{
private:
  int startTime;              // Last time the clock was
                              // started.
  int baseTime;               // How much game time passed
                              // before the last time the
                              // clock was started.
  bool running;               // Is the clock running or
                              // not?

public:

  // Initialize the class variables. At this point no game
  // time has elapsed and the clock is not running.

  gameTime()
  {
    startTime = 0;
    baseTime = 0;
    running = false;
  }

  // Start the clock.

  void start()
  {
    if (!running)
    {
      startTime = SDL_GetTicks();
      running = true;
    }
  }

  // Stop the clock

  void stop()
  {
    if (running)
    {
      baseTime = baseTime + (SDL_GetTicks() - startTime);
      running = false;
    }
  }

  // True if the clock is paused.

  bool stopped()
  {
    return !running;
  }

  // Get this clocks current time in milliseconds.

  int time()
  {
    if (running)
    {
      return baseTime + (SDL_GetTicks() - startTime);
    }
    else
    {
      return baseTime;
    }
  }
};

//----------------------------------------------------------

int wmain(int argc, char **argv)
{
  // Declare all the local variables.

  gameTime gt;
  char *name = argv[0];

  Uint32 start = 0;
  Uint32 frames = 0;

  SDL_Texture *texture;
  SDL_Surface *screen = NULL;
  SDL_Event event;
  SDL_PixelFormat *pf = NULL;
  SDL_Rect r;
  Uint32 black;
  Uint32 red;
  Uint32 green;
  Uint32 blue;

  int screenWidth = 640;
  int screenHeight = 480;

  bool done = false;

  sweepLine *rl = NULL;
  sweepLine *gl = NULL;
  sweepLine *bl = NULL;

  // If you want to use hardware buffers under Linux and
  // X11 you must have this environment variable set. It
  // tells SDL which device driver to use. In this case,
  // I'm telling SDL to use the DGA driver instead of the
  // normal X11 graphics interface. Under X11, SDL only
  // supports hardware buffers through the DGA extension.

#ifdef __linux__
  putenv("SDL_VIDEODRIVER=dga");
#endif

  // Try to initialize SDL. If it fails, then give up.

  if (-1 == SDL_Init(SDL_INIT_EVERYTHING))
  {
    printf("Can't initialize SDL:%s\n", SDL_GetError());
    exit(1);
  }

  // Safety first. If the program exits in an unexpected
  // way the atexit() call should ensure that SDL will be
  // shut down properly and the screen returned to a
  // reasonable state.

  atexit(SDL_Quit);

  // Initialize the display. Here I'm asking for a full
  // screen, 640x480 display, with any pixel format, any
  // pixel depth, double buffering, and hardware buffers.
  // Your application may have to run in full screen mode
  // to get hardware buffers at all. And, it may have to
  // be full screen to get double buffering.

  /*screen = SDL_SetVideoMode(screenWidth, 
                            screenHeight, 
                            0, 
                            SDL_ANYFORMAT |
                            SDL_FULLSCREEN |
                            SDL_HWSURFACE |
                            SDL_DOUBLEBUF
                            );*/
                            
  SDL_Window* window;
  SDL_Renderer* renderer;

  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
      return 1;

  // Create the window where we will draw.
  window = SDL_CreateWindow(name,
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      screenWidth, screenHeight,
      0);

  // We must call SDL_CreateRenderer in order for draw calls to affect this window.
  renderer = SDL_CreateRenderer(window, -1, 0);
  //texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screenWidth, screenHeight);

  Uint32 rmask, gmask, bmask, amask;

  /* SDL interprets each pixel as a 32-bit number, so our masks must depend
  on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  screen = SDL_CreateRGBSurface(0, 640, 480, 32, rmask, gmask, bmask, amask);

  r.w = 100;
  r.h = 50;


  if (NULL == screen)
  {
    printf("Can't set video mode:%s\n", SDL_GetError());
    exit(1);
  }

  // SDL might give you a software buffer even though you
  // asked for a hardware buffer. Check the flags to make
  // sure you got what you asked for.

  /*if (0 == screen->flags & SDL_HWSURFACE)
  {
    printf("Can't get hardware surface\n");
    exit(1);
  }*/

  // Grab the pixel format for the screen. SDL_MapRGB()
  // needs the pixel format to create pixels that are laid
  // out correctly for the screen.

  pf = screen->format;

  //Create the pixel values used in the program. Black is
  //for clearing the background and the other three are
  //for line colors. Note that in SDL you specify color
  //intensities in the range 0 to 255 (hex ff). That
  //doesn't mean that you always get 24 or 32 bits of
  //color. If the format doesn't support the full color
  //range, SDL scales it to the range that is correct for
  //the pixel format.

  black = SDL_MapRGB(pf, 0x00, 0x00, 0x00);
  red = SDL_MapRGB(pf, 0xff, 0x00, 0x00);
  green = SDL_MapRGB(pf, 0x00, 0xff, 0x00);
  blue = SDL_MapRGB(pf, 0x00, 0x00, 0xff);

  // Create the three animating lines. It is amazing to
  // see the different kinds of behavior you can get from
  // such a simple animation object.

  rl = new sweepLine(screen, 
                     red, 
                     gt.time(),
                     screen->w - 1, 0,
                     -0.3, 0,
                     0, screen->h - 1,
                     0.3, 0);
  gl = new sweepLine(screen, 
                     green, 
                     gt.time(),
                     0, 0,
                     0, 0.1,
                     screen->w - 1, screen->h - 1,
                     0, -0.1);
  bl = new sweepLine(screen, 
                     blue, 
                     gt.time(),
                     screen->w - 1, 0,
                     -0.1, -0.5,
                     0, screen->h - 1,
                     0.4, 0.2);

  // Start the game clock.

  start = SDL_GetTicks();
  gt.start();

  // The animation loop.

  while (!done)
  {

    // Loop while reading all pending events.

    while (!done && SDL_PollEvent(&event))
    {
      switch (event.type)
      {

        // Here we are looking for two special keys. If we
        // get an event telling us that the escape key has
        // been pressed the program will quit. If we see
        // the F1 key we either start or stop the
        // animation by starting or stopping the clock.

      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          done = true;
          break;

        case SDLK_F1:
          if (gt.stopped())
          {
            gt.start();
          }
          else
          {
            gt.stop();
          }
          break;

        default:
          break;
        }
        break;

        // The SDL_QUIT event is generated when you click
        // on the close button on a window. If we see that
        // event we should exit the program. So, we do.

      case SDL_QUIT:
        done = true;
        break;
      }
    }

    //If there is a buffer swap pending then the program
    //will wait for it either during the call to
    //SDL_FillRect() or during the call to
    //SDL_Locksurface().

    // Erase the old picture by painting the whole buffer
    // black. Since we are using hardware buffers this
    // operation may be done by the hardware of your video
    // card and be much faster than the software version.

    SDL_FillRect(screen, NULL, black);

    // If the hardware buffer must be locked, then lock
    // it.

    if (SDL_MUSTLOCK(screen))
    {
      if (-1 == SDL_LockSurface(screen))
      {
        printf("Can't lock hardware surface\n");
        exit(1);
      }
    }

    // Get the current game time. Note that if the clock
    // is stopped this method will return the same value
    // over and over.

    int t = gt.time();

    // Based on the current time update the location of
    // each line and draw the line into the buffer.

    rl->update(t);
    gl->update(t);
    bl->update(t);


    // Unlock the hardware buffer.

    if (SDL_MUSTLOCK(screen))
    {
      SDL_UnlockSurface(screen);
    }

    // Since I'm using a hardware buffer the call to
    // SDL_Flip() tells the video card to start displaying
    // from a new buffer. Which may or may not happen
    // before SDL_Flip() returns. When used on hardware
    // buffers SDL_Flip() will "usually" return
    // immediately.

    //SDL_Flip(screen);

    r.x = rand() % 500;
    r.y = rand() % 500;

    texture = SDL_CreateTextureFromSurface(renderer, screen);
    
    //SDL_SetRenderTarget(renderer, texture);
    //SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    //SDL_RenderClear(renderer);
    //SDL_RenderDrawRect(renderer, &r);
    //SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
    //SDL_RenderFillRect(renderer, &r);
    //SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);

    frames++;
  }

  // Compute the average number of frames drawn per
  // second. This number can be useful for diagnosing some
  // kinds of programming errors. But, usually it is just
  // fun to see.

  float seconds = 
        ((float) (SDL_GetTicks() - start)) / 1000.0;
  printf("frames/second=%f\n", ((float)frames) / seconds);

  // When we get here, just clean up and quit. Yes, the
  // atexit() call makes this redundant. But, it doesn't
  // hurt and I'd rather be safe than sorry.

  SDL_Quit();
}
