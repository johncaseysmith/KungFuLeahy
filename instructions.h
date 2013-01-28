
//{{BLOCK(instructions)

//======================================================================
//
//	instructions, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 118 tiles (t reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 7552 + 2048 = 10112
//
//	Time-stamp: 2011-12-04, 21:58:00
//	Exported by Cearn's GBA Image Transmogrifier
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef __INSTRUCTIONS__
#define __INSTRUCTIONS__

#define instructionsTilesLen 7552
extern const unsigned short instructionsTiles[3776];

#define instructionsMapLen 2048
extern const unsigned short instructionsMap[1024];

#define instructionsPalLen 512
extern const unsigned short instructionsPal[256];

#endif // __INSTRUCTIONS__

//}}BLOCK(instructions)
