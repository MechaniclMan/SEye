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
#include "scripts.h"
#include "engine_common.h"
#include "engine_math.h"
#ifdef WIN32
#include <xmmintrin.h> //SSE Intrinsics, win32
#endif
_Vector3MathFunctions* Vector3Math;
_Vector4MathFunctions* Vector4Math;

void InitEngineMath()
{
	Vector3Math = new _Vector3MathFunctions();
#ifdef WIN32
	if ((HasSSE) && (*HasSSE))
	{
		//DO NOT USE _Vector3MathFunctionsSSE, NOT FULLY OPERATIONAL YET
		//Vector3Math = new _Vector3MathFunctionsSSE();
		Vector4Math = new _Vector4MathFunctionsSSE();
	}
	else
#endif
	{
		//Vector3Math = new _Vector3MathFunctions();
		Vector4Math = new _Vector4MathFunctions();
	}
}

void DestroyEngineMath()
{
	delete Vector3Math;
	delete Vector4Math;
}

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}
Vector2::Vector2()
{
	Vector2::Vector2(0,0);
}
Vector2& Vector2::operator *= (Vector2& v)
{
	this->X *= v.X;
	this->Y *= v.Y;
	return *this;
}
Vector2& Vector2::operator /= (Vector2& v)
{
	this->X /= v.X;
	this->Y /= v.Y;
	return *this;
}
Vector2& Vector2::operator += (Vector2& v)
{
	this->X += v.X;
	this->Y += v.Y;
	return *this;
}
Vector2& Vector2::operator -= (Vector2& v)
{
	this->X -= v.X;
	this->Y -= v.Y;
	return *this;
}
Vector2& Vector2::operator *= (float f)
{
	this->X *= f;
	this->Y *= f;
	return *this;
}
Vector2& Vector2::operator /= (float f)
{
	this->X /= f;
	this->Y /= f;
	return *this;
}
Vector2 Vector2::operator * (const Vector2& v) const
{
	return Vector2(this->X * v.X,this->Y * v.Y);
}
Vector2 Vector2::operator / (const Vector2& v) const
{
	return Vector2(this->X / v.X,this->Y / v.Y);
}
Vector2 Vector2::operator + (const Vector2& v) const
{
	return Vector2(this->X + v.X,this->Y + v.Y);
}
Vector2 Vector2::operator - (const Vector2& v) const
{
	return Vector2(this->X - v.X,this->Y - v.Y);
}
Vector2 Vector2::operator * (float f) const
{
	return Vector2(this->X * f,this->Y * f);
}
Vector2 Vector2::operator / (float f) const
{
	return Vector2(this->X / f,this->Y / f);
}

Vector3::Vector3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}
Vector3& Vector3::operator *= (Vector3& v)
{
 	Vector3Math->Multiply(this,&v,this);
	return *this;
}
Vector3& Vector3::operator /= (Vector3& v)
{
	Vector3Math->Divide(this,&v,this);
	return *this;
}
Vector3& Vector3::operator += (Vector3& v)
{
	Vector3Math->Add(this,&v,this);
	return *this;
}
Vector3& Vector3::operator -= (Vector3& v)
{
	Vector3Math->Subtract(this,&v,this);
	return *this;
}
Vector3& Vector3::operator *= (float f)
{
	Vector3Math->Multiply(this,&f,this);
	return *this;
}
Vector3& Vector3::operator /= (float f)
{
 	Vector3Math->Divide(this,&f,this);
	return *this;
}
Vector3 Vector3::operator * (const Vector3& v) const
{
	return Vector3Math->Multiply((Vector3*)this,(Vector3*)&v);
}
Vector3 Vector3::operator / (const Vector3& v) const
{
	return Vector3Math->Divide((Vector3*)this,(Vector3*)&v);	
}
Vector3 Vector3::operator + (const Vector3& v) const
{
	return Vector3Math->Add((Vector3*)this,(Vector3*)&v);
}
Vector3 Vector3::operator - (const Vector3& v) const
{
	return Vector3Math->Subtract((Vector3*)this,(Vector3*)&v);
}
Vector3 Vector3::operator * (float f) const
{
	return Vector3Math->Multiply((Vector3*)this,&f);
}
Vector3 Vector3::operator / (float f) const
{
	return Vector3Math->Divide((Vector3*)this,&f);
}
void Vector3::Normalize()
{
	Vector3Math->Normalize(this);
}
Vector3 Vector3::Normalize(Vector3 v)
{
	Vector3 temp;
	Vector3Math->Normalize(&v,&temp);
	return temp;
}
float Vector3::Dot(Vector3 v)
{
	return Vector3Math->Dot(this, &v);
}
float Vector3::Dot(Vector3 v,Vector3 v2)
{
	return Vector3Math->Dot(&v, &v2);
}
Vector3 Vector3::Cross(Vector3 v)
{
	return Vector3Math->Cross(this, &v);
}
Vector3 Vector3::Cross(Vector3 v,Vector3 v2)
{
	return Vector3Math->Cross(&v, &v2);
}

