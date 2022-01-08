#include "fxlib.h"
#include "math.h"
#include "string.h"
#include "MonochromeLib.h"

#define SWIDTH 128
#define SHEIGHT 64

// char bmHUDHealthF[]  = {108,146,146,130,68, 40, 16, 0};
// char bmHUDHealthE[]  = {108,254,254,254,124,56, 16, 0};
char bmPlayerIdle1[] = {30, 60, 20, 60, 126,189,60, 36 };
char bmPlayerIdle2[] = {0,  30, 60, 20, 60, 126,189,36 };
char bmPlayerWalkL[] = {30, 60, 20, 60, 126,189,60, 32 };
char bmPlayerWalkR[] = {30, 60, 20, 60, 126,189,60, 4  };
char bmPlayerJump[]  = {30, 60, 20, 189,126,60, 126,0  };
char bmPipeV[]       = {24, 60, 24, 24, 24, 24, 60, 24 }; // -1
char bmPipeH[]       = {0,  0,  66, 255,255,66, 0,  0  }; // -2
char bmPipeTL[]      = {0,  0,  2,  15, 31, 26, 60, 24 }; // -3
char bmPipeBL[]      = {24, 60, 26, 31, 15, 2,  0,  0  }; // -4
char bmPipeBR[]      = {24, 60, 88, 248,240,64, 0,  0  }; // -5
char bmPipeTR[]      = {0,  0,  64, 240,248,88, 60, 24 }; // -6
char bmPipeVB[]      = {24, 60, 24, 74, 164,24, 60, 24 }; // -7
char bmPipeHB[]      = {0,  0,  66, 247,239,82, 8,  16 }; // -8
char bmAcid[]        = {0,  0,  51, 204,16, 2,  64, 0  }; // -9
char bmSpike[]       = {0,  0,  0,  170,85, 0,  85, 170}; // -10
char bmLadder[]      = {85, 255,85, 255,85, 255,85, 255}; // -11
char bmBlockTL[]     = {127,255,213,234,208,229,208,228}; // 1
char bmBlockL[]      = {209,228,209,228,209,228,209,228}; // 2
char bmBlockBL[]     = {209,228,210,224,213,234,255,127}; // 3
char bmBlockB[]      = {85, 0,  170,0,  85, 170,255,255}; // 4
char bmBlockBR[]     = {39, 11, 167,11, 87, 171,255,254}; // 5
char bmBlockR[]      = {39, 139,39, 139,39, 139,39, 139}; // 6
char bmBlockTR[]     = {254,255,87, 171,7,  75, 39, 139}; // 7
char bmBlockT[]      = {255,255,85, 170,0,  85, 0,  170}; // 8
char bmBlock[]       = {126,255,215,235,215,235,255,126}; // 9
char bmBlockLTL[]    = {209,228,81 ,164,1  ,84, 1,  170}; // 10
char bmBlockLBL[]    = {84, 0,  161,8,  65, 164,209,228}; // 11
char bmBlockLTR[]    = {39, 139,37, 130,16, 133,0,  42 }; // 12
char bmBlockLBR[]    = {85, 128,42, 128,37, 138,39, 139}; // 13
char bmBlockVT[]     = {126,255,215,235,215,235,215,235}; // 14
char bmBlockVB[]     = {235,215,235,215,235,215,255,126}; // 15
char bmBlockHB[]     = {127,255,234,213,234,213,255,127}; // 16
char bmSky[]         = {0,  0,  0,  0,  0,  0,  0,  0  };

int cRoom = 0;
/*{
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};*/
char sLevel[16][64];


int nLevelWidth = 64;
int nLevelHeight = 16;
int nPlayerState = 0;
int nPlayerFacing = 0;

float fCameraPosX = 0.0;
float fCameraPosY = 0.0;

float fPlayerPosX = 2.0;
float fPlayerPosY = 11.0;
float fPlayerVelX = 0.0;
float fPlayerVelY = 0.0;
float fPlayerHealth = 25;
float fPlayerMaxHealth = 25;

float deltatime = 0.01;

