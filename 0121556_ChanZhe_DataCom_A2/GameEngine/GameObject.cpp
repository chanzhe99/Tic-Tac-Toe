#include "GameObject.h"

GameObject::GameObject()
{
	ObjectPosition = Vector2(0.f, 0.f);
	ObjectRotation = 0.f;
	ObjectScale = Vector2(1.f, 1.f);

	ObjectSprite = new Sprite();

	TranslateMatrix = Matrix::makeTranslationMatrix(ObjectPosition.X, ObjectPosition.Y, 0.f);
	RotateMatrix = Matrix::makeRotateMatrix(ObjectRotation, Vector(0.f, 0.f, 1.f));
	ScaleMatrix = Matrix::makeScaleMatrix(ObjectScale.X, ObjectScale.Y, 0.f);

	// Set the blend mode
	ObjectBlendMode = BlendMode::Normal;
}


GameObject::GameObject(Sprite* DesiredSprite)
{
	ObjectPosition = Vector2(0.f, 0.f);
	ObjectRotation = 0.f;
	ObjectScale = Vector2(1.f, 1.f);

	ObjectSprite = DesiredSprite;

	TranslateMatrix = Matrix::makeTranslationMatrix(ObjectPosition.X, ObjectPosition.Y, 0.f);
	RotateMatrix = Matrix::makeRotateMatrix(ObjectRotation, Vector(0.f, 0.f, 1.f));
	ScaleMatrix = Matrix::makeScaleMatrix(ObjectScale.X, ObjectScale.Y, 0.f);

	// Set the blend mode
	ObjectBlendMode = BlendMode::Normal;
}


GameObject::~GameObject()
{
}

void GameObject::SetPosition(const Vector2& DesiredPosition)
{
	ObjectPosition = DesiredPosition;
	TranslateMatrix = Matrix::makeTranslationMatrix(ObjectPosition.X, ObjectPosition.Y, 0.f);
}

void GameObject::SetRotation(float DesiredRotation)
{
	ObjectRotation = DesiredRotation;
	RotateMatrix = Matrix::makeRotateMatrix(ObjectRotation, Vector(0.f, 0.f, 1.f));
}

void GameObject::SetScale(const Vector2& DesiredScale)
{
	ObjectScale = DesiredScale;
	ScaleMatrix = Matrix::makeScaleMatrix(ObjectScale.X, ObjectScale.Y, 0.f);
}

Vector2 GameObject::GetWorldScale()
{
	Vector2 WorldScale;
	WorldScale.X = ObjectScale.X * ObjectSprite->GetScale().X;
	WorldScale.Y = ObjectScale.Y * ObjectSprite->GetScale().Y;

	return WorldScale;
}

bool GameObject::CheckCollision(GameObject& Other)
{
	// Colliding X-axis?
	bool CollisionX =
		this->GetPosition().X + (this->GetWorldScale().X / 2) >= Other.GetPosition().X - (Other.GetWorldScale().X / 2) &&
		Other.GetPosition().X + (Other.GetWorldScale().X / 2) >= this->GetPosition().X - (this->GetWorldScale().X / 2);

	// Colliding Y-axis?
	bool CollisionY =
		this->GetPosition().Y + (this->GetWorldScale().Y / 2) >= Other.GetPosition().Y - (Other.GetWorldScale().Y / 2) &&
		Other.GetPosition().Y + (Other.GetWorldScale().Y / 2) >= this->GetPosition().Y - (this->GetWorldScale().Y / 2);

	// Return true if both X and Y collide
	return CollisionX && CollisionY;
}

void GameObject::Update(float DeltaTime)
{
}

void GameObject::Draw()
{
	TransformMatrix = TranslateMatrix * RotateMatrix * ScaleMatrix;
	glLoadMatrixf((GLfloat*)TransformMatrix.mVal);
	
	ObjectSprite->Draw(ObjectColor, ObjectBlendMode);
}
