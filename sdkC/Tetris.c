#include "fxlib.h"
#include "string.h"
#include "stdio.h"
#include "revolution.h"

unsigned char tetrb[4][4] = {
  {1, 1, 1, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 1, 1, 1}
};
unsigned char tetrv[4][4] = {
  {0, 1, 0, 1},
  {1, 0, 1, 0},
  {0, 1, 0, 1},
  {1, 0, 1, 0}
};

const int fieldWidth = 12;
const int fieldHeight = 16;
unsigned char field[16 * 12];
unsigned char tetromino[7][16] = {
  { // Line
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0
  },
  { // S
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
  },
  { // S 2
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0
  },
  { // Block
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
  },
  { // T
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0
  },
  { // L
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0
  },
  { // L 2
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 1, 0, 0
  }
};

int rotate(int px, int py, int r) {
  switch (r % 4) {
    case 0: return py * 4 + px;       // 0
    case 1: return 12 + py - (px * 4);// 90
    case 2: return 15 - (py * 4) - px;// 180
    case 3: return 3 - py + (px * 4); // 270
  }
  return 0;
}

void draw_rect(int x, int y, int sx, int sy) {
  Bdisp_DrawLineVRAM(x, y, x+sx, y);
  Bdisp_DrawLineVRAM(x, y, x, y+sy);
  Bdisp_DrawLineVRAM(x+sx, y, x+sx, y+sy);
  Bdisp_DrawLineVRAM(x, y+sy, x+sx, y+sy);
}

void draw_tetrb(int x, int y) {
  int i, k;
  if (field[y*fieldWidth+x] == 2) return;
  if (field[y*fieldWidth+x] == 8) {
    for (i = 0; i < 4; i++)
      for (k = 0; k < 4; k++)
        Bdisp_SetPoint_VRAM(i+(x*4+1),k+(y*4+2),tetrv[k][i]);

    return;
  }
  for (i = 0; i < 4; i++)
    for (k = 0; k < 4; k++)
      Bdisp_SetPoint_VRAM(i+(x*4+1),k+(y*4+2),tetrb[k][i]);
}

int does_piece_fit(int ntetromino, int rotation, int posx, int posy) {
  int px, py, pi, fi;
  for (px = 0; px < 4; px++) {
    for (py = 0; py < 4; py++) {
      pi = rotate(px, py, rotation);
      fi = (posy + py) * fieldWidth + (posx + px);

      if (posx + px >= 0 && posx + px < fieldWidth)
        if (posy + py >= 0 && posy + py < fieldHeight)
          if (tetromino[ntetromino][pi] != 0 && field[fi] != 0)
            return 0;

      /*if (posx + px < 0 || posx + px > fieldWidth-1 || posy + py < 0 || posy + py > fieldHeight-1)
        if (tetromino[ntetromino][pi] == 1)
          return 0;*/
    }
  }

  return 1;
}

