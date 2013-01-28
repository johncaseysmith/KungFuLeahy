
//{{BLOCK(startscreen)

//======================================================================
//
//	startscreen, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 601 tiles (t reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 38464 + 2048 = 41024
//
//	Time-stamp: 2011-11-21, 16:06:31
//	Exported by Cearn's GBA Image Transmogrifier
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef __STARTSCREEN__
#define __STARTSCREEN__

#define startscreenTilesLen 38464
extern const unsigned short startscreenTiles[19232];

#define startscreenMapLen 2048
extern const unsigned short startscreenMap[1024];

#define startscreenPalLen 512
extern const unsigned short startscreenPal[256];

#endif // __STARTSCREEN__

//}}BLOCK(startscreen)
