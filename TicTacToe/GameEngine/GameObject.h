#pragma once
#include "Matrix.h"
#include "Vector2.h"
#include "Sprite.h"

//! GameObject class
class GameObject
{
protected:
	Vector2 ObjectPosition;
	float ObjectRotation;
	Vector2 ObjectScale;

	Sprite* ObjectSprite;
	Matrix TransformMatrix, TranslateMatrix, RotateMatrix, ScaleMatrix;
	Color ObjectColor = Color::White;
	BlendMode ObjectBlendMode;

	//! Returns a random float based on the given parameters
	float RandomFloat(float MinRandomValue, float MaxRandomValue)
	{ return ((float)rand() / RAND_MAX) * (MaxRandomValue - MinRandomValue) + MinRandomValue; }

public:
	//! Initialises a GameObject instance with default values
	GameObject();
	//! Initialises a GameObject instance that takes in a Sprite pointer
	GameObject(Sprite* DesiredSprite);
	~GameObject();
	//! Returns a Vector2 of the GameObject's position
	Vector2 GetPosition() { return ObjectPosition; }
	//! Returns a float of the GameObject's rotation in degrees
	float GetRotation() { return ObjectRotation; }
	//! Returns a Vector2 of the GameObject's size
	Vector2 GetScale() { return ObjectScale; }
	//! Returns a Sprite pointer of the GameObject's Sprite
	Sprite* GetSprite() { return ObjectSprite; }
	//! Returns a Color of the GameObject's Color
	Color GetColor() { return ObjectColor; }
	//! Takes in a Vector2 reference and sets the GameObject's position
	void SetPosition(const Vector2& DesiredPosition);
	//! Takes in a float and sets the GameObject's rotation in degrees
	void SetRotation(float DesiredRotation);
	//! Takes in a Vector2 reference and sets the GameObject's size
	void SetScale(const Vector2& DesiredScale);
	//! Takes in a Sprite pointer and sets the GameObject's Sprite
	void SetSprite(Sprite* DesiredSprite) { ObjectSprite = DesiredSprite; }
	//! Takes in a Color reference and sets the GameObject's Color
	void SetColor(const Color& DesiredColor) { ObjectColor = DesiredColor; }
	//! Takes in a BlendMode enum and sets the GameObject's BlendMode
	void SetBlendMode(BlendMode DesiredBlendMode) { ObjectBlendMode = DesiredBlendMode; }

	//! Returns a Vector2 of the GameObject's size in world space (GameObject size * Sprite size)
	Vector2 GetWorldScale();
	//! Returns a boolean if this GameObject overlaps the GameObject referenced in the Other parameter
	bool CheckCollision(GameObject& Other);

	//! Updates the GameObject
	void Update(float DeltaTime);
	//! Draws the GameObject
	void Draw();
};
