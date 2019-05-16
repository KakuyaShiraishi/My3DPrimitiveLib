#ifndef H_IMESH
#define H_IMESH

#include "Vector.h"

class IMesh
{
protected:
	int mVertCnt;
	int mFaceCnt;
public:
	IMesh(int vertCnt, int faceCnt);
	~IMesh();
	int getVertCnt();
	int getFaceCnt();
	virtual void resize(int vertCnt, int faceCnt);
	virtual Vector *getVertices() = 0;
	virtual void setVertex(int index, float x, float y, float z) = 0;
	virtual void setFace(int index, int a, int b, int c) = 0;
	virtual void setAnchor(int index, float x, float y) = 0;
	virtual void getDim(Vector &pMin, Vector &pMax) = 0;
};

#endif