void _Vector3MathFunctions::Add(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	*dest = Vector3(src1->X + src2->X,src1->Y + src2->Y,src1->Z + src2->Z);
}
void _Vector3MathFunctions::Subtract(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	*dest = Vector3(src1->X - src2->X,src1->Y - src2->Y,src1->Z - src2->Z);
}
void _Vector3MathFunctions::Multiply(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	*dest = Vector3(src1->X * src2->X,src1->Y * src2->Y,src1->Z * src2->Z);
}
void _Vector3MathFunctions::Divide(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	*dest = Vector3(src1->X / src2->X,src1->Y / src2->Y,src1->Z / src2->Z);
}
void _Vector3MathFunctions::Multiply(Vector3 *src1, float *src2, Vector3 *dest)
{
	*dest = Vector3(src1->X * *src2,src1->Y * *src2,src1->Z * *src2);
}
void _Vector3MathFunctions::Divide(Vector3 *src1, float *src2, Vector3 *dest)
{
 	*dest = Vector3(src1->X / *src2,src1->Y / *src2,src1->Z / *src2);
}
void _Vector3MathFunctions::Cross(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	*dest = Vector3(src1->X * src2->Z - src1->Z * src2->Y,src1->Z * src2->X - src1->X * src2->Z,src1->X * src2->Y - src1->Y * src2->Z);
}
void _Vector3MathFunctions::Normalize(Vector3 *src1, Vector3 *dest)
{
 	float magnitude = src1->X * src1->X + src1->Y * src1->Y + src1->Z * src1->Z;
	if (!magnitude)
	{
		*dest = Vector3();
	}
	float multiply = 1.0f / sqrt(magnitude);
	*dest = Vector3(src1->X * multiply,src1->Y * multiply,src1->Z * multiply);
}
void _Vector3MathFunctions::Dot(Vector3 *src1,Vector3 *src2,float *dest)
{
	*dest = (src1->X * src2->X) + (src1->Y * src2->Y) + (src1->Z * src2->Z);
}
Vector3 _Vector3MathFunctions::Add(Vector3* src1, Vector3* src2)
{
	Vector3 temp;
	this->Add(src1,src2,&temp);
	return temp;
}
Vector3 _Vector3MathFunctions::Subtract(Vector3* src1, Vector3* src2)
{
 	Vector3 temp;
	this->Subtract(src1,src2,&temp);
	return temp;
}
Vector3 _Vector3MathFunctions::Multiply(Vector3* src1, Vector3* src2)
{
 	Vector3 temp;
	this->Multiply(src1,src2,&temp);
	return temp;
}
Vector3 _Vector3MathFunctions::Divide(Vector3* src1, Vector3* src2)
{
 	Vector3 temp;
	this->Divide(src1,src2,&temp);
	return temp;
}
Vector3 _Vector3MathFunctions::Multiply(Vector3* src1, float* src2)
{
 	Vector3 temp;
	this->Multiply(src1,src2,&temp);
	return temp;
}
Vector3 _Vector3MathFunctions::Divide(Vector3* src1, float* src2)
{
 	Vector3 temp;
	this->Divide(src1,src2,&temp);
	return temp;
}
Vector3 _Vector3MathFunctions::Cross(Vector3* src1, Vector3* src2)
{
 	Vector3 temp;
	this->Cross(src1,src2,&temp);
	return temp;
}
Vector3 _Vector3MathFunctions::Normalize(Vector3* src)
{
 	Vector3 temp;
	this->Normalize(src,&temp);
	return temp;
}
float _Vector3MathFunctions::Dot(Vector3* src1, Vector3* src2)
{
	float temp;
	this->Dot(src1,src2,&temp);
	return temp;
}
/*
//DO NOT USE _Vector3MathFunctionsSSE, NOT FULLY OPERATIONAL YET
#ifdef WIN32
void _Vector3MathFunctionsSSE::Add(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	__m128 a = _mm_set_ps(src1->X,src1->Y,src1->Z,0.0f);
	__m128 b = _mm_set_ps(src2->X,src2->Y,src2->Z,0.0f);
	__m128 res = _mm_add_ps(a,b);
	memcpy(dest,&res,sizeof(Vector3));
}
void _Vector3MathFunctionsSSE::Subtract(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	__m128 a = _mm_set_ps(src1->X,src1->Y,src1->Z,0.0f);
	__m128 b = _mm_set_ps(src2->X,src2->Y,src2->Z,0.0f);
	__m128 res = _mm_sub_ps(a,b);
	memcpy(dest,&res,sizeof(Vector3));
}
void _Vector3MathFunctionsSSE::Multiply(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	__m128 a = _mm_set_ps(src1->X,src1->Y,src1->Z,0.0f);
	__m128 b = _mm_set_ps(src2->X,src2->Y,src2->Z,0.0f);
	__m128 res = _mm_mul_ps(a,b);
	memcpy(dest,&res,sizeof(Vector3));
}
void _Vector3MathFunctionsSSE::Divide(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	__m128 a = _mm_set_ps(src1->X,src1->Y,src1->Z,0.0f);
	__m128 b = _mm_set_ps(src2->X,src2->Y,src2->Z,1.0f);
	__m128 res = _mm_div_ps(a,b);
	memcpy(dest,&res,sizeof(Vector3));
}
void _Vector3MathFunctionsSSE::Multiply(Vector3 *src1, float *src2, Vector3 *dest)
{
	__m128 a = _mm_set_ps(src1->X,src1->Y,src1->Z,0.0f);
	__m128 b = _mm_set_ps(*src2,*src2,*src2,0.0f);
	__m128 res = _mm_mul_ps(a,b);
	memcpy(dest,&res,sizeof(Vector3));
}
void _Vector3MathFunctionsSSE::Divide(Vector3 *src1, float *src2, Vector3 *dest)
{
	__m128 a = _mm_set_ps(src1->X,src1->Y,src1->Z,0.0f);
	__m128 b = _mm_set_ps(*src2,*src2,*src2,1.0f);
	__m128 res = _mm_div_ps(a,b);
	memcpy(dest,&res,sizeof(Vector3));
}
void _Vector3MathFunctionsSSE::Cross(Vector3 *src1, Vector3 *src2, Vector3 *dest)
{
	__m128 a = _mm_set_ps(src1->X,src1->Z,src1->Z,src1->X);
	__m128 b = _mm_set_ps(src2->Z,src2->Y,src2->X,src2->Y);
	__m128 c = _mm_set_ps(src1->X,0,0,0);
	__m128 d = _mm_set_ps(src1->Y,0,0,0);
	__m128 res = _mm_mul_ps(a,b);
	__m128 res2 = _mm_mul_ss(c,d);
	float res1f[4];
	float res2f[4];
	memcpy(res1f,&res,16);
	memcpy(res2f,&res2,16);
	a = _mm_set_ps(res1f[0],res1f[2],res1f[3],0.0f);
	b = _mm_set_ps(res1f[1],res1f[0],res2f[0],0.0f);
	__m128 dst = _mm_sub_ps(a,b);
	memcpy(dest,&dst,sizeof(Vector3));
}
void _Vector3MathFunctionsSSE::Normalize(Vector3 *src1, Vector3 *dest)
{
 	float magnitude = src1->X * src1->X + src1->Y * src1->Y + src1->Z * src1->Z;
	if (!magnitude)
	{
		*dest = Vector3();
	}
	float multiply = rsqrtSSE(magnitude);
	return this->Multiply(src1,&multiply,dest);
}
#endif
*/
Vector4::Vector4(float x,float y, float z, float w) 
{
	X = x;
	Y = y;
	Z = z;
	W = w;
};
Vector4 Vector4::FromVector2(Vector2 source)
{
	return Vector4(source.X,source.Y,0,0);
}
Vector4 *Vector4::FromVector2(Vector2 *source)
{
	return new Vector4(source->X,source->Y,0,0);
}
Vector4 Vector4::FromVector3(Vector3 source)
{
	return Vector4(source.X,source.Y,source.Z,0);
}
Vector4 *Vector4::FromVector3(Vector3 *source)
{
	return new Vector4(source->X,source->Y,source->Z,0);
}
Vector4& Vector4::operator *= (Vector4& v)
{
	Vector4Math->Multiply(this,&v,this);
	return *this;
}
Vector4& Vector4::operator /= (Vector4& v)
{
	Vector4Math->Divide(this,&v,this);
	return *this;
}
Vector4& Vector4::operator += (Vector4& v)
{
	Vector4Math->Add(this,&v,this);
	return *this;
}
Vector4& Vector4::operator -= (Vector4& v)
{
	Vector4Math->Add(this,&v,this);
	return *this;
}
Vector4& Vector4::operator *= (float f)
{
	Vector4Math->Multiply(this,&f,this);
	return *this;
}
Vector4& Vector4::operator /= (float f)
{
	Vector4Math->Divide(this,&f,this);
	return *this;
}
Vector4 Vector4::operator * (const Vector4& v) const
{
	return Vector4Math->Multiply((Vector4*)this,(Vector4*)&v);
}
Vector4 Vector4::operator / (const Vector4& v) const
{
	return Vector4Math->Divide((Vector4*)this,(Vector4*)&v);
}
Vector4 Vector4::operator + (const Vector4& v) const
{
	return Vector4Math->Add((Vector4*)this,(Vector4*)&v);
}
Vector4 Vector4::operator - (const Vector4& v) const
{
	return Vector4Math->Subtract((Vector4*)this,(Vector4*)&v);
}
Vector4 Vector4::operator * (float f) const
{
	return Vector4Math->Multiply((Vector4*)this,&f);
}
Vector4 Vector4::operator / (float f) const
{
	return Vector4Math->Divide((Vector4*)this,&f);
}
Vector4 Vector4::Inverse()
{
	return *this * -1;
}

