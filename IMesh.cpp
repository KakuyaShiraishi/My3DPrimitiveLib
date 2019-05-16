#include "IMesh.h"

IMesh::IMesh(int vertCnt, int faceCnt)
{
	this->resize(vertCnt, faceCnt);
}

IMesh::~IMesh()
{
}

void IMesh::resize(int vertCnt, int faceCnt)
{
	mVertCnt = vertCnt;
	mFaceCnt = faceCnt;
}

int IMesh::getVertCnt()
{
	return mVertCnt;
}

int IMesh::getFaceCnt()
{
	return mFaceCnt;
}