#include "game.h"
#include "sound.h"

int state = STARTSCREEN;
    

void splash() {
    
}

void start() {
    state = STARTSCREEN;
    
    isjumping = OFF;
    frame = 0;
    player.row = 35;
    player.col = 140;
    GRAV = -3;
    player.counter = 0;
    player.state = IDLE;
    player.prevstate = IDLE;
    player.kick = 0;
    menuPos = 0;
    letters = 0;
    hOff = 0;
    REG_BG0HOFS = hOff;
    REG_BG1VOFS = 20;
    score = 0;
    
    loadPalette(startPal);
    DMANow(3, (unsigned int*)startTiles, &CHARBLOCKBASE[1], startTilesLen/2);
    DMANow(3, (unsigned int*)startMap, &SCREENBLOCKBASE[28], startMapLen/2);
    
    DMANow(3, (unsigned int*)tilesTiles, &CHARBLOCKBASE[4], tilesTilesLen/2);
    DMANow(3, (unsigned int*)tilesPal, SPRITE_PALETTE, tilesPalLen/2);

    int i;
    for (i = 0; i < 128; i++) {
        shadowOAM[i].attr0 = ATTR0_HIDE;
    }
    
}

void instructions() {
    state = INSTRUCTIONS;
    int i;
    for (i = 0; i < 128; i++) {
        shadowOAM[i].attr0 = ATTR0_HIDE;
    }
    loadPalette(instructionsPal);
    DMANow(3, (unsigned int*)instructionsTiles, &CHARBLOCKBASE[1], instructionsTilesLen/2);
    DMANow(3, (unsigned int*)instructionsMap, &SCREENBLOCKBASE[28], instructionsMapLen/2);
    
    drawString(10, 40, "INSTRUCTIONS");
    
    drawString(30, 90, "LEFT AND RI ");
    drawString(30, 156, "GHT TO MOVE");
    
    drawString(46, 90, "UP JUMPS");
    
    drawString(62, 90, "A KICKS");
}

void game() {
    state = GAMESCREEN;
    
    isjumping = OFF;
    frame = 0;
    player.row = 96;
    player.col = 200;
    GRAV = -3;
    player.counter = 0;
    player.state = IDLE;
    player.prevstate = RIGHT;
    player.kick = 0;
    hOff = 0;
    REG_BG0HOFS = hOff;
    flip = 0;
    letters = 0;
    
    enemy1.current = 0;
    enemy1.col = -10;
    enemy2.current = 0;
    enemy2.col = -10;
    enemy3.current = 0;
    enemy3.col = -10;
    
    enemy1.dead = FALSE;
    enemy2.dead = FALSE;
    enemy3.dead = FALSE;
    
    shadowOAM[5].attr0 = ATTR0_HIDE;
    shadowOAM[6].attr0 = ATTR0_HIDE;
    shadowOAM[7].attr0 = ATTR0_HIDE;
    shadowOAM[8].attr0 = ATTR0_HIDE;
    score = 0;
    
    // exit sign
    REG_BG1CNT = CBB(0) | SBB(27) | BG_SIZE0 | BG_PRIO0 | COLOR256;
    
    loadPalette(level1Pal);
    // level1 background
    DMANow(3, (unsigned int*)level1Tiles, &CHARBLOCKBASE[1], level1TilesLen/2);
    DMANow(3, (unsigned int*)level1Map, &SCREENBLOCKBASE[28], level1MapLen/2);
    // exit sign
    DMANow(3, (unsigned int*)exitTiles, &CHARBLOCKBASE[0], exitTilesLen/2);
    DMANow(3, (unsigned int*)exitMap, &SCREENBLOCKBASE[27], exitMapLen/2);
    // sprites
    DMANow(3, (unsigned int*)tilesTiles, &CHARBLOCKBASE[4], tilesTilesLen/2);
    DMANow(3, (unsigned int*)tilesPal, SPRITE_PALETTE, tilesPalLen/2);
    drawPlayer();
    
}

void pause() {
    state = PAUSESCREEN;

}

