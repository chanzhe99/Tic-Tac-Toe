#include "GridObject.h"

GridObject::GridObject()
{
	ObjectSprite = new Sprite("../Content/Empty.bmp");
	CrossSprite = new Sprite("../Content/Cross.bmp");
	CircleSprite = new Sprite("../Content/Circle.bmp");

	GridState = EGridState::Empty;
}

GridObject::GridObject(int IndexX, int IndexY)
{
	ObjectSprite = new Sprite("../Content/Empty.bmp");
	CrossSprite = new Sprite("../Content/Cross.bmp");
	CircleSprite = new Sprite("../Content/Circle.bmp");

	GridState = EGridState::Empty;

	GridIndex.X = IndexX;
	GridIndex.Y = IndexY;
}

GridObject::~GridObject()
{
}

bool GridObject::IsMouseOverlapping(GLFWwindow* AppWindow, double MousePosX, double MousePosY)
{
	float Left = GetPosition().X - (GetWorldScale().X / 2);
	float Right = GetPosition().X + (GetWorldScale().X / 2);
	float Top = GetPosition().Y + (GetWorldScale().Y / 2);
	float Bottom = GetPosition().Y - (GetWorldScale().Y / 2);
	
	int WindowY = 0;
	glfwGetWindowSize(AppWindow, nullptr, &WindowY);

	MousePosY = WindowY - MousePosY;

	bool CollisionX = MousePosX >= Left && MousePosX <= Right;
	bool CollisionY = MousePosY >= Bottom && MousePosY <= Top;

	bool Collision = CollisionX && CollisionY;

	if (Collision)
	{
		//std::cout << "Grid (" << GridIndex.X << ", " << GridIndex.Y << ") selected" << std::endl;
		if(GridState == EGridState::Empty)
			GridState = EGridState::Highlighted;
		MouseIsOverlapping = true;
		return true;
	}
	
	if (GridState == EGridState::Highlighted)
		GridState = EGridState::Empty;
	MouseIsOverlapping = false;
	return false;
}

bool GridObject::IsMouseClicked(bool IsCrossing)
{
	if (GridState == EGridState::Highlighted)
	{
		if (IsCrossing)
			GridState = EGridState::Crossed;
		else
			GridState = EGridState::Circled;

		//IsCrossing = !IsCrossing;
		return true;
	}
	return false;
}

void GridObject::Update(float DeltaTime)
{
	
}

void GridObject::Draw()
{
	TransformMatrix = TranslateMatrix * RotateMatrix * ScaleMatrix;
	glLoadMatrixf((GLfloat*)TransformMatrix.mVal);

	switch (GridState)
	{
	case EGridState::Empty:
		ObjectSprite->Draw(Color::White, BlendMode::Normal);
		break;
	case EGridState::Highlighted:
		ObjectSprite->Draw(Color(1, 0.984, 0.651, 1.0), BlendMode::Normal);
		break;
	case EGridState::Crossed:
		CrossSprite->Draw(Color::White, BlendMode::Normal);
		break;
	case EGridState::Circled:
		CircleSprite->Draw(Color::White, BlendMode::Normal);
		break;
	}
	
}
