#include <stdlib.h>
#include <string.h>
#include "myLib.h"
#include "start.h"
#include "tiles.h"
#include "level1.h"
#include "exit.h"
#include "instructions.h"
#include "win.h"
#include "photon.h"

typedef struct {
    int row;
    int col;
    int dir;
    int acc;
    int vel;
    int state;
    int prevstate;
    int counter;
    int kick;
    int current;
    int dead;
} CHARACTER;

int GRAV;
int frame;
OBJ_ATTR shadowOAM[128];
int vbcounter;
int stop;
int flip;
int isjumping;
int menuPos;
int letters;
int hOff;
int hOffdiff;
int score;
char buffer[50];

extern int state;

void drawPlayer();
void jump();
void drawChar(int row, int col, char ch);
void drawString(int row, int col, char *str);

CHARACTER player;
CHARACTER enemy1;
CHARACTER enemy2;
CHARACTER enemy3;

int aButtonState;
int bButtonState;
int selectButtonState;
int startButtonState;
int rightButtonState;
int leftButtonState;
int upButtonState;
int downButtonState;
int rButtonState;
int lButtonState;

#define IDLE 0
#define LEFT 1
#define RIGHT 2

#define FALSE 0
#define TRUE 1