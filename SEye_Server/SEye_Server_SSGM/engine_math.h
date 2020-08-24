/*	Renegade Scripts.dll
	Math related classes and engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
void InitEngineMath();
void DestroyEngineMath();

class Vector2 {
public:
	float X;
	float Y;
	Vector2(float x, float y);
	Vector2();
	Vector2& operator *= (Vector2&);
	Vector2& operator /= (Vector2&);
	Vector2& operator += (Vector2&);
	Vector2& operator -= (Vector2&);
	Vector2& operator *= (float);
	Vector2& operator /= (float);
	Vector2 operator * (const Vector2&) const;
	Vector2 operator / (const Vector2&) const;
	Vector2 operator + (const Vector2&) const;
	Vector2 operator - (const Vector2&) const;
	Vector2 operator * (float) const;
	Vector2 operator / (float) const;
};

class _Vector3MathFunctions
{
public:
	virtual void Add(Vector3* src1, Vector3* src2, Vector3* dest);
	virtual void Subtract(Vector3* src1, Vector3* src2, Vector3* dest);
	virtual void Multiply(Vector3* src1, Vector3* src2, Vector3* dest);
	virtual void Divide(Vector3* src1, Vector3* src2, Vector3* dest);
	virtual void Multiply(Vector3* src1, float *src2, Vector3* dest);
	virtual void Divide(Vector3* src1, float *src2, Vector3* dest);
	virtual void Cross(Vector3* src1, Vector3* src2, Vector3* dest);
	virtual void Normalize(Vector3* src1, Vector3* dest);
	virtual void Dot(Vector3* src1, Vector3* src2, float* dest);

	virtual Vector3 Add(Vector3* src1, Vector3* src2);
	virtual Vector3 Subtract(Vector3* src1, Vector3* src2);
	virtual Vector3 Multiply(Vector3* src1, Vector3* src2);
	virtual Vector3 Divide(Vector3* src1, Vector3* src2);
	virtual Vector3 Multiply(Vector3* src1, float* src2);
	virtual Vector3 Divide(Vector3* src1, float* src2);
	virtual Vector3 Cross(Vector3* src1, Vector3* src2);
	virtual Vector3 Normalize(Vector3* src);
	virtual float	Dot(Vector3* src1, Vector3* src2);
};

/* 
//DO NOT USE _Vector3MathFunctionsSSE, NOT FULLY OPERATIONAL YET
#ifdef WIN32
class _Vector3MathFunctionsSSE : public _Vector3MathFunctions
{
public:
	void Add(Vector3* src1, Vector3* src2, Vector3* dest);
	void Subtract(Vector3* src1, Vector3* src2, Vector3* dest);
	void Multiply(Vector3* src1, Vector3* src2, Vector3* dest);
	void Divide(Vector3* src1, Vector3* src2, Vector3* dest);
	void Multiply(Vector3* src1, float *src2, Vector3* dest);
	void Divide(Vector3* src1, float *src2, Vector3* dest);
	void Cross(Vector3* src1, Vector3* src2, Vector3* dest);
	void Normalize(Vector3* src1, Vector3* dest);
};
#endif
*/

struct Vector4 {
	float X;
	float Y;
	float Z;
	float W;
	Vector4(float x = 0.0f,float y = 0.0f, float z = 0.0f, float w = 0.0f);
	static Vector4 FromVector2(Vector2 source);
	static Vector4* FromVector2(Vector2* source);
	static Vector4 FromVector3(Vector3 source);
	static Vector4* FromVector3(Vector3* source);
	Vector4& operator *= (Vector4&);
	Vector4& operator /= (Vector4&);
	Vector4& operator += (Vector4&);
	Vector4& operator -= (Vector4&);
	Vector4& operator *= (float);
	Vector4& operator /= (float);
	Vector4 operator * (const Vector4&) const;
	Vector4 operator / (const Vector4&) const;
	Vector4 operator + (const Vector4&) const;
	Vector4 operator - (const Vector4&) const;
	Vector4 operator * (float) const;
	Vector4 operator / (float) const;
	Vector4 Inverse();
};