void _Vector4MathFunctions::Add(Vector4* src1, Vector4* src2, Vector4* dest)
{
	*dest = Vector4(src1->X - src2->X,src1->Y - src2->Y,src1->Z - src2->Z,src1->W - src2->W);
}
void _Vector4MathFunctions::Subtract(Vector4* src1, Vector4* src2, Vector4* dest)
{
	*dest = Vector4(src1->X - src2->X,src1->Y - src2->Y,src1->Z - src2->Z,src1->W - src2->W);
}
void _Vector4MathFunctions::Multiply(Vector4* src1, Vector4* src2, Vector4* dest)
{
	*dest = Vector4(src1->X * src2->X,src1->Y * src2->Y,src1->Z * src2->Z,src1->W * src2->W);
}
void _Vector4MathFunctions::Divide(Vector4* src1, Vector4* src2, Vector4* dest)
{
	*dest = Vector4(src1->X / src2->X,src1->Y / src2->Y,src1->Z / src2->Z,src1->W / src2->W);
}
void _Vector4MathFunctions::Multiply(Vector4* src1, float* src2, Vector4* dest)
{
	*dest = Vector4(src1->X * *src2,src1->Y * *src2,src1->Z * *src2,src1->W * *src2);
}
void _Vector4MathFunctions::Divide(Vector4* src1, float* src2, Vector4* dest)
{
	*dest = Vector4(src1->X / *src2,src1->Y / *src2,src1->Z / *src2,src1->W / *src2);
}

