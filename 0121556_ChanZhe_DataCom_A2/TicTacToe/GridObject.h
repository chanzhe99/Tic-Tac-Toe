#pragma once
#include <GameObject.h>

enum class EGridState
{
	Empty,
	Highlighted,
	Crossed,
	Circled
};

class GridObject : public GameObject
{
private:
	Sprite* CrossSprite;
	Sprite* CircleSprite;

	EGridState GridState;
	Vector2 GridIndex;

	bool MouseIsOverlapping;

public:
	GridObject();
	GridObject(int IndexX, int IndexY);
	~GridObject();

	EGridState GetGridState() { return GridState; }
	void SetGridState(EGridState DesiredState) { GridState = DesiredState; }
	Vector2 GetGridIndex() { return GridIndex; }

	bool IsMouseOverlapping(GLFWwindow* AppWindow, double MousePosX, double MousePosY);
	bool IsMouseClicked(bool IsCrossing);

	void Update(float DeltaTime);
	void Draw();
};