void loadLevel0() {
  char stemp[16][64] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13,4, 4, 4, 4, 4, 11,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13,5, 0, 0,-1, 0, 0, 3, 4, 4, 4, 11,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13,5,-11, 0,-3,-5, 0, 0, 0, 0, 0, 0, 3, 4, 4, 4, 11,0, 0, 13,4, 4, 4, 4, 4, 11,0, 0, 13,4, 4, 11,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13,4, 4,4,5,-11,-11, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 5,-1, 0, 0, 0, 0, 3, 4, 4, 5, 0, 0, 3, 4, 4, 11,0, 0, 0, 0, 0, 0, 0, 13,4, 4, 4, 4,11},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13,5,-1, 0,0,0,-11,-11, 1, 8, 8, 8, 7, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 11,13,4, 4, 4, 4, 5, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 13,4, 4, 5, 0,-1, 0,0,0,-11,-11, 2, 0, 0, 0, 6, 0, 0, 0,16,17, 0, 0, 0, 0, 0, 0, 0,-7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 0, 13,4, 4, 5, 0, 0, 0, 0,-1, 0,0,0,-11,-11, 3, 4, 4, 4, 5, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 1, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {0, 0, 13,4, 4, 5, 0, 0, 0, 0, 0, 0, 0,-1, 0,0,0,-11,-11, 0, 0,-1, 0, 0, 0, 0, 0,-7, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 8, 8, 10,0, 0, 0, 0, 12,8, 7,-2,-8,-2,-2,-2,-2,-8,-6, 0, 0, 0, 0, 0, 0, 0, 2},
    {4, 4, 5, 0, 0, 0, 0, 0, 0,-3,-2,-2,-2,-5, 0,0,0,-11,-11, 0, 0,-1, 0, 0, 0, 0, 0,-1, 0, 1, 7, 0, 0, 0, 1, 8, 10,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,8, 7, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0,0,-11, 1, 8, 8, 8, 8, 7, 0, 0, 0,-1, 0, 2, 6, 0, 1, 8, 10,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,7, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 3},
    {0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 1, 10,0, 0, 0, 0, 12,8, 8, 8, 7, 0, 2, 6, 1, 10,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 1, 10,0, 0, 0, 0, 0, 0, 0, 0, 0, 12,8,10,12, 10,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,7, 0, 0, 0, 0, 0, 0, 0},
    {8, 8, 8, 8, 8, 8, 7, 0, 0,-1, 0, 0, 0, 1, 8, 8, 10,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,7, 0, 0, 0, 1, 8, 8},
    {0, 0, 0, 0, 0, 0, 12,8, 8, 8, 8, 8, 8, 10,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,8, 8, 8, 10,0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };
  memcpy(sLevel, stemp, 16 * 64 * sizeof(char));
}

