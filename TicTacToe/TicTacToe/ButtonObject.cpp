#include "ButtonObject.h"

ButtonObject::ButtonObject()
{
	ButtonState = EButtonState::Default;
}

ButtonObject::ButtonObject(Sprite* DesiredSprite) : GameObject(DesiredSprite)
{
	ButtonState = EButtonState::Default;
}

ButtonObject::~ButtonObject()
{
}

bool ButtonObject::IsMouseOverlapping(GLFWwindow* AppWindow, double MousePosX, double MousePosY)
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
		if (ButtonState == EButtonState::Default)
			ButtonState = EButtonState::Highlighted;
		MouseIsOverlapping = true;
		return true;
	}

	if (ButtonState == EButtonState::Highlighted)
		ButtonState = EButtonState::Default;
	MouseIsOverlapping = false;
	return false;
}

bool ButtonObject::IsMouseClicked(int MouseButton, int ButtonAction)
{
	if (ButtonState == EButtonState::Highlighted)
	{
		return true;
	}
	return false;
}

void ButtonObject::Draw()
{
	TransformMatrix = TranslateMatrix * RotateMatrix * ScaleMatrix;
	glLoadMatrixf((GLfloat*)TransformMatrix.mVal);

	switch (ButtonState)
	{
	case EButtonState::Default:
		ObjectSprite->Draw(Color::White, BlendMode::Normal);
		break;
	case EButtonState::Highlighted:
		ObjectSprite->Draw(Color(1, 0.984, 0.651, 1.0), BlendMode::Normal);
		break;
	}
}