Vector4 _Vector4MathFunctions::Add(Vector4* src1, Vector4* src2)
{
	Vector4 temp;
	this->Add(src1,src2,&temp);
	return temp;
}
Vector4 _Vector4MathFunctions::Subtract(Vector4* src1, Vector4* src2)
{
	Vector4 temp;
	this->Subtract(src1,src2,&temp);
	return temp;
}
Vector4 _Vector4MathFunctions::Multiply(Vector4* src1, Vector4* src2)
{
	Vector4 temp;
	this->Multiply(src1,src2,&temp);
	return temp;
}
Vector4 _Vector4MathFunctions::Divide(Vector4* src1, Vector4* src2)
{
	Vector4 temp;
	this->Divide(src1,src2,&temp);
	return temp;
}
Vector4 _Vector4MathFunctions::Multiply(Vector4* src1, float* src2)
{
	Vector4 temp;
	this->Multiply(src1,src2,&temp);
	return temp;
}
Vector4 _Vector4MathFunctions::Divide(Vector4* src1, float* src2)
{
	Vector4 temp;
	this->Divide(src1,src2,&temp);
	return temp;
}

#ifdef WIN32
void _Vector4MathFunctionsSSE::Add(Vector4* src1, Vector4* src2, Vector4* dest)
{
	__m128 a = _mm_loadu_ps((float*)src1);
	__m128 b = _mm_loadu_ps((float*)src2);
	__m128 res = _mm_add_ps(a,b);
	_mm_storeu_ps((float*)dest,res);
}
void _Vector4MathFunctionsSSE::Subtract(Vector4* src1, Vector4* src2, Vector4* dest)
{
	__m128 a = _mm_loadu_ps((float*)src1);
	__m128 b = _mm_loadu_ps((float*)src2);
	__m128 res = _mm_sub_ps(a,b);
	_mm_storeu_ps((float*)dest,res);
}
void _Vector4MathFunctionsSSE::Multiply(Vector4* src1, Vector4* src2, Vector4* dest)
{
	__m128 a = _mm_loadu_ps((float*)src1);
	__m128 b = _mm_loadu_ps((float*)src2);
	__m128 res = _mm_mul_ps(a,b);
	_mm_storeu_ps((float*)dest,res);
}
void _Vector4MathFunctionsSSE::Divide(Vector4* src1, Vector4* src2, Vector4* dest)
{
	__m128 a = _mm_loadu_ps((float*)src1);
	__m128 b = _mm_loadu_ps((float*)src2);
	__m128 res = _mm_div_ps(a,b);
	_mm_storeu_ps((float*)dest,res);
}
void _Vector4MathFunctionsSSE::Multiply(Vector4* src1, float *src2, Vector4* dest)
{
	__m128 a = _mm_loadu_ps((float*)src1);
	__m128 b = _mm_load_ps1((float*)src2);
	__m128 res = _mm_mul_ps(a,b);
	_mm_storeu_ps((float*)dest,res);
}
void _Vector4MathFunctionsSSE::Divide(Vector4* src1, float *src2, Vector4* dest)
{
	__m128 a = _mm_loadu_ps((float*)src1);
	__m128 b = _mm_load_ps1((float*)src2);
	__m128 res = _mm_mul_ps(a,b);
	_mm_storeu_ps((float*)dest,res);
}
#endif