int AddIn_main(int isAppli, unsigned short OptionNum)
{
  unsigned int key;
  unsigned char scoretxt[20];
  unsigned char linestxt[20];
  unsigned char randn[20];
  unsigned int key1 = 0, key2 = 0;
  short unused = 0;
  int gameover = 0;
  int x, y, px, py, line;
  int currentPiece = 1;
  int nextPiece = 2;
  int heldPiece = -1;
  int t;
  int currentRotation = 0;
  int currentX = fieldWidth / 2;
  int currentY = 0;
  int speed = 20;
  int speedCounter = 0;
  int rotateHold = 1;
  int pieceCount = 0;
  int score = 0;
  int slines = 0;

  int vlines[8];
  int cvlines = 0;

  // DISPBOX tetArea;
  // tetArea.left = 4;
  // tetArea.top = 1;
  // tetArea.right = 45;
  // tetArea.bottom = 62;

  memset(vlines, 0, 8 * sizeof(int));
  memset(field, 0, fieldWidth * fieldHeight);
  for (x = 0; x < fieldWidth; x++)
    for (y = 0; y < fieldHeight; y++)
      field[y*fieldWidth+x] = (x == 0 || x == fieldWidth - 1 || y == fieldHeight - 1) ? 2 : 0;
  Bdisp_AllClr_DDVRAM();
  
  PrintMini(0, 0, (unsigned char*)"Seed:", MINI_OVER);
  string_input(0,7,&randn);
  srand((unsigned int)(atoi(randn)));
  currentPiece = rand() % 7;nextPiece = rand() % 7;
  while(!gameover) {
    Sleep(50);
    // GetKey(&key);
    key1 = 0;key2 = 0;
    Bkey_GetKeyWait(&key1, &key2, KEYWAIT_HALTOFF_TIMEROFF, 0, 0, &unused);
    Bdisp_AllClr_VRAM();
    // Bdisp_AreaClr_VRAM(&tetArea);

    speedCounter += 1;

    // currentX -= key == KEY_CTRL_LEFT && does_piece_fit(currentPiece, currentRotation, currentX - 1, currentY) ? 1 : 0;
    // currentX += key == KEY_CTRL_RIGHT && does_piece_fit(currentPiece, currentRotation, currentX + 1, currentY) ? 1 : 0;
    // currentY += key == KEY_CTRL_DOWN && does_piece_fit(currentPiece, currentRotation, currentX, currentY + 1) ? 1 : 0;
    // currentRotation += key == KEY_CTRL_SHIFT && does_piece_fit(currentPiece, currentRotation+1, currentX, currentY) ? 1 : 0;
    currentX -= key1 == 3 && key2 == 9 && does_piece_fit(currentPiece, currentRotation, currentX - 1, currentY) ? 1 : 0;
    currentX += key1 == 2 && key2 == 8 && does_piece_fit(currentPiece, currentRotation, currentX + 1, currentY) ? 1 : 0;
    currentY += key1 == 3 && key2 == 8 && does_piece_fit(currentPiece, currentRotation, currentX, currentY + 1) ? 1 : 0;

    if (key1 == 7 && key2 == 9) {
      currentRotation += (rotateHold == 1 && does_piece_fit(currentPiece, currentRotation + 1, currentX, currentY)) ? 1 : 0;
      rotateHold = 0;
    } else {
      rotateHold = 1;
    }

    if (key1 == 6 && key2 == 9) { // OPTN KEY
      if (heldPiece != -1) {
        t = currentPiece;
        currentPiece = heldPiece;
        heldPiece = t;
      } else {
        heldPiece = currentPiece;

        currentX = fieldWidth / 2;
        currentY = 0;
        currentRotation = 0;
        currentPiece = nextPiece;
        nextPiece = rand() % 7;
      }
      Sleep(75);
    }

    if (key1 == 4 && key2 == 8) gameover = 1; // EXIT KEY

    if (speedCounter >= speed) {
      if (does_piece_fit(currentPiece, currentRotation, currentX, currentY + 1) == 1)
        currentY++;
      else {
        for (px = 0; px < 4; px++)
          for (py = 0; py < 4; py++)
            if (tetromino[currentPiece][rotate(px, py, currentRotation)] == 1)
              field[(currentY + py) * fieldWidth + (currentX + px)] = 1;

        pieceCount++;
        if (pieceCount % 10 == 0)
          if (speed >= 10) speed--;

        for (py = 0; py < 4; py++) {
          if (currentY + py < fieldHeight - 1) {
            line = 1;
            for (px = 1; px < fieldWidth - 1; px++)
              line &= (field[(currentY + py) * fieldWidth + px]) != 0;

            if (line) {
              for (px = 1; px < fieldWidth - 1; px++)
                field[(currentY + py) * fieldWidth + px] = 8;
              vlines[cvlines] = currentY + py;
              cvlines++;
            }
          }
        }

        score += 25;
        if (cvlines != 0) {
          score += (1 << cvlines) * 100;
          slines += cvlines;
        }

        currentX = fieldWidth / 2;
        currentY = 0;
        currentRotation = 0;
        currentPiece = nextPiece;
        nextPiece = rand() % 7;

        gameover = does_piece_fit(currentPiece, currentRotation, currentX, currentY) ? 0 : 1;
      }
      speedCounter = 0;
    }

    for (x = 0; x < fieldWidth; x++)
      for (y = 0; y < fieldHeight; y++)
        if (field[y*fieldWidth+x] != 0)
          draw_tetrb(x, y);

    for (px = 0; px < 4; px++)
      for (py = 0; py < 4; py++)
        if (tetromino[currentPiece][rotate(px, py, currentRotation)] == 1)
          draw_tetrb(currentX + px, currentY + py);

    for (px = 0; px < 4; px++)
      for (py = 0; py < 4; py++)
        if (tetromino[nextPiece][rotate(px, py, 0)] == 1)
          draw_tetrb(px + 12 /*49 (-1 / 4)*/, py + 1 /*0 -2 / 4*/);

    if (heldPiece != -1) {
      for (px = 0; px < 4; px++)
        for (py = 0; py < 4; py++)
          if (tetromino[heldPiece][rotate(px, py, 0)] == 1)
            draw_tetrb(px + 27 /*49 (-1 / 4)*/, py + 1 /*0 -2 / 4*/);
    }

    draw_rect(4, 1, 41, 61);

    memset(scoretxt, 0, 20);memset(linestxt, 0, 20);
    sprintf(scoretxt, "SCORE %d", score);
    sprintf(linestxt, "LINES %d", slines);
    PrintMini(50, 56, (unsigned char*)scoretxt, MINI_OVER);
    PrintMini(50, 56-7, (unsigned char*)linestxt, MINI_OVER);
    PrintMini(48+20, 1, (unsigned char*)"< Next", MINI_OVER);
    PrintMini(108-25, 7, (unsigned char*)"Hold >", MINI_OVER);
    PrintMini(48+20+7, 21, (unsigned char*)"TETRIS", MINI_OVER);

    draw_rect(48, 47, 125-47, 61-46);
    draw_rect(48, 1, 17, 25);
    draw_rect(108, 1, 17, 25);

    if (cvlines != 0) {
      Bdisp_PutDisp_DD();
      Sleep(400);

      for (y = 0; y < cvlines; y++) {
        for (px = 1; px < fieldWidth - 1; px++) {
          for (py = vlines[y]; py > 0; py--)
            field[py * fieldWidth + px] = field[(py - 1) * fieldWidth + px];
          field[px] = 0;
        }
      }
      cvlines = 0;
    }

    Bdisp_PutDisp_DD();
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
