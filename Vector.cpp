#include "Vector.h"

Vector::Vector()  {}
Vector::~Vector() {}

//=============================================================================

Vector::Vector(float x, float y, float z) {this->x = x; this->y = y; this->z = z;}
Vector::Vector(Vector &v)                 {*this = v;}
Vector::Vector(float s)                   {x = s; y = s; z = s;}
Vector::Vector(float *v)                  {memcpy(this->v, v, sizeof(float) * 3);}

//=============================================================================

void Vector::toArray(float *v)
{
	memcpy(v, this->v, sizeof(float) * 3);
}

//=============================================================================

Vector &Vector::operator=(Vector &v)  {x  = v.x; y  = v.y; z  = v.z; return *this;}

Vector &Vector::operator+=(Vector &v) {x += v.x; y += v.y; z += v.z; return *this;}
Vector &Vector::operator-=(Vector &v) {x -= v.x; y -= v.y; z -= v.z; return *this;}
Vector &Vector::operator&=(Vector &v) {x *= v.x; y *= v.y; z *= v.z; return *this;}
Vector &Vector::operator*=(float s)   {x *=   s; y *=   s; z *=   s; return *this;}
Vector &Vector::operator/=(float s)
{
	float r = 1 / s;
	x *= r; y *= r; z *= r;
	return *this;
}
Vector &Vector::operator*=(Vector &v)
{
	return *this = Vector(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
		);
}
Vector &Vector::operator*=(Matrix &m)
{
	return *this = Vector(
		x * m[0][0] + y * m[1][0] + z * m[2][0] + m[3][0],
		x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1],
		x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2]
		);
}

Vector Vector::operator+(Vector &v) {return Vector(*this) += v;}
Vector Vector::operator-(Vector &v) {return Vector(*this) -= v;}
Vector Vector::operator&(Vector &v) {return Vector(*this) &= v;}
Vector Vector::operator*(float s)   {return Vector(*this) *= s;}
Vector Vector::operator/(float s)   {return Vector(*this) /= s;}
Vector Vector::operator*(Vector &v) {return Vector(*this) *= v;}
Vector Vector::operator*(Matrix &m) {return Vector(*this) *= m;}

float  &Vector::operator[](AXIS::AXIS axis) {return v[axis];}
float  Vector::operator|(Vector &v)         {return x * v.x + y * v.y + z * v.z;}
Vector Vector::operator-()                  {return *this * -1;};
bool   Vector::operator==(Vector &v)        {return x == v.x && y == v.y && z == v.z;}
bool   Vector::operator!=(Vector &v)        {return x != v.x || y != v.y || z != v.z;}

//=============================================================================

Vector &Vector::mask(Vector &m, Vector &v)
{
	x = m.x ? v.x : x;
	y = m.y ? v.y : y;
	z = m.z ? v.z : z;
	return *this;
}

Vector Vector::vec_interp(Vector &v, float s)
{
	return interp(*this, v, s);
}

float Vector::mod()
{
	return (float) pow(*this | *this, 0.5f);
}

float Vector::dist(Vector &v)
{
	return (*this - v).mod();
}

Vector &Vector::normalize()
{
	float t = this->mod();
	return *this = (t != 0) ? *this / t : NULL_VECTOR;
}

Vector Vector::normal()
{
	return Vector(*this).normalize();
}

Vector Vector::normTri(Vector &v1, Vector &v2)
{
	return ((v1 - *this) * (v2 - *this)).normalize();
}

float Vector::angle(Vector &v)
{
	return this->normal() | v.normal();
}

int Vector::compare(Vector &v1, Vector &v2)
{
	return sgn((*this | v1) - (*this | v2));
}

float Vector::sectPlane(Vector &p, Vector &v, Vector &n)
{
	float t = n | *this;
	return (t != 0) ? (n | (v - p)) / t : BIG_NUMBER;
}

Vector Vector::project(Vector &v)
{
	Vector t = v.normal();
	return t * (*this | t);
}

Vector Vector::ortho(Vector &v)
{
	return *this - this->project(v);
}

Vector Vector::reflect(Vector &n)
{
	if (this->angle(n) < 0)
		return *this + this->project(n) * -2;
	return *this;
}

Vector &Vector::fromAngle(Vector &v)
{
	return *this =
		FWD_VECTOR * RotateTrans(AXIS::X, v.pitch) * RotateTrans(AXIS::Y, v.yaw);
}

Vector Vector::toAngle()
{
	Vector t(x, 0, z);
	Vector r(
		0,
		acosEx(t.angle(*this)),
		acosEx(t.angle(FWD_VECTOR))
		);
	if (x < 0) r.yaw *= -1;
	if (y > 0) r.pitch *= -1;
	return r;
}

//=============================================================================

Vector &Vector::vec_wrap(Vector &pMin, Vector &pMax)
{
	x = wrap(x, pMin.x, pMax.x);
	y = wrap(y, pMin.y, pMax.y);
	z = wrap(z, pMin.z, pMax.z);
	return *this;
}

Vector &Vector::vec_limit(Vector &pMin, Vector &pMax)
{
	x = limit(x, pMin.x, pMax.x);
	y = limit(y, pMin.y, pMax.y);
	z = limit(z, pMin.z, pMax.z);
	return *this;
}

void Vector::multEx(float *r, Matrix &m)
{
	r[0] = x * m[0][0] + y * m[1][0] + z * m[2][0] + m[3][0];
	r[1] = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
	r[2] = x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2];
	r[3] = x * m[0][3] + y * m[1][3] + z * m[2][3] + m[3][3];
}