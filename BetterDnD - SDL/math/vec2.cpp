#pragma once

#include "vec2.h"

vec2::vec2()
{
	x = 0.0f;
	y = 0.0f;
}

vec2::vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

vec2& vec2::Add(const vec2& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
vec2& vec2::Subtract(const vec2& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
vec2& vec2::Multiply(const vec2& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}
vec2& vec2::Divide(const vec2& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

vec2& operator+(vec2& v1, const vec2& v2)
{
	return v1.Add(v2);
}
vec2& operator-(vec2& v1, const vec2& v2)
{
	return v1.Subtract(v2);
}
vec2& operator*(vec2& v1, const vec2& v2)
{
	return v1.Multiply(v2);
}
vec2& operator/(vec2& v1, const vec2& v2)
{
	return v1.Divide(v2);
}

vec2& vec2::operator+=(const vec2& vec)
{
	return this->Add(vec);
}
vec2& vec2::operator-=(const vec2& vec)
{
	return this->Subtract(vec);
}
vec2& vec2::operator*=(const vec2& vec)
{
	return this->Multiply(vec);
}
vec2& vec2::operator/=(const vec2& vec)
{
	return this->Divide(vec);
}

vec2& vec2::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}
vec2& vec2::Zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}

std::ostream& operator<<(std::ostream stream, const vec2& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}