void win() {
    state = WINSCREEN;
    loadPalette(winPal);
    DMANow(3, (unsigned int*)winTiles, &CHARBLOCKBASE[1], winTilesLen/2);
    DMANow(3, (unsigned int*)winMap, &SCREENBLOCKBASE[28], winMapLen/2);
    REG_BG0CNT = CBB(1) | SBB(28) | BG_SIZE0 | BG_PRIO0 | COLOR256;
    REG_BG0HOFS = 0;

}

void lose() {
    enemy1.current = 0;
    enemy1.col = -10;
    enemy2.current = 0;
    enemy2.col = -10;
    enemy3.current = 0;
    enemy3.col = -10;
    state = LOSESCREEN;
}

void jumpCheck() {
    if (upButtonState && player.row >= 95 && !isjumping) {
        //player.acc = 40;
        player.vel = 14;
        isjumping = ON;
    } if (isjumping) {
        player.row = player.row - player.vel;
        player.row = player.row - GRAV;
        player.col += player.dir;
        //player.vel = player.acc + player.vel;
    } if (player.vel >= -player.vel) {
        player.vel = player.vel - 1;
    } if (player.row >= 95) {
        player.row = 96;
        isjumping = OFF;
    }
}

void buttonCheck() {
    oldButtons = buttons;
    buttons = BUTTONS;
    
    // BUTTON A
    if (BUTTON_HELD(BUTTON_A)) {
        if (aButtonState == OFF) {
            aButtonState = ON;
            if (player.kick != 1) {
                player.kick = 1;
                player.counter = 0;
            } else if (state == LOSESCREEN && BUTTON_HELD(BUTTON_A)) {
                start();
            }
        }
    } else {
        aButtonState = OFF;
    }
    
    // BUTTON B
    if (BUTTON_HELD(BUTTON_B)) {
        if ((bButtonState == OFF)) {
            bButtonState = ON;
        } 
    } else {
        bButtonState = OFF;
    }
    
    // BUTTON SELECT
    if (BUTTON_HELD(BUTTON_SELECT)) {
        if (selectButtonState == OFF) {
            selectButtonState = ON;
            if (enemy1.current == 1) {
                enemy1.col = 0;
                enemy1.vel = player.col % 3;
                shadowOAM[5].attr0 = ATTR0_HIDE;
                shadowOAM[6].attr0 = ATTR0_HIDE;
                enemy1.dead = TRUE;
                score++;
            } if (enemy2.current == 1) {
                enemy2.col = 0;
                enemy2.vel = player.col % 3;
                shadowOAM[7].attr0 = ATTR0_HIDE;
                shadowOAM[8].attr0 = ATTR0_HIDE;
                enemy2.dead = TRUE;
                score++;
            } if (enemy3.current == 1) {
                enemy3.col = 0;
                enemy3.vel = player.col % 3;
                shadowOAM[9].attr0 = ATTR0_HIDE;
                shadowOAM[10].attr0 = ATTR0_HIDE;
                enemy3.dead = TRUE;
                score++;
            }
        }
    } else {
        selectButtonState = OFF;
    }
    
    // BUTTON START
    if (BUTTON_HELD(BUTTON_START)) {
        if (startButtonState == OFF) {
            startButtonState = ON;
            if (player.kick != 1 && state == STARTSCREEN) {
                player.kick = 1;
                player.counter = 0;
            } else if (state == PAUSESCREEN && BUTTON_HELD(BUTTON_START)) {
                state = GAMESCREEN;
            } else if (state == GAMESCREEN && BUTTON_HELD(BUTTON_START)) {
                pause();
            } else if (state == LOSESCREEN && BUTTON_HELD(BUTTON_START)) {
                start();
            }
        } 
    } else {
        startButtonState = OFF;
    }
    
    // BUTTON RIGHT
    if (BUTTON_HELD(BUTTON_RIGHT)) {
        if (rightButtonState == OFF) {
            rightButtonState = ON;
            flip = ATTR1_HFLIP;
        }
    } else {
        rightButtonState = OFF;
    }
    
    // BUTTON LEFT
    if (BUTTON_HELD(BUTTON_LEFT)) {
        if (leftButtonState == OFF) {
            leftButtonState = ON;
            flip = 0;
        }
    } else {
        leftButtonState = OFF;
    }
    
    // BUTTON UP
    if (BUTTON_HELD(BUTTON_UP)) {
        if (upButtonState == OFF) {
            upButtonState = ON;
        }
    } else {
        upButtonState = OFF;
    }
    
    // BUTTON DOWN
    if (BUTTON_HELD(BUTTON_DOWN)) {
        if (downButtonState == OFF) {
            downButtonState = ON;
        }
    } else {
        downButtonState = OFF;
    }
    
    // BUTTON R
    if (BUTTON_HELD(BUTTON_R)) {
        if (rButtonState == OFF) {
            rButtonState = ON;
        }
    } else {
        rButtonState = OFF;
    }
    
    // BUTTON L
    if (BUTTON_HELD(BUTTON_L)) {
        if (lButtonState == OFF) {
            lButtonState = ON;
        }
    } else {
        lButtonState = OFF;
    }
}