Matrix4::Matrix4()
{
	this->Row[0] = Vector4(0,0,0,0);
	this->Row[1] = Vector4(0,0,0,0);
	this->Row[2] = Vector4(0,0,0,0);
	this->Row[3] = Vector4(0,0,0,0);
}
Matrix4& Matrix4::operator *= (Matrix4& m)
{
	return *this;
}

Matrix4& Matrix4::operator += (Matrix4& m)
{
	this->Row[0] += m.Row[0];
	this->Row[1] += m.Row[1];
	this->Row[2] += m.Row[2];
	this->Row[3] += m.Row[3];
	return *this;
}
Matrix4& Matrix4::operator -= (Matrix4& m)
{
	this->Row[0] -= m.Row[0];
	this->Row[1] -= m.Row[1];
	this->Row[2] -= m.Row[2];
	this->Row[3] -= m.Row[3];
	return *this;
}
Matrix4& Matrix4::operator *= (float f)
{
	this->Row[0] *= f;
	this->Row[1] *= f;
	this->Row[2] *= f;
	this->Row[3] *= f;
	return *this;
}
Matrix4& Matrix4::operator /= (float f)
{
	this->Row[0] /= f;
	this->Row[1] /= f;
	this->Row[2] /= f;
	this->Row[3] /= f;
	return *this;
}

