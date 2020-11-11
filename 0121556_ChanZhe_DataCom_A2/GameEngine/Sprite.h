#pragma once
#include <GLFW/glfw3.h>
#include "bitmap.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include "Color.h"
#include "Vector2.h"


//! Enumerator class for Sprite blend mode
enum class BlendMode
{
	Normal = 0,
	Additive,
	Multiply
};

//! Sprite class
class Sprite
{
private:
	unsigned int SpriteWidth;
	unsigned int SpriteHeight;
	unsigned int SpriteTextureID;

public:
	//! Initialises empty Sprite with default values
	Sprite();
	//! Initialises Sprite and loads sprite image from local file directory
	Sprite(const char* File);
	~Sprite();

	//! Returns a Vector2 of the Sprite's size
	Vector2 GetScale() { return Vector2(SpriteWidth, SpriteHeight); }
	//! Draws the Sprite on screen
	void Draw(const Color& DesiredColor, BlendMode DesiredBlendMode);
};