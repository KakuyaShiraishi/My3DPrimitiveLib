#ifndef H_MATRIX
#define H_MATRIX

#include <windows.h>
#include <math.h>

#define IDENT_MATRIX IdentMatrix
#define ZERO_MATRIX ZeroMatrix

inline float **buildArray(int rowCnt, int colCnt)
{
	float **r = new float *[rowCnt];
	for (int i = 0; i < rowCnt; i++)
		r[i] = new float[colCnt];
	return r;
}

inline void killArray(float **m, int rowCnt)
{
	for (int i = 0; i < rowCnt; i++)
		delete []m[i];
	delete []m;
}

class Matrix
{
private:
	float mItem[4][4];

	inline void get(float **m);
	inline Matrix &set(float **m);

	inline Matrix &mult(Matrix &m);
	inline Matrix &scale(float s);
	
	inline Matrix mult(Matrix &m1, Matrix &m2);
	inline Matrix scale(Matrix &m, float s);

	static inline void minor(float **r, float **m, int rowCnt, int colCnt, int row, int col);
	static inline float cofact(float **t, float **m, int size, int row, int col);
	static inline float det(float **m, int size);

public:
	Matrix();
	~Matrix();
	
	Matrix(Matrix &m);
	Matrix(float **m);
	Matrix(float s);
	
	void toArray(float *m);
	
	Matrix &operator=(Matrix &m);
	Matrix operator~();
	
	Matrix &operator*=(Matrix &m);
	Matrix &operator*=(float s);
	Matrix &operator/=(float s);
	
	Matrix operator*(Matrix &m);
	Matrix operator*(float s);
	Matrix operator/(float s);
	
	float *operator[](int row);
	Matrix operator!();
	
	Matrix &invert();
	Matrix inverse();
	
};

static Matrix IdentMatrix(1.0);
static Matrix ZeroMatrix(0.0);

#endif