Matrix4 Matrix4::operator + (const Matrix4& m) const
{
	Matrix4 t;
	t.Row[0] = this->Row[0] + m.Row[0];
	t.Row[1] = this->Row[1] + m.Row[1];
	t.Row[2] = this->Row[2] + m.Row[2];
	t.Row[3] = this->Row[3] + m.Row[3];
	return t;
}
Matrix4 Matrix4::operator - (const Matrix4& m) const
{
	Matrix4 t;
	t.Row[0] = this->Row[0] - m.Row[0];
	t.Row[1] = this->Row[1] - m.Row[1];
	t.Row[2] = this->Row[2] - m.Row[2];
	t.Row[3] = this->Row[3] - m.Row[3];
	return t;
}
Matrix4 Matrix4::operator * (const Matrix4& m) const
{
	Matrix4 temp;
	temp.Row[0].X = this->Row[0].X * m.Row[0].X + this->Row[0].Y * m.Row[1].X + this->Row[0].Z * m.Row[2].X + this->Row[0].W * m.Row[3].X;
	temp.Row[0].Y = this->Row[0].X * m.Row[0].Y + this->Row[0].Y * m.Row[1].Y + this->Row[0].Z * m.Row[2].Y + this->Row[0].W * m.Row[3].Y;
	temp.Row[0].Z = this->Row[0].X * m.Row[0].Z + this->Row[0].Y * m.Row[1].Z + this->Row[0].Z * m.Row[2].Z + this->Row[0].W * m.Row[3].Z;
	temp.Row[0].W = this->Row[0].X * m.Row[0].W + this->Row[0].Y * m.Row[1].W + this->Row[0].Z * m.Row[2].W + this->Row[0].W * m.Row[3].W;
	temp.Row[1].X = this->Row[1].X * m.Row[0].X + this->Row[1].Y * m.Row[1].X + this->Row[1].Z * m.Row[2].X + this->Row[1].W * m.Row[3].X;
	temp.Row[1].Y = this->Row[1].X * m.Row[0].Y + this->Row[1].Y * m.Row[1].Y + this->Row[1].Z * m.Row[2].Y + this->Row[1].W * m.Row[3].Y;
	temp.Row[1].Z = this->Row[1].X * m.Row[0].Z + this->Row[1].Y * m.Row[1].Z + this->Row[1].Z * m.Row[2].Z + this->Row[1].W * m.Row[3].Z;
	temp.Row[1].W = this->Row[1].X * m.Row[0].W + this->Row[1].Y * m.Row[1].W + this->Row[1].Z * m.Row[2].W + this->Row[1].W * m.Row[3].W;
	temp.Row[2].X = this->Row[2].X * m.Row[0].X + this->Row[2].Y * m.Row[1].X + this->Row[2].Z * m.Row[2].X + this->Row[2].W * m.Row[3].X;
	temp.Row[2].Y = this->Row[2].X * m.Row[0].Y + this->Row[2].Y * m.Row[1].Y + this->Row[2].Z * m.Row[2].Y + this->Row[2].W * m.Row[3].Y;
	temp.Row[2].Z = this->Row[2].X * m.Row[0].Z + this->Row[2].Y * m.Row[1].Z + this->Row[2].Z * m.Row[2].Z + this->Row[2].W * m.Row[3].Z;
	temp.Row[2].W = this->Row[2].X * m.Row[0].W + this->Row[2].Y * m.Row[1].W + this->Row[2].Z * m.Row[2].W + this->Row[2].W * m.Row[3].W;
	temp.Row[3].X = this->Row[3].X * m.Row[0].X + this->Row[3].Y * m.Row[1].X + this->Row[3].Z * m.Row[2].X + this->Row[3].W * m.Row[3].X;
	temp.Row[3].Y = this->Row[3].X * m.Row[0].Y + this->Row[3].Y * m.Row[1].Y + this->Row[3].Z * m.Row[2].Y + this->Row[3].W * m.Row[3].Y;
	temp.Row[3].Z = this->Row[3].X * m.Row[0].Z + this->Row[3].Y * m.Row[1].Z + this->Row[3].Z * m.Row[2].Z + this->Row[3].W * m.Row[3].Z;
	temp.Row[3].W = this->Row[3].X * m.Row[0].W + this->Row[3].Y * m.Row[1].W + this->Row[3].Z * m.Row[2].W + this->Row[3].W * m.Row[3].W;
	return temp;
}
Matrix4 Matrix4::operator * (float f) const
{
	Matrix4 t;
	t.Row[0] = this->Row[0] * f;
	t.Row[1] = this->Row[1] * f;
	t.Row[2] = this->Row[2] * f;
	t.Row[3] = this->Row[3] * f;
	return t;
}
Matrix4 Matrix4::operator / (float f) const
{
	Matrix4 t;
	t.Row[0] = this->Row[0] / f;
	t.Row[1] = this->Row[1] / f;
	t.Row[2] = this->Row[2] / f;
	t.Row[3] = this->Row[3] / f;
	return t;
}

