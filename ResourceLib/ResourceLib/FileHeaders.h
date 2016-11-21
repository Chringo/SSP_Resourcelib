#ifndef RESOURCELIB_FILEHEADERS_H
#define RESOURCELIB_FILEHEADERS_H

struct MainHeader
{
	unsigned int meshes;
};

struct MeshHeader
{
	unsigned int numVerts;
	unsigned int indexLength;
	bool skeleton;
};


#endif
