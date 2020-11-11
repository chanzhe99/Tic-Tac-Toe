#pragma once
#include <GameObject.h>

enum class EButtonState
{
	Default,
	Highlighted
};

class ButtonObject : public GameObject
{
private:
	bool MouseIsOverlapping = false;

	EButtonState ButtonState;

public:
	ButtonObject();
	ButtonObject(Sprite* DesiredSprite);
	~ButtonObject();

	bool IsMouseOverlapping(GLFWwindow* AppWindow, double MousePosX, double MousePosY);
	bool IsMouseClicked(int MouseButton, int ButtonAction);

	void Draw();
};

