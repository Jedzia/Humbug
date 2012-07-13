#ifndef _HumbugGfx_c
#define _HumbugGfx_c


#ifndef _GFX_BITMAP_DATA
#define _GFX_BITMAP_DATA
/* structure with bitmap data */
typedef struct GFX_BITMAP_DATA
{
  char * BitmapIdentifier;
  int BitmapWidth;
  int BitmapHeight;
  int TileWidth;
  int TileHeight;
  int TileCountX;
  int TileCountY;
  int TransparentX;
  int TransparentY;
  int Sequences;
  int ** SequenceData;
  int * SequenceLength;
  int * SequencePosition;
  int * SequenceCounter;

} GFX_BITMAP_DATA;
#endif


#ifndef _GFX_EMPTY
#define _GFX_EMPTY
static int Empty[] = {0};
#endif


#define GfxTiles1Map1MapWidth (4)
#define GfxTiles1Map1MapHeight (4)

signed short Tiles1Map1MapData[4][4] =
  {{ 1, 0, 0, 2},
  { 0, 0, 0, 0},
  { 0, 0, 0, 0},
  { 3, 0, 0, 4}};

unsigned short Tiles1Map1BoundMapData[4][4] =
  {{258,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0}};


/* tile sequences */

int Tiles1SeqLength[] =
{
  -1
};

int Tiles1SeqPosition[0 + 1];
int Tiles1SeqCounter[0 + 1];

int * Tiles1Sequences[] = 
{
  Empty
};

 

/* bitmap data */
const struct GFX_BITMAP_DATA GfxTiles1Bitmap = 
  { "Tiles1",  256, 64,  64, 64,  
    4, 1,  0, 0, 0,
    &Tiles1Sequences[0], &Tiles1SeqLength[0],
    &Tiles1SeqPosition[0], &Tiles1SeqCounter[0]
  };


#endif