void movementCheck() {
    hOffdiff = 0;
    if (leftButtonState && player.col > 120) {
        player.state = LEFT;
        player.dir = -1;
    } else if (leftButtonState && player.col <= 120) {
        player.state = LEFT;
        player.dir = 0;
        hOffdiff = 1;
        hOff--;
    }
    
    if (rightButtonState && player.col < 200) {
        player.state = RIGHT;
        player.dir = 1;
    } else if (rightButtonState && player.col >= 200) {
        player.state = RIGHT;
        player.dir = 0;
        hOffdiff = -1;
        hOff++;
    }
    
    // check for enemies
    if ((hOff % 21 == 0) && enemy1.current != 1) {
        enemy1.col = 0;
        enemy1.row = 96;
        enemy1.vel = player.col % 3;
        enemy1.current = 1;
    } if ((hOff % 54 == 0) && enemy2.current != 1) {
        enemy2.col = 0;
        enemy2.row = 96;
        enemy2.vel = player.col % 3;
        enemy2.current = 1;
    } if ((hOff % 66 == 0) && enemy3.current != 1) {
        enemy3.col = 0;
        enemy3.row = 96;
        enemy3.vel = player.col % 3;
        enemy3.current = 1;
    }
    
    drawStudent();
    REG_BG1HOFS = 100 + hOff + hOff/4;
    REG_BG1VOFS = -9;
    REG_BG0HOFS = hOff;
}