class _Vector4MathFunctions
{
public:
	virtual void Add(Vector4* src1, Vector4* src2, Vector4* dest);
	virtual void Subtract(Vector4* src1, Vector4* src2, Vector4* dest);
	virtual void Multiply(Vector4* src1, Vector4* src2, Vector4* dest);
	virtual void Divide(Vector4* src1, Vector4* src2, Vector4* dest);
	virtual void Multiply(Vector4* src1, float *src2, Vector4* dest);
	virtual void Divide(Vector4* src1, float *src2, Vector4* dest);

	virtual Vector4 Add(Vector4* src1, Vector4* src2);
	virtual Vector4 Subtract(Vector4* src1, Vector4* src2);
	virtual Vector4 Multiply(Vector4* src1, Vector4* src2);
	virtual Vector4 Divide(Vector4* src1, Vector4* src2);
	virtual Vector4 Multiply(Vector4* src1, float* src2);
	virtual Vector4 Divide(Vector4* src1, float* src2);
};

#ifdef WIN32
class _Vector4MathFunctionsSSE: public _Vector4MathFunctions
{
public:
	void Add(Vector4* src1, Vector4* src2, Vector4* dest);
	void Subtract(Vector4* src1, Vector4* src2, Vector4* dest);
	void Multiply(Vector4* src1, Vector4* src2, Vector4* dest);
	void Divide(Vector4* src1, Vector4* src2, Vector4* dest);
	void Multiply(Vector4* src1, float *src2, Vector4* dest);
	void Divide(Vector4* src1, float *src2, Vector4* dest);
};
#endif

struct Matrix2
{
	Vector2 Row[2];
	Matrix2();
	Matrix2(Vector2 r1, Vector2 r2);
	float Determinant();
	Matrix2 Inverse();
};

struct Matrix4 {
	Matrix4();
	Vector4 Row[4];
	Matrix4& operator *= (Matrix4&);
	Matrix4& operator += (Matrix4&);
	Matrix4& operator -= (Matrix4&);
	Matrix4& operator *= (float);
	Matrix4& operator /= (float);
	Matrix4 operator + (const Matrix4&) const;
	Matrix4 operator - (const Matrix4&) const;
	Matrix4 operator * (const Matrix4&) const;
	Matrix4 operator * (float) const;
	Matrix4 operator / (float) const;
	float Determinant();
	Matrix4 Inverse();
};



struct Matrix3D {
	Vector4 Row[3];
};

class Vector3i {
public:
	short I;
	short J;
	short K;
};

class RectClass {
public:
	float Left;
	float Top;
	float Right;
	float Bottom;
	RectClass(float NewLeft,float NewTop,float NewRight,float NewBottom)
	{
		Left = NewLeft;
		Top = NewTop;
		Right = NewRight;
		Bottom = NewBottom;
	}
	RectClass()
	{
		Left = 0;
		Right = 0;
		Top = 0;
		Bottom = 0;
	}
	Vector2 Upper_Left()
	{
		return Vector2(Top,Left);
	}
	Vector2 Lower_Right()
	{
		return Vector2(Right,Bottom);
	}
	RectClass& operator*=(float f)
	{
		Left *= f;
		Right *= f;
		Top *= f;
		Bottom *= f;
		return *this;
	}
	RectClass& operator+=(class Vector2& v)
	{
		Left += v.X;
		Top += v.Y;
		Right += v.X;
		Bottom += v.Y;
		return *this;
	}
};

class OBBoxClass {
public:
	float Basis[3][3]; //rotation matrix
	Vector3 Center; //centerpoint
	Vector3 Extent; //size (i.e. how far from the centerpoint in each direction does the box go)
};

inline unsigned long F2DW(float f)
{
	return *((unsigned long*)&f);
}

#ifdef WIN32
inline float rsqrtSSE(float x)
{
	float z;
	_asm
	{
		rsqrtss xmm0, x
		movss z, xmm0 // z ~= 1/sqrt(x) to 0.038%
	}
	return z;
}
#endif
extern bool *HasSSE;
