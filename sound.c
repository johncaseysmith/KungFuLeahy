#include "sound.h"
#include "game.h"

void setupSounds()
{
	// COMPLETE THIS FUNCTION !!!
	// This function will enable sounds
	
	// uncomment and complete the following lines
	REG_SOUNDCNT_X = SND_ENABLED;

	REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 |
                DSA_OUTPUT_RATIO_100 |
                DSA_OUTPUT_TO_BOTH |
                DSA_TIMER0 |
                DSA_FIFO_RESET | 
                DSB_OUTPUT_RATIO_100 |
                DSB_OUTPUT_TO_BOTH |
                DSB_TIMER1 |
                DSB_FIFO_RESET;

	REG_SOUNDCNT_L = 0;
}

void playSoundA( const unsigned char* sound, int length, int frequency, int isLooping ) {

	// COMPLETE THIS FUNCTION !!!

	// This function will play a sound out of sound channel A
    dma[1].cnt = 0;
    vbCountA = 0;
	// fist compute the timer interval for the sound.  The number of cycles divided by the frequency of the sound
    int timerinterval = 16777216/frequency;
	// then setup the DMA channel for this sound
    DMANow(1, sound, REG_FIFO_A, DMA_DESTINATION_FIXED | DMA_AT_REFRESH |
            DMA_REPEAT | DMA_32);
    
	// then setup the timer for this sound
    REG_TM0CNT = 0;
    REG_TM0D = -timerinterval;
	// then start the timer
    REG_TM0CNT = TM_ON;
	// you may have to create additional global variables for these functions to work (to stop the sounds later)
    
    soundA.data = sound;
    soundA.length = length;
    soundA.frequency = frequency;
    soundA.isPlaying = 1;
    soundA.loops = isLooping;
    soundA.duration = ((60*length)/frequency)-((length/frequency)*3)-1;

}


void playSoundB( const unsigned char* sound, int length, int frequency, int isLooping ) {

	// COMPLETE THIS FUNCTION !!!
    dma[2].cnt = 0;
    vbCountB = 0;

	// This function will play a sound out of sound channel B
	// refer to playSoundA instructions
	int timerinterval = 16777216/frequency;
	// then setup the DMA channel for this sound
    DMANow(2, sound, REG_FIFO_B, DMA_DESTINATION_FIXED | DMA_AT_REFRESH |
            DMA_REPEAT | DMA_32);
    
	// then setup the timer for this sound
    REG_TM1CNT = 0;
    REG_TM1D = -timerinterval;
	// then start the timer
    REG_TM1CNT = TM_ON;
    soundB.data = sound;
    soundB.length = length;
    soundB.frequency = frequency;
    soundB.isPlaying = 1;
    soundB.loops = isLooping;
    soundB.duration = ((60*length)/frequency)-((length/frequency)*3)-1;
}

void setupInterrupts()
{
	REG_IME = 0;
	REG_INTERRUPT = (unsigned int)interruptHandler;
	// accept interrupts
	REG_IE |= INT_VBLANK;
	// turn on interrupt sending
	REG_DISPSTAT |= INT_VBLANK_ENABLE;

	REG_IME = 1;
}


void interruptHandler()
{
	REG_IME = 0;

	if(REG_IF & INT_VBLANK)
	{

		// MODIFY THIS FUNCTION !!!
		// Add code to stop/repeat sounds here
                vbCountA++;
                if (vbCountA >= soundA.duration) {
                    REG_TM0CNT = 0;
                    dma[1].cnt = 0;
                    if (soundA.loops)
                        playSoundA(soundA.data, soundA.length, soundA.frequency, soundA.loops);
                }
                
                vbCountB++;
                if (vbCountB >= soundB.duration) {
                    REG_TM1CNT = 0;
                    dma[2].cnt = 0;
                    if (soundB.loops)
                        playSoundB(soundB.data, soundB.length, soundB.frequency, soundB.loops);
                }

		REG_IF = INT_VBLANK; 
	}

	REG_IME = 1;
}
