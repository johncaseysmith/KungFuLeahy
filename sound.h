typedef struct {
    unsigned char* data;
    int length;
    int frequency;
    int loops;
    int isPlaying;
    int duration;
} SOUND;

SOUND soundA, soundB;
int vbCountA, vbCountB;

void setupSounds();
void playSoundA( const unsigned char* sound, int length, int frequency, int isLooping );
void playSoundB( const unsigned char* sound, int length, int frequency, int isLooping );

void setupInterrupts();
void interruptHandler();