int i;
void drawPlayer() {
    
    // if on the start screen
    if (state == STARTSCREEN) {
        
        flip = ATTR1_HFLIP;
        
        if (player.kick == 1 && player.counter < 10) { // kick 1
            // body
            shadowOAM[0].attr0 = player.row + 3 | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[0].attr1 = player.col | ATTR1_SIZE32 | flip;
            shadowOAM[0].attr2 = SPRITEOFFSET16(0, 5) | SUBPALETTE(0);
            // right foot
            shadowOAM[1].attr0 = player.row + 35 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[1].attr1 = player.col + 8 | ATTR1_SIZE8 | flip;
            shadowOAM[1].attr2 = SPRITEOFFSET16(2, 4) | SUBPALETTE(0);
            // left foot
            shadowOAM[2].attr0 = player.row + 35 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[2].attr1 = player.col | ATTR1_SIZE8 | flip;
            shadowOAM[2].attr2 = SPRITEOFFSET16(3, 4) | SUBPALETTE(0);
        } else if (player.kick == 1 && player.state != LEFT && player.counter >= 10 && player.counter < 20) { // kick 2
            // body
            shadowOAM[0].attr0 = player.row + 3 | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[0].attr1 = player.col | ATTR1_SIZE32 | flip;
            shadowOAM[0].attr2 = SPRITEOFFSET16(0, 7) | SUBPALETTE(0);
            // left foot
            shadowOAM[1].attr0 = player.row + 35 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[1].attr1 = player.col | ATTR1_SIZE8 | flip;
            shadowOAM[1].attr2 = SPRITEOFFSET16(0, 9) | SUBPALETTE(0);
            shadowOAM[2].attr0 = ATTR0_HIDE;
        } else if (player.kick == 1 && player.state != LEFT && player.counter >= 20 && player.counter < 100) { // kick 2
            // body
            shadowOAM[0].attr0 = player.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[0].attr1 = player.col | ATTR1_SIZE32 | flip;
            shadowOAM[0].attr2 = SPRITEOFFSET16(0, 10) | SUBPALETTE(0);
            // right leg
            shadowOAM[1].attr0 = player.row + 8 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[1].attr1 = player.col + 16 | ATTR1_SIZE8 | flip;
            shadowOAM[1].attr2 = SPRITEOFFSET16(2, 9) | SUBPALETTE(0);
            
            shadowOAM[2].attr0 = player.row + 16 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[2].attr1 = player.col + 16 | ATTR1_SIZE8 | flip;
            shadowOAM[2].attr2 = SPRITEOFFSET16(3, 9) | SUBPALETTE(0);
            // right foot
            shadowOAM[3].attr0 = player.row + 8 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[3].attr1 = player.col + 24 | ATTR1_SIZE8 | flip;
            shadowOAM[3].attr2 = SPRITEOFFSET16(1, 9) | SUBPALETTE(0);
            // left foot
            shadowOAM[4].attr0 = player.row + 32 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[4].attr1 = player.col + 8 | ATTR1_SIZE8 | flip;
            shadowOAM[4].attr2 = SPRITEOFFSET16(0, 12) | SUBPALETTE(0);
            
            if (player.counter == 99) {
                playSoundB(photon, PHOTONLEN, PHOTONFREQ, 0);
            }
        } else { // idle animation
            
            if (upButtonState) {
                player.row = 35;
                player.col = 140;
                menuPos = 0;
            } if (downButtonState) {
                player.row = 70;
                player.col = 45;
                menuPos = 1;
            }
            
            player.kick = 0;
            shadowOAM[2].attr0 = ATTR0_HIDE;
            shadowOAM[3].attr0 = ATTR0_HIDE;
            shadowOAM[4].attr0 = ATTR0_HIDE;
            // body
            shadowOAM[0].attr0 = player.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[0].attr1 = player.col | ATTR1_SIZE16 | flip;
            shadowOAM[0].attr2 = SPRITEOFFSET16(0, 0) | SUBPALETTE(0);
            // back
            shadowOAM[1].attr0 = player.row + 10 | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[1].attr1 = player.col - 2 | ATTR1_SIZE16 | flip;
            shadowOAM[1].attr2 = SPRITEOFFSET16(0, 1) | SUBPALETTE(0);
        } 
    
    // if on the game screen
    } else {
        
        player.col += player.dir;
    
        if (player.kick == 1 && player.state != LEFT && player.counter < 10) { // kick 1
            // body
            shadowOAM[0].attr0 = player.row + 3 | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[0].attr1 = player.col | ATTR1_SIZE32 | flip;
            shadowOAM[0].attr2 = SPRITEOFFSET16(0, 5) | SUBPALETTE(0);
            // right foot
            shadowOAM[1].attr0 = player.row + 35 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[1].attr1 = player.col | ATTR1_SIZE8 | flip;
            shadowOAM[1].attr2 = SPRITEOFFSET16(2, 4) | SUBPALETTE(0);
            // left foot
            shadowOAM[2].attr0 = player.row + 35 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[2].attr1 = player.col + 8 | ATTR1_SIZE8 | flip;
            shadowOAM[2].attr2 = SPRITEOFFSET16(3, 4) | SUBPALETTE(0);
        } else if (player.kick == 1 && player.state != LEFT && player.counter >= 10 && player.counter < 20) { // kick 2
            // body
            shadowOAM[0].attr0 = player.row + 3 | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[0].attr1 = player.col | ATTR1_SIZE32 | flip;
            shadowOAM[0].attr2 = SPRITEOFFSET16(0, 7) | SUBPALETTE(0);
            // left foot
            shadowOAM[1].attr0 = player.row + 35 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[1].attr1 = player.col + 8| ATTR1_SIZE8 | flip;
            shadowOAM[1].attr2 = SPRITEOFFSET16(0, 9) | SUBPALETTE(0);
            shadowOAM[2].attr0 = ATTR0_HIDE;
        } else if (player.kick == 1 && player.state != LEFT && player.counter >= 20 && player.counter < 30) { // kick 2
            // body
            shadowOAM[0].attr0 = player.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[0].attr1 = player.col | ATTR1_SIZE32 | flip;
            shadowOAM[0].attr2 = SPRITEOFFSET16(0, 10) | SUBPALETTE(0);
            // right leg
            shadowOAM[1].attr0 = player.row + 8 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[1].attr1 = player.col - 8| ATTR1_SIZE8 | flip;
            shadowOAM[1].attr2 = SPRITEOFFSET16(2, 9) | SUBPALETTE(0);
            
            shadowOAM[2].attr0 = player.row + 16 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[2].attr1 = player.col - 8| ATTR1_SIZE8 | flip;
            shadowOAM[2].attr2 = SPRITEOFFSET16(3, 9) | SUBPALETTE(0);
            // right foot
            shadowOAM[3].attr0 = player.row + 8 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[3].attr1 = player.col - 16| ATTR1_SIZE8 | flip;
            shadowOAM[3].attr2 = SPRITEOFFSET16(1, 9) | SUBPALETTE(0);
            // left foot
            shadowOAM[4].attr0 = player.row + 32 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[4].attr1 = player.col | ATTR1_SIZE8 | flip;
            shadowOAM[4].attr2 = SPRITEOFFSET16(0, 12) | SUBPALETTE(0);
            
            if (player.counter == 29) {
                playSoundB(photon, PHOTONLEN, PHOTONFREQ, 0);
            }
            
            // collision check
            if (((player.kick == 1) && ((enemy1.col + 14) >= (player.col - 16))) || (enemy1.col > 230)) {
                enemy1.current = 0;
                enemy1.col = 0;
                enemy1.vel = player.col % 3;
                shadowOAM[5].attr0 = ATTR0_HIDE;
                shadowOAM[6].attr0 = ATTR0_HIDE;
                enemy1.dead = TRUE;
                score++;
            } if (((player.kick == 1) && ((enemy2.col + 14) >= (player.col - 16))) || (enemy2.col > 230)) {
                enemy2.current = 0;
                enemy2.col = 0;
                enemy2.vel = player.col % 3;
                shadowOAM[7].attr0 = ATTR0_HIDE;
                shadowOAM[8].attr0 = ATTR0_HIDE;
                enemy2.dead = TRUE;
                score++;
            } if (((player.kick == 1) && ((enemy3.col + 14) >= (player.col - 16))) || (enemy3.col > 230)) {
                enemy3.current = 0;
                enemy3.col = 0;
                enemy3.vel = player.col % 3;
                shadowOAM[9].attr0 = ATTR0_HIDE;
                shadowOAM[10].attr0 = ATTR0_HIDE;
                enemy3.dead = TRUE;
                score++;
            }
        } else if (player.state == LEFT && (frame == 0 || frame == 2 || frame == 4)) { // walking animation
            // body
            shadowOAM[0].attr0 = player.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[0].attr1 = player.col - 2 | ATTR1_SIZE32 | flip;
            shadowOAM[0].attr2 = SPRITEOFFSET16(0, 2) | SUBPALETTE(0);
            // left foot
            shadowOAM[1].attr0 = player.row + 32 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[1].attr1 = player.col - 2 | ATTR1_SIZE8 | flip;
            shadowOAM[1].attr2 = SPRITEOFFSET16(0, 4) | SUBPALETTE(0);
            // right foot
            shadowOAM[2].attr0 = player.row + 32 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[2].attr1 = player.col + 6 | ATTR1_SIZE8 | flip;
            shadowOAM[2].attr2 = SPRITEOFFSET16(1, 4) | SUBPALETTE(0);
        } else { // idle animation
            player.kick = 0;
            shadowOAM[2].attr0 = ATTR0_HIDE;
            shadowOAM[3].attr0 = ATTR0_HIDE;
            shadowOAM[4].attr0 = ATTR0_HIDE;
            // body
            shadowOAM[0].attr0 = player.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[0].attr1 = player.col | ATTR1_SIZE16 | flip;
            shadowOAM[0].attr2 = SPRITEOFFSET16(0, 0) | SUBPALETTE(0);
            // back
            shadowOAM[1].attr0 = player.row + 10 | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[1].attr1 = player.col + 2 | ATTR1_SIZE16 | flip;
            shadowOAM[1].attr2 = SPRITEOFFSET16(0, 1) | SUBPALETTE(0);
        } 
    }
}

