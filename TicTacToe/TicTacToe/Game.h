#pragma once

#include <Application.h>
#include <GameObject.h>
#include <Sprite.h>

#include "windows.h"
#include "GridObject.h"
#include "ButtonObject.h"

#define WINDOW_X 720
#define WINDOW_Y 720

#define GRID_SIZE 3

class Game
{
private:

	Sprite* WaitingUISprite;
	Sprite* WinUISprite;
	Sprite* LoseUISprite;
	Sprite* DrawUISprite;
	Sprite* MyTurnUISprite;
	Sprite* OpponentTurnUISprite;
	Sprite* PendingUISprite;
	Sprite* ReplayButtonUISprite;

	GameObject WaitingUI;
	GameObject WinUI;
	GameObject LoseUI;
	GameObject DrawUI;
	GameObject MyTurnUI;
	GameObject OpponentTurnUI;
	GameObject PendingUI;
	ButtonObject* ReplayButtonUI;

	Application App = Application(WINDOW_X, WINDOW_Y, 60);
	GridObject* Grid[GRID_SIZE][GRID_SIZE];

	bool CanGameStart = false;
	int Winner = 0;

	int PlayerNumber = 0;
	bool IsCrossTurn = true;
	bool ReplayRequested = false;



public:
	Game();
	~Game() {}

	Application GetApp() { return App; }
	
	GridObject* GetGrid(int X, int Y) { return Grid[X][Y]; }
	void SetGrid(int X, int Y);
	
	ButtonObject* GetReplayButtonUI() { return ReplayButtonUI; }

	bool GetCanGameStart() { return CanGameStart; }
	void SetCanGameStart(bool Value) { CanGameStart = Value; }

	int GetPlayerNumber() { return PlayerNumber; }
	void SetPlayerNumber(int DesiredPlayerNumber);

	bool GetIsCrossTurn() { return IsCrossTurn; }
	void InvertCrossTurn() { IsCrossTurn = !IsCrossTurn; }

	bool GetReplayRequested() { return ReplayRequested; }
	void SetReplayRequested(bool Value) { ReplayRequested = Value; }

	void ResetGame();

	bool IsGameOver();
	bool CheckHorizontalTiles(int TilesCrossed, int TilesCircled);
	bool CheckVerticalTiles(int TilesCrossed, int TilesCircled);
	bool CheckDiagonalTiles(int TilesCrossed, int TilesCircled);
	bool CheckEmptyTiles(int TilesEmpty);

	void OnMouseMove(GLFWwindow* AppWindow, double MousePosX, double MousePosY);
	void OnMouseButton(int MouseButton, int ButtonAction);

	void Start();
	void Update();
	void Draw();
};
