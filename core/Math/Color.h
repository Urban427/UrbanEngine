#pragma once
#include "Vector4.h"

class Color
{
public:
	Color() : r(0), g(0), b(0), a(0xFF) {};
	Color(char light) : r(light), g(light), b(light), a(0xFF) {};
	Color(char r, char g, char b) : r(r), g(g), b(b), a(0xFF) {};
	Color(int r, int g, int b) : r(r), g(g), b(b), a(0xFF) {};
	Color(float r, float g, float b) : a(0xFF)
	{
		this->r = static_cast<unsigned char>(r * 255.0f);
		this->g = static_cast<unsigned char>(g * 255.0f);
		this->b = static_cast<unsigned char>(b * 255.0f);
	};
	Color(double r, double g, double b) : a(0xFF)
	{
		this->r = static_cast<unsigned char>(r * 255.0f);
		this->g = static_cast<unsigned char>(g * 255.0f);
		this->b = static_cast<unsigned char>(b * 255.0f);
	};
	Color(char r, char g, char b, char a) : r(r), g(g), b(b), a(a) {};

	inline Vector4 ToVector4() const {
		constexpr float inv = 1.0f / 255.0f;
		return {r * inv, g * inv, b * inv, a * inv};
	}

	inline unsigned char& operator[](int index) {
		switch(index) {
			case(0): {
				return r;
			}
			case(1): {
				return g;
			}
			case(2): {
				return b;
			}
			case(3): {
				return a;
			}
		}
		return r;
	}

	inline int ToINT() const {
		return ((int)a << 24) | ((int)r << 16) | ((int)g << 8) | b;
	}
public:
	static Color HSV(float h, float s, float v) {
		float r, g, b;

		int i = int(h * 6.0f);
		float f = h * 6.0f - i;
		float p = v * (1.0f - s);
		float q = v * (1.0f - f * s);
		float t = v * (1.0f - (1.0f - f) * s);

		switch (i % 6)
		{
		case 0: r = v; g = t; b = p; break;
		case 1: r = q; g = v; b = p; break;
		case 2: r = p; g = v; b = t; break;
		case 3: r = p; g = q; b = v; break;
		case 4: r = t; g = p; b = v; break;
		case 5: r = v; g = p; b = q; break;
		}
		return Color( uint8_t(r * 255), uint8_t(g * 255), uint8_t(b * 255) );
	}
public:
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 0xFF;
};