void drawStudent() {
    if (enemy1.current == 1) {
        if (hOffdiff != 0) {
            enemy1.col = enemy1.col + hOffdiff;
        }
        enemy1.col = enemy1.col + 1 + enemy1.vel;
        if (frame == 0 || frame == 2 || frame == 4) {
            // body
            shadowOAM[5].attr0 = enemy1.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[5].attr1 = enemy1.col | ATTR1_SIZE32;
            shadowOAM[5].attr2 = SPRITEOFFSET16(4, 0) | SUBPALETTE(0);
            // legs
            shadowOAM[6].attr0 = enemy1.row + 24 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[6].attr1 = enemy1.col - 2 | ATTR1_SIZE16;
            shadowOAM[6].attr2 = SPRITEOFFSET16(4, 2) | SUBPALETTE(0);
        } else {
            // body
            shadowOAM[5].attr0 = enemy1.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[5].attr1 = enemy1.col | ATTR1_SIZE32;
            shadowOAM[5].attr2 = SPRITEOFFSET16(4, 0) | SUBPALETTE(0);
            // legs
            shadowOAM[6].attr0 = enemy1.row + 24 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[6].attr1 = enemy1.col | ATTR1_SIZE16;
            shadowOAM[6].attr2 = SPRITEOFFSET16(6, 2) | SUBPALETTE(0);
        }
        
        // collision check
        if (((enemy1.col + 12) >= player.col) && ((enemy1.col - 12) <= player.col) && (player.kick == 0) && (isjumping == OFF)) {
            lose();
        }
    } if (enemy2.current == 1) {
        if (hOffdiff != 0) {
            enemy2.col = enemy2.col + hOffdiff;
        }
        enemy2.col = enemy2.col + 1 + enemy2.vel;
        if (frame == 0 || frame == 2 || frame == 4) {
            // body
            shadowOAM[7].attr0 = enemy2.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[7].attr1 = enemy2.col | ATTR1_SIZE32;
            shadowOAM[7].attr2 = SPRITEOFFSET16(4, 0) | SUBPALETTE(0);
            // legs
            shadowOAM[8].attr0 = enemy2.row + 24 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[8].attr1 = enemy2.col - 2 | ATTR1_SIZE16;
            shadowOAM[8].attr2 = SPRITEOFFSET16(4, 2) | SUBPALETTE(0);
        } else {
            // body
            shadowOAM[7].attr0 = enemy2.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[7].attr1 = enemy2.col | ATTR1_SIZE32;
            shadowOAM[7].attr2 = SPRITEOFFSET16(4, 0) | SUBPALETTE(0);
            // legs
            shadowOAM[8].attr0 = enemy2.row + 24 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[8].attr1 = enemy2.col | ATTR1_SIZE16;
            shadowOAM[8].attr2 = SPRITEOFFSET16(6, 2) | SUBPALETTE(0);
        }
        
        // collision check
        if (((enemy2.col + 12) >= player.col) && ((enemy2.col - 12) <= player.col) && (player.kick == 0) && (isjumping == OFF)) {
            lose();
        }
    } if (enemy3.current == 1) {
        if (hOffdiff != 0) {
            enemy3.col = enemy3.col + hOffdiff;
        }
        enemy3.col = enemy3.col + 1 + enemy3.vel;
        if (frame == 0 || frame == 2 || frame == 4) {
            // body
            shadowOAM[9].attr0 = enemy3.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[9].attr1 = enemy3.col | ATTR1_SIZE32;
            shadowOAM[9].attr2 = SPRITEOFFSET16(4, 0) | SUBPALETTE(0);
            // legs
            shadowOAM[10].attr0 = enemy3.row + 24 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[10].attr1 = enemy3.col - 2 | ATTR1_SIZE16;
            shadowOAM[10].attr2 = SPRITEOFFSET16(4, 2) | SUBPALETTE(0);
        } else {
            // body
            shadowOAM[9].attr0 = enemy3.row | ATTR0_4BPP | ATTR0_TALL;
            shadowOAM[9].attr1 = enemy3.col | ATTR1_SIZE32;
            shadowOAM[9].attr2 = SPRITEOFFSET16(4, 0) | SUBPALETTE(0);
            // legs
            shadowOAM[10].attr0 = enemy3.row + 24 | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[10].attr1 = enemy3.col | ATTR1_SIZE16;
            shadowOAM[10].attr2 = SPRITEOFFSET16(6, 2) | SUBPALETTE(0);
        }
        
        // collision check
        if (((enemy3.col + 12) >= player.col) && ((enemy3.col - 12) <= player.col) && (player.kick == 0) && (isjumping == OFF)) {
            lose();
        }
    }
}

