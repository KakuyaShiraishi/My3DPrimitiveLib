#ifndef H_TRANSFORM
#define H_TRANSFORM

#include <math.h>
#include "Vector.h"
#include "Matrix.h"
#include "Exception.h"

class ScaleTrans     : public Matrix {public: ScaleTrans(Vector &v);};
class TranslateTrans : public Matrix {public: TranslateTrans(Vector &v);};
class RotateTrans    : public Matrix {public: RotateTrans(AXIS::AXIS axis, float angle);};

class ComboTrans : public Matrix
{
public:
	ComboTrans(
		Vector &origin,
		Vector &angle,
		Vector &scale
		);
};

class ProjectTrans : public Matrix
{
protected:
	float cx;
	float cy;
public:
	ProjectTrans(
		float sw, float sh, float n, float f
		);
};

class ProjectPerspectTrans : public ProjectTrans
{
public:
	ProjectPerspectTrans(
		float sw, float sh, float aspect, float n, float f,
		float halfTan
		);
};

class ProjectOrthoTrans : public ProjectTrans
{
public:
	ProjectOrthoTrans(
		float sw, float sh, float aspect, float n, float f,
		float zoom
		);
};

#endif