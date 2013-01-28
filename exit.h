
//{{BLOCK(exit)

//======================================================================
//
//	exit, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 9 tiles (t reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 576 + 2048 = 3136
//
//	Time-stamp: 2011-11-30, 16:39:58
//	Exported by Cearn's GBA Image Transmogrifier
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef __EXIT__
#define __EXIT__

#define exitTilesLen 576
extern const unsigned short exitTiles[288];

#define exitMapLen 2048
extern const unsigned short exitMap[1024];

#define exitPalLen 512
extern const unsigned short exitPal[256];

#endif // __EXIT__

//}}BLOCK(exit)
