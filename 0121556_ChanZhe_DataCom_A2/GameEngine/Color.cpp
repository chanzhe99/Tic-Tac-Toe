#include "Color.h"

Color Color::White	= Color(1, 1, 1, 1);
Color Color::Red	= Color(1, 0, 0, 1);
Color Color::Orange	= Color(1, 0.7, 0, 1);
Color Color::Yellow	= Color(1, 1, 0, 1);
Color Color::Green	= Color(0, 1, 0, 1);
Color Color::Blue	= Color(0, 0, 1, 1);
Color Color::Purple	= Color(0.5, 0, 0.5, 1);

Color::Color()
{
	R = 1.f;
	G = 1.f;
	B = 1.f;
	A = 1.f;
}

Color::Color(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}
