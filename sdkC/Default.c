#include "fxlib.h"
#include "stdio.h"
#include "math.h"
#include "mathf.h"

unsigned char specChar[3] = {0x8C, 0xCB, 0xCC};

int clamp(int value, int min, int max) {
	if (value >= max) return max;
	if (value <= min) return min;
	return value;
}

int AddIn_main(int isAppli, unsigned short OptionNum)
{
		unsigned char string[20];
		unsigned int keyc;
		float playerX = 4.0;
		float playerY = 4.0;
		float playerA = 0.0;

		const int mapHeight = 16;
		const int mapWidth = 16;
		const float fov = 3.14159 / 3.0;
		const float depth = 16;
		const float detail = 0.5;

		int x, y, s;
		float b;
		float rayAngle, distanceToWall, eyeX, eyeY;
		int hitWall, testX, testY;
		int ceiling, floor;

		float mov_sp = 0.5;
		float rot_sp = 0.1;
		int mul = 1;

		int map[16][16] = {
		  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		  {1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		  {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		};

		Bdisp_AllClr_DDVRAM();
		GetKey(&keyc);

		while (keyc != KEY_CTRL_EXIT) {
			GetKey(&keyc);

			if (keyc == KEY_CTRL_UP) {
				playerX += sinf(playerA) * mov_sp;
				playerY += cosf(playerA) * mov_sp;
				if (map[clamp((int)playerY, 0, mapHeight-1)][clamp((int)playerX, 0, mapWidth-1)] == 1) {
					playerX -= sinf(playerA) * mov_sp;
					playerY -= cosf(playerA) * mov_sp;
				}
			}
			if (keyc == KEY_CTRL_DOWN) {
				playerX -= sinf(playerA) * mov_sp;
				playerY -= cosf(playerA) * mov_sp;
				if (map[clamp((int)playerY, 0, mapHeight-1)][clamp((int)playerX, 0, mapWidth-1)] == 1) {
					playerX += sinf(playerA) * mov_sp;
					playerY += cosf(playerA) * mov_sp;
				}
			}
			if (keyc == KEY_CTRL_LEFT) playerA -= rot_sp;
			if (keyc == KEY_CTRL_RIGHT) playerA += rot_sp;

			for (x = 0; x < 128; x++) {
				rayAngle = (playerA - fov / 2.0) + ((float)x / (float)128.0) * fov;
				distanceToWall = 0;
				hitWall = 0;

				eyeX = sinf(rayAngle);
				eyeY = cosf(rayAngle);

				while (hitWall == 0 && distanceToWall < depth) {
					distanceToWall += detail;

					testX = (int)(playerX + eyeX * distanceToWall);
					testY = (int)(playerY + eyeY * distanceToWall);

					if (testX < 0 || testX >= mapWidth || testY < 0 || testY >= mapHeight) {
		        hitWall = 1;
		        distanceToWall = depth;
		      }
		      else {
		        if (map[testY][testX] == 1) {
		          hitWall = 1;
		        }
		      }
				}

				ceiling = (float)32 - 64 / ((float)distanceToWall);
				floor = 64 - ceiling;

				for (y = 0; y < 64; y++) {
					if (y < ceiling) Bdisp_SetPoint_VRAM(x,y,0);
					else if (y >= ceiling && y <= floor) {
						Bdisp_SetPoint_VRAM(x,y,1);
					}
					else {
						b = 1.0 - (((float)y - 32.0) / ((float)64.0));
						if (b < 0.25) 				s = 7;
						else if (b < 0.5)   	s = 6;
						else if (b < 0.65)   	s = 5;
						else if (b < 0.75)  	s = 4;
						else if (b < 0.85)   	s = 3;
						else if (b < 0.9)   	s = 2;
						else									s = 2;

						if ((y + (x % s)) % s == 0) {
		          Bdisp_SetPoint_VRAM(x,y,1);
		        } else {
							Bdisp_SetPoint_VRAM(x,y,0);
						}
					}
				}
			}

			memset(string, 0, 20);
    	sprintf(string, "%.1f%c %.1f%c %.1f%c", playerX, specChar[1], playerY, specChar[2], playerA, specChar[0]);
			PrintMini(0, 0, (unsigned char*)string, MINI_OVER);

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