void drawChar(int row, int col, char ch) {
    letters++;
    if ((ch == 'A') || (ch == 'a')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 0) | SUBPALETTE(0);
    } else if ((ch == 'B') || (ch == 'b')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 1) | SUBPALETTE(0);
    } else if ((ch == 'C') || (ch == 'c')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 2) | SUBPALETTE(0);
    } else if ((ch == 'D') || (ch == 'd')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 3) | SUBPALETTE(0);
    } else if ((ch == 'E') || (ch == 'e')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 4) | SUBPALETTE(0);
    } else if ((ch == 'F') || (ch == 'f')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 5) | SUBPALETTE(0);
    } else if ((ch == 'G') || (ch == 'g')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 6) | SUBPALETTE(0);
    } else if ((ch == 'H') || (ch == 'h')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 7) | SUBPALETTE(0);
    } else if ((ch == 'I') || (ch == 'i')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 8) | SUBPALETTE(0);
    } else if ((ch == 'J') || (ch == 'j')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 9) | SUBPALETTE(0);
    } else if ((ch == 'K') || (ch == 'k')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 10) | SUBPALETTE(0);
    } else if ((ch == 'L') || (ch == 'l')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 11) | SUBPALETTE(0);
    } else if ((ch == 'M') || (ch == 'm')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 12) | SUBPALETTE(0);
    } else if ((ch == 'N') || (ch == 'n')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 13) | SUBPALETTE(0);
    } else if ((ch == 'O') || (ch == 'o')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 14) | SUBPALETTE(0);
    } else if ((ch == 'P') || (ch == 'p')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 15) | SUBPALETTE(0);
    } else if ((ch == 'Q') || (ch == 'q')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 16) | SUBPALETTE(0);
    } else if ((ch == 'R') || (ch == 'r')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 17) | SUBPALETTE(0);
    } else if ((ch == 'S') || (ch == 's')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 18) | SUBPALETTE(0);
    } else if ((ch == 'T') || (ch == 't')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 19) | SUBPALETTE(0);
    } else if ((ch == 'U') || (ch == 'u')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 20) | SUBPALETTE(0);
    } else if ((ch == 'V') || (ch == 'v')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 21) | SUBPALETTE(0);
    } else if ((ch == 'W') || (ch == 'w')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 22) | SUBPALETTE(0);
    } else if ((ch == 'X') || (ch == 'x')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 23) | SUBPALETTE(0);
    } else if ((ch == 'Y') || (ch == 'y')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 24) | SUBPALETTE(0);
    } else if ((ch == 'Z') || (ch == 'z')) {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 25) | SUBPALETTE(0);
    } else if (ch == '1') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 26) | SUBPALETTE(0);
    } else if (ch == '2') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 27) | SUBPALETTE(0);
    } else if (ch == '3') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 28) | SUBPALETTE(0);
    } else if (ch == '4') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 29) | SUBPALETTE(0);
    } else if (ch == '5') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 30) | SUBPALETTE(0);
    } else if (ch == '6') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(31, 31) | SUBPALETTE(0);
    } else if (ch == '7') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(30, 28) | SUBPALETTE(0);
    } else if (ch == '8') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(30, 29) | SUBPALETTE(0);
    } else if (ch == '9') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(30, 30) | SUBPALETTE(0);
    } else if (ch == '0') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(30, 31) | SUBPALETTE(0);
    } else if (ch == ' ') {
        shadowOAM[40 + letters].attr0 = row | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40 + letters].attr1 = col | ATTR1_SIZE8;
        shadowOAM[40 + letters].attr2 = SPRITEOFFSET16(30, 27) | SUBPALETTE(0);
    }
}

void drawString(int row, int col, char *str) {
    while(*str) {
        drawChar(row, col, *str);
        str++;
        col += 6;
    }
}

void hideStrings() {
    int i;
    for (i = 0; i <= letters; i++) {
        shadowOAM[40 + i].attr0 = ATTR0_HIDE;
    }
    letters = 0;
}