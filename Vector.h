#ifndef H_VECTOR
#define H_VECTOR

#include <windows.h>
#include <math.h>
#include "Matrix.h"
#include "Util.h"

#define UNIT_VECTOR UnitVector
#define NULL_VECTOR NullVector
#define FWD_VECTOR FwdVector
#define LEFT_VECTOR LeftVector
#define UP_VECTOR UpVector
#define RAND_VECTOR Vector(rand(), rand(), rand())

namespace AXIS
{
	enum AXIS {X, Y, Z, S};
};

class Vector
{
public:
	union
	{
		float v[3];
		struct
		{
			union {float x; float roll;};
			union {float y; float pitch;};
			union {float z; float yaw;};
		};
	};

	Vector();
	~Vector();
	
	Vector(float x, float y, float z);
	Vector(Vector &v);
	Vector(float s);
	Vector(float *v);
	
	void toArray(float *v);
	
	Vector &operator=(Vector &v);
	
	Vector &operator+=(Vector &v);
	Vector &operator-=(Vector &v);
	Vector &operator&=(Vector &v);
	Vector &operator*=(float s);
	Vector &operator/=(float s);
	Vector &operator*=(Vector &v);
	Vector &operator*=(Matrix &m);
	
	Vector operator+(Vector &v);
	Vector operator-(Vector &v);
	Vector operator&(Vector &v);
	Vector operator*(float s);
	Vector operator/(float s);
	Vector operator*(Vector &v);
	Vector operator*(Matrix &m);
	
	float &operator[](AXIS::AXIS axis);
	float operator|(Vector &v);
	Vector operator-();
	bool operator==(Vector &v);
	bool operator!=(Vector &v);
	
	Vector &mask(Vector &m, Vector &v);
	Vector vec_interp(Vector &v, float s);
	float mod();
	float dist(Vector &v);
	Vector &normalize();
	Vector normal();
	Vector normTri(Vector &v1, Vector &v2);
	float angle(Vector &v);
	int compare(Vector &v1, Vector &v2);
	float sectPlane(Vector &p, Vector &v, Vector &n);
	Vector project(Vector &v);
	Vector ortho(Vector &v);
	Vector reflect(Vector &n);
	Vector &fromAngle(Vector &v);
	Vector toAngle();
	
	Vector &vec_wrap(Vector &pMin, Vector &pMax);
	Vector &vec_limit(Vector &pMin, Vector &pMax);
	void multEx(float *r, Matrix &m);
	
};

static Vector UnitVector(1.0);
static Vector NullVector(0.0);
static Vector FwdVector(0, 0, 1);
static Vector LeftVector(1, 0, 0);
static Vector UpVector(0, 1, 0);

#include "Transform.h"

#endif