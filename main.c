/*****************************************
 * I am making a game where the player must reach the 
 * end of the building while fighting various enemies
 * along the way.
 * 
 * In the end, the player will move across a scrolling
 * background, punching and kicking enemies that come at
 * them. There will be bosses and levels. Right now, the
 * player can move left and right, as well as jump.
    ******************************************/

#include "myLib.h"
#include "labTiles.h"
#include "game.h"
#include "sound.h"
#include "freddie.h"

unsigned int buttons;
unsigned int oldButtons;

int main()
{
    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE;
    // level1 background
    REG_BG0CNT = CBB(1) | SBB(28) | BG_SIZE0 | BG_PRIO2 | COLOR256;

    buttons = BUTTONS;

    aButtonState = OFF;
    bButtonState = OFF;
    selectButtonState = OFF;
    startButtonState = OFF;
    rightButtonState = OFF;
    leftButtonState = OFF;
    upButtonState = OFF;
    downButtonState = OFF;
    rButtonState = OFF;
    lButtonState = OFF;

    setupInterrupts();
    setupSounds();
    start();
    
    playSoundA(freddie, FREDDIELEN, FREDDIEFREQ, 1);

    while(1)
    {


        player.state = IDLE;
        player.dir = 0;

        if (player.counter % 20 == 0) {
            if (frame == 5)
                frame = 0;
            else
                frame++;
        }

        switch(state) {

            case STARTSCREEN:
            // States
                buttonCheck();
                drawPlayer();
                player.counter++;
                if (player.counter == 99 && player.kick == 1 && player.col == 140) {
                    game();
                } else if (player.counter == 99 && player.kick == 1 && player.col == 45) {
                    instructions();
                }
                break;
            case INSTRUCTIONS:
                if (BUTTON_HELD(BUTTON_START)) {
                    if (startButtonState == OFF) {
                        startButtonState = ON;
                        start();
                    }
                } else {
                    startButtonState = OFF;
                }
                break;
            case GAMESCREEN:
                hideStrings();
                sprintf(buffer, "%d", score);
                drawString(2, 90, "SCORE ");
                drawString(2, 126, buffer);
                movementCheck();
                jumpCheck();
                buttonCheck();

                player.counter++;
                drawPlayer();
                
                if (score >= 50) {
                    state = WINSCREEN;
                }
                break;
            case PAUSESCREEN:
                hideStrings();
                drawString(2, 100, "PAUSED");
                buttonCheck();
                break;
            case LOSESCREEN:
                hideStrings();
                drawString(67, 96, "YOU LOSE");
                buttonCheck();
                break;
            case WINSCREEN:
                hideStrings();
                win();
                if (BUTTON_HELD(BUTTON_START)) {
                    if (startButtonState == OFF) {
                        startButtonState = ON;
                        start();
                    }
                } else {
                    startButtonState = OFF;
                }
                break;
        }


        vbcounter++;
        waitForVblank();

        shadowOAM[64].attr1 = player.counter;
        DMANow(3, shadowOAM, OAM, sizeof(shadowOAM)/2);
    }
    return 0;
}