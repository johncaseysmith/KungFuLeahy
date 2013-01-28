
//{{BLOCK(labTiles)

//======================================================================
//
//	labTiles, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 8 tiles (t reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 512 + 2048 = 3072
//
//	Time-stamp: 2011-11-02, 00:07:47
//	Exported by Cearn's GBA Image Transmogrifier
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef __LABTILES__
#define __LABTILES__

#define labTilesTilesLen 512
extern const unsigned short labTilesTiles[256];

#define labTilesMapLen 2048
extern const unsigned short labTilesMap[1024];

#define labTilesPalLen 512
extern const unsigned short labTilesPal[256];

#endif // __LABTILES__

//}}BLOCK(labTiles)