float Matrix4::Determinant()
{
	float det;
	det =	(Row[0].X * Row[1].Y - Row[0].Y * Row[1].X) * (Row[2].Z * Row[3].W - Row[2].W * Row[3].Z);
	det -=	(Row[0].X * Row[1].Z - Row[0].Z * Row[1].X) * (Row[2].Y * Row[3].W - Row[2].W * Row[3].Y);
	det +=	(Row[0].X * Row[1].W - Row[0].W * Row[1].X) * (Row[2].Y * Row[3].Z - Row[2].Z * Row[3].Y);
	det +=	(Row[0].Y * Row[1].Z - Row[0].Z * Row[1].Y) * (Row[2].X * Row[3].W - Row[2].W * Row[3].X);
	det -=	(Row[0].Y * Row[1].W - Row[0].W * Row[1].Y) * (Row[2].X * Row[3].Z - Row[2].Z * Row[3].X);
	det +=	(Row[0].Z * Row[1].W - Row[0].W * Row[1].Z) * (Row[2].X * Row[3].Y - Row[2].Y * Row[3].X);
	return det;
}
Matrix4 Matrix4::Inverse()
{
	float s = Determinant();
	if (s == 0.0) return Matrix4();
	s = 1/s;
	Matrix4 t;
	t.Row[0].X = s*(Row[1].Y*(Row[2].Z*Row[3].W - Row[2].W*Row[3].Z) + Row[1].Z*(Row[2].W*Row[3].Y - Row[2].Y*Row[3].W) + Row[1].W*(Row[2].Y*Row[3].Z - Row[2].Z*Row[3].Y));
	t.Row[0].Y = s*(Row[2].Y*(Row[0].Z*Row[3].W - Row[0].W*Row[3].Z) + Row[2].Z*(Row[0].W*Row[3].Y - Row[0].Y*Row[3].W) + Row[2].W*(Row[0].Y*Row[3].Z - Row[0].Z*Row[3].Y));
	t.Row[0].Z = s*(Row[3].Y*(Row[0].Z*Row[1].W - Row[0].W*Row[1].Z) + Row[3].Z*(Row[0].W*Row[1].Y - Row[0].Y*Row[1].W) + Row[3].W*(Row[0].Y*Row[1].Z - Row[0].Z*Row[1].Y));
	t.Row[0].W = s*(Row[0].Y*(Row[1].W*Row[2].Z - Row[1].Z*Row[2].W) + Row[0].Z*(Row[1].Y*Row[2].W - Row[1].W*Row[2].Y) + Row[0].W*(Row[1].Z*Row[2].Y - Row[1].Y*Row[2].Z));
	t.Row[1].X = s*(Row[1].Z*(Row[2].X*Row[3].W - Row[2].W*Row[3].X) + Row[1].W*(Row[2].Z*Row[3].X - Row[2].X*Row[3].Z) + Row[1].X*(Row[2].W*Row[3].Z - Row[2].Z*Row[3].W));
	t.Row[1].Y = s*(Row[2].Z*(Row[0].X*Row[3].W - Row[0].W*Row[3].X) + Row[2].W*(Row[0].Z*Row[3].X - Row[0].X*Row[3].Z) + Row[2].X*(Row[0].W*Row[3].Z - Row[0].Z*Row[3].W));
	t.Row[1].Z = s*(Row[3].Z*(Row[0].X*Row[1].W - Row[0].W*Row[1].X) + Row[3].W*(Row[0].Z*Row[1].X - Row[0].X*Row[1].Z) + Row[3].X*(Row[0].W*Row[1].Z - Row[0].Z*Row[1].W));
	t.Row[1].W = s*(Row[0].Z*(Row[1].W*Row[2].X - Row[1].X*Row[2].W) + Row[0].W*(Row[1].X*Row[2].Z - Row[1].Z*Row[2].X) + Row[0].X*(Row[1].Z*Row[2].W - Row[1].W*Row[2].Z));
	t.Row[2].X = s*(Row[1].W*(Row[2].X*Row[3].Y - Row[2].Y*Row[3].X) + Row[1].X*(Row[2].Y*Row[3].W - Row[2].W*Row[3].Y) + Row[1].Y*(Row[2].W*Row[3].X - Row[2].X*Row[3].W));
	t.Row[2].Y = s*(Row[2].W*(Row[0].X*Row[3].Y - Row[0].Y*Row[3].X) + Row[2].X*(Row[0].Y*Row[3].W - Row[0].W*Row[3].Y) + Row[2].Y*(Row[0].W*Row[3].X - Row[0].X*Row[3].W));
	t.Row[2].Z = s*(Row[3].W*(Row[0].X*Row[1].Y - Row[0].Y*Row[1].X) + Row[3].X*(Row[0].Y*Row[1].W - Row[0].W*Row[1].Y) + Row[3].Y*(Row[0].W*Row[1].X - Row[0].X*Row[1].W));
	t.Row[2].W = s*(Row[0].W*(Row[1].Y*Row[2].X - Row[1].X*Row[2].Y) + Row[0].X*(Row[1].W*Row[2].Y - Row[1].Y*Row[2].W) + Row[0].Y*(Row[1].X*Row[2].W - Row[1].W*Row[2].X));
	t.Row[3].X = s*(Row[1].X*(Row[2].Z*Row[3].Y - Row[2].Y*Row[3].Z) + Row[1].Y*(Row[2].X*Row[3].Z - Row[2].Z*Row[3].X) + Row[1].Z*(Row[2].Y*Row[3].X - Row[2].X*Row[3].Y));
	t.Row[3].Y = s*(Row[2].X*(Row[0].Z*Row[3].Y - Row[0].Y*Row[3].Z) + Row[2].Y*(Row[0].X*Row[3].Z - Row[0].Z*Row[3].X) + Row[2].Z*(Row[0].Y*Row[3].X - Row[0].X*Row[3].Y));
	t.Row[3].Z = s*(Row[3].X*(Row[0].Z*Row[1].Y - Row[0].Y*Row[1].Z) + Row[3].Y*(Row[0].X*Row[1].Z - Row[0].Z*Row[1].X) + Row[3].Z*(Row[0].Y*Row[1].X - Row[0].X*Row[1].Y));
	t.Row[3].W = s*(Row[0].X*(Row[1].Y*Row[2].Z - Row[1].Z*Row[2].Y) + Row[0].Y*(Row[1].Z*Row[2].X - Row[1].X*Row[2].Z) + Row[0].Z*(Row[1].X*Row[2].Y - Row[1].Y*Row[2].X));
	return t;
}

Matrix2::Matrix2()
{
	Row[0] = Vector2();
	Row[1] = Vector2();
}
Matrix2::Matrix2(Vector2 r1, Vector2 r2)
{
	Row[0] = r1;
	Row[1] = r2;
}
float Matrix2::Determinant()
{
	return (Row[0].X * Row[1].Y) - (Row[0].Y * Row[1].X);
}
Matrix2 Matrix2::Inverse()
{
	float s = Determinant();
	if (s == 0.0f) return Matrix2();
	s = 1/s;
	Matrix2 temp;
	temp.Row[0].X = s * Row[1].Y;
	temp.Row[0].Y = s * (-Row[0].Y);
	temp.Row[1].X = s * (-Row[1].X);
	temp.Row[1].Y = s * Row[0].X;
	return temp;
}
