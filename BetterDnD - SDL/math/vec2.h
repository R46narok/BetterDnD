#pragma once

#include<vector>
#include<iostream>
struct vec2
{
	int x, y;

	vec2();
	vec2(float x, float y);

	vec2& Add(const vec2& vec);
	vec2& Subtract(const vec2& vec);
	vec2& Multiply(const vec2& vec);
	vec2& Divide(const vec2& vec);

	friend vec2& operator+(vec2& v1, const vec2& v2);
	friend vec2& operator-(vec2& v1, const vec2& v2);
	friend vec2& operator*(vec2& v1, const vec2& v2);
	friend vec2& operator/(vec2& v1, const vec2& v2);

	vec2& operator+=(const vec2& vec);
	vec2& operator-=(const vec2& vec);
	vec2& operator*=(const vec2& vec);
	vec2& operator/=(const vec2& vec);

	vec2& operator*(const int& i);
	vec2& Zero();

	friend std::ostream& operator<<(std::ostream stream, const vec2& vec);
};