void loadLevel1() {
  char stemp[16][64] = {
    {13, 4, 4, 4, 4, 4, 4, 4, 4,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 6, 0,-1, 0, 0, 0, 0,-1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 6, 0,-1, 0, 0, 0, 0,-1, 0, 3, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 6, 0,-1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 6, 0,-1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 6, 0,-1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 6, 0,-1, 0, 0, 0, 0,-1, 0, 1, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 6,-10,-10,-10,-10,-10,-10,-10,-10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {12, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };
  memcpy(sLevel, stemp, 16 * 64 * sizeof(char));
}

void loadLevel2() {
  char stemp[16][64] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 4, 4, 4, 4,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 3, 4, 4,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 3, 4, 4,11,13, 4,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 0, 3,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0,12, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0,12, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0,12, 7, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0,13, 5, 0, 0,-1, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0,13, 5, 0, 0, 0,-1, 0,-1, 0, 9, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0,13, 5, 0, 0, 0, 0,-1, 0,-1, 0,-1, 0, 9, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {13, 5, 0, 0, 0, 0, 0,-1, 0,-1, 0,-1, 0,-1, 0, 0, 1, 8, 8,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 6,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 6, 0, 0, 0, 0, 0, 0,-1, 0,-1, 0,-1, 0,-1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {12, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };
  memcpy(sLevel, stemp, 16 * 64 * sizeof(char));
}

void loadLevel(int n) {
  switch (n) {
    case 0:loadLevel0();break;
    case 1:loadLevel1();break;
    case 2:loadLevel2();break;
  }
}

int bitReverse(int n) {
  int y = 0;
  int pos;
  for (pos = 7; pos >= 0; pos--) {
    y += ((n & 1) << pos);
    n >>= 1;
  }
  return y;
}

int ML2_bmp_8_xor_flip(char spr[8], int x, int y) {
  int j;
  char sprcpy[8];

  for (j = 0; j < 8; j++) sprcpy[j] = (char)bitReverse((int)spr[j]);

  ML_bmp_8_xor_cl(sprcpy, x, y);
}

char get_tile(int x, int y) {
  if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight) {
    return sLevel[y][x];
  }
  else
    return 0;
}

void set_tile(int x, int y, char c) {
  if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
    sLevel[y][x] = c;
}



int AddIn_main(int isAppli, unsigned short OptionNum)
{
  // gameloop
  unsigned int key1 = 0, key2 = 0;
  short unused = 0;
  int gameover = 0;

  int nTileWidth = 8;
  int nTileHeight = 8;
  int nVisibleTilesX = SWIDTH / nTileWidth;
  int nVisibleTilesY = SHEIGHT / nTileHeight;
  float fOffsetX, fOffsetY, fTileOffsetX, fTileOffsetY;
  float fNewPlayerPosX, fNewPlayerPosY;
  int bPlayerOnGround = 0;

  int frameCounter = 0;
  int frameMax = 256;
  int frameMem = 0;

  int x, y, i, j;
  char sTileID;

  loadLevel(0);

  while(!gameover) {
    key1 = 0;key2 = 0;
    Bkey_GetKeyWait(&key1, &key2, KEYWAIT_HALTOFF_TIMEROFF, 0, 0, &unused);
    ML_clear_vram();

    frameCounter++;
    if (frameCounter >= frameMax) frameCounter = 0;

    // quit
    if (key1 == 4 && key2 == 8) gameover = 1;

    // input
    if (key1 == 2 && key2 == 9 && get_tile((int)fPlayerPosX, (int)fPlayerPosY) == -11)
      fPlayerVelY = -6.0;

    if (key1 == 3 && key2 == 8)
      fPlayerVelY = 6.0;

    if (key1 == 3 && key2 == 9) {
      fPlayerVelX += (bPlayerOnGround ? -6.0 : -4.0) * deltatime;
      nPlayerFacing = 0;
    }

    if (key1 == 2 && key2 == 8) {
      fPlayerVelX += (bPlayerOnGround ? 6.0 : 4.0) * deltatime;
      nPlayerFacing = 1;
    }

    if (key1 == 7 && key2 == 9) {
      if (fPlayerVelY == 0 && bPlayerOnGround) {
        fPlayerVelY = -12.0;
      }
    }

    fPlayerVelY += 20.0 * deltatime;

    if (fPlayerVelX > 0.3 || fPlayerVelX < -0.3) {
      nPlayerState = 1; // walk
    }

    if (bPlayerOnGround) {
      fPlayerVelX += -1.0 * fPlayerVelX * deltatime;
      if (fabs(fPlayerVelX) < 0.01)
        fPlayerVelX = 0.0;

      if (fPlayerVelX <= 0.3 && fPlayerVelX >= -0.3) {
        nPlayerState = 0; // idle
      }
    } else {
      nPlayerState = 2; // jump
    }

    fNewPlayerPosX = fPlayerPosX + fPlayerVelX * deltatime;
    fNewPlayerPosY = fPlayerPosY + fPlayerVelY * deltatime;

    if (fPlayerVelX > 16.0) fPlayerVelX = 16.0;
    if (fPlayerVelX < -16.0) fPlayerVelX = -16.0;
    if (fPlayerVelY > 100.0) fPlayerVelY = 100.0;
    if (fPlayerVelY < -100.0) fPlayerVelY = -100.0;

    // collision
    if (fPlayerVelX <= 0) {
      if (get_tile(fNewPlayerPosX + 0.0, fPlayerPosY + 0.0) > 0 || get_tile(fNewPlayerPosX + 0.0, fPlayerPosY + 0.9) > 0) {
        fNewPlayerPosX = (int)fNewPlayerPosX + 1;
        fPlayerVelX = 0;
      }
    } else {
      if (get_tile(fNewPlayerPosX + 1.0, fPlayerPosY + 0.0) > 0 || get_tile(fNewPlayerPosX + 1.0, fPlayerPosY + 0.9) > 0) {
        fNewPlayerPosX = (int)fNewPlayerPosX;
        fPlayerVelX = 0;
      }
    }

    bPlayerOnGround = 0;
    if (fPlayerVelY <= 0) {
      if (get_tile(fNewPlayerPosX + 0.0, fNewPlayerPosY + 0.0) > 0 || get_tile(fNewPlayerPosX + 0.9, fNewPlayerPosY + 0.0) > 0) {
        fNewPlayerPosY = (int)fNewPlayerPosY + 1;
        fPlayerVelY = 0;
      }
    } else {
      if (get_tile(fNewPlayerPosX + 0.0, fNewPlayerPosY + 1.0) > 0 || get_tile(fNewPlayerPosX + 0.9, fNewPlayerPosY + 1.0) > 0) {
        fNewPlayerPosY = (int)fNewPlayerPosY;
        fPlayerVelY = 0;
        bPlayerOnGround = 1;
      }
    }

    // update
    fPlayerPosX = fNewPlayerPosX;
    fPlayerPosY = fNewPlayerPosY;

    // health
    if (fPlayerHealth <= 0) gameover = 1;

    // check exits
    switch (cRoom) {
      case 0:
        if ((int)fPlayerPosX == 0 && nPlayerFacing == 0) {
          if ((int)fPlayerPosY == 11 || (int)fPlayerPosY == 12 || (int)fPlayerPosY == 13) {
            cRoom = 1;
            nLevelWidth = 12;
            nLevelHeight = 9;
            fPlayerPosX = 11;
            fPlayerPosY = 5;
            loadLevel(cRoom);
          }
        }
        if ((int)fPlayerPosX == 63 && nPlayerFacing == 1) {
          if ((int)fPlayerPosY == 11 || (int)fPlayerPosY == 12) {
            cRoom = 2;
            nLevelWidth = 21;
            nLevelHeight = 16;
            fPlayerPosX = 0;
            fPlayerPosY = 3;
            loadLevel(cRoom);
          }
        }
        break;
      case 1:
        if ((int)fPlayerPosX == 11 && nPlayerFacing == 1) {
          if ((int)fPlayerPosY == 5 || (int)fPlayerPosY == 6 || (int)fPlayerPosY == 7) {
            cRoom = 0;
            nLevelWidth = 64;
            nLevelHeight = 16;
            fPlayerPosX = 0;
            fPlayerPosY = 12;
            loadLevel(cRoom);
          }
        }
        break;
      case 2:
        if ((int)fPlayerPosX == 0 && nPlayerFacing == 0) {
          if ((int)fPlayerPosY == 3 || (int)fPlayerPosY == 2) {
            cRoom = 0;
            nLevelWidth = 64;
            nLevelHeight = 16;
            fPlayerPosX = 63;
            fPlayerPosY = 12;
            loadLevel(cRoom);
          }
        }
        break;
      default:
        break;
    }

    // camera
    fCameraPosX = fPlayerPosX;
    fCameraPosY = fPlayerPosY;

    // draw level
    fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0;
    fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0;

    if (fOffsetX < 0) fOffsetX = 0;
    if (fOffsetY < 0) fOffsetY = 0;
    if (fOffsetX > nLevelWidth - nVisibleTilesX) fOffsetX = nLevelWidth - nVisibleTilesX;
    if (fOffsetY > nLevelHeight - nVisibleTilesY) fOffsetY = nLevelHeight - nVisibleTilesY;

    fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
    fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;

    for (x = -1; x < nVisibleTilesX + 1; x++) {
      for (y = -1; y < nVisibleTilesY + 1; y++) {
        sTileID = get_tile(x + fOffsetX, y + fOffsetY);
        switch (sTileID) {
          case -11: ML_bmp_8_or_cl(bmLadder, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -10: ML_bmp_8_or_cl(bmSpike, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -9: ML_bmp_8_or_cl(bmAcid, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -8: ML_bmp_8_or_cl(bmPipeHB, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -7: ML_bmp_8_or_cl(bmPipeVB, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -6: ML_bmp_8_or_cl(bmPipeTR, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -5: ML_bmp_8_or_cl(bmPipeBR, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -4: ML_bmp_8_or_cl(bmPipeBL, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -3: ML_bmp_8_or_cl(bmPipeTL, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -2: ML_bmp_8_or_cl(bmPipeH, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case -1: ML_bmp_8_or_cl(bmPipeV, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 0: break;
          case 1: ML_bmp_8_or_cl(bmBlockTL, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 2: ML_bmp_8_or_cl(bmBlockL, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 3: ML_bmp_8_or_cl(bmBlockBL, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 4: ML_bmp_8_or_cl(bmBlockB, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 5: ML_bmp_8_or_cl(bmBlockBR, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 6: ML_bmp_8_or_cl(bmBlockR, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 7: ML_bmp_8_or_cl(bmBlockTR, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 8: ML_bmp_8_or_cl(bmBlockT, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 9: ML_bmp_8_or_cl(bmBlock, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 10: ML_bmp_8_or_cl(bmBlockLTL, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 11: ML_bmp_8_or_cl(bmBlockLBL, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 12: ML_bmp_8_or_cl(bmBlockLTR, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 13: ML_bmp_8_or_cl(bmBlockLBR, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 14: ML_bmp_8_or_cl(bmBlockVT, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 15: ML_bmp_8_or_cl(bmBlockVB, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 16: ML_bmp_8_or_cl(bmBlockHB, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          case 17: ML2_bmp_8_xor_flip(bmBlockHB, x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY);
            break;
          default:
            break;
        }
      }
    }

    // player
    switch (nPlayerState) {
      case 0:
        if (nPlayerFacing == 1) {
          if (frameCounter < 128 || frameCounter > 148) ML2_bmp_8_xor_flip(bmPlayerIdle1, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
          else ML2_bmp_8_xor_flip(bmPlayerIdle2, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
        }
        else {
          if (frameCounter < 128 || frameCounter > 148) ML_bmp_8_xor(bmPlayerIdle1, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
          else ML_bmp_8_xor(bmPlayerIdle2, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
        }
        break;
      case 1:
        if (nPlayerFacing == 1) {
          if (frameCounter % 32 <= 16) ML2_bmp_8_xor_flip(bmPlayerWalkL, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
          else ML2_bmp_8_xor_flip(bmPlayerWalkR, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
        } else  {
          if (frameCounter % 32 <= 16) ML_bmp_8_xor(bmPlayerWalkL, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
          else ML_bmp_8_xor(bmPlayerWalkR, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
        }
        break;
      case 2:
        if (nPlayerFacing == 1) ML2_bmp_8_xor_flip(bmPlayerJump, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
        else {
          ML_bmp_8_xor(bmPlayerJump, (fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight);
        }
        break;
      default:
        break;
    }

    // hud
    if (get_tile((int)fPlayerPosX, (int)fPlayerPosY) == -9 || get_tile((int)fPlayerPosX, (int)fPlayerPosY) == -10) fPlayerHealth = 0;
    ML_rectangle(1, 1, 26, 6, 1, ML_BLACK, ML_WHITE);
    ML_rectangle(0, 0, 27, 7, 1, ML_WHITE, ML_TRANSPARENT);
    if (fPlayerHealth != 0) ML_rectangle(2, 2, (25 / fPlayerMaxHealth) * fPlayerHealth, 5, 0, ML_CHECKER, ML_BLACK);

    ML_display_vram();
  }

  return 1;
}


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

int InitializeSystem(int isAppli, unsigned short OptionNum)
{
  return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section
