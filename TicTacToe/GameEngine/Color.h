#pragma once

//! Color class
class Color
{
public:
	float R, G, B, A;
	static Color White, Black, Red, Orange, Yellow, Green, Blue, Purple;
	//! Initialises a Color instance and sets the values to White
	Color();
	//! Initialises a Color instance and that takes in RGBA floats
	Color(float r, float g, float b, float a);
};
