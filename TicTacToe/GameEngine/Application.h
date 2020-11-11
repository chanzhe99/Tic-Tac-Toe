#pragma once
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <gl/GLU.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Matrix.h"
#include "Vector2.h"

class Application
{
private:
	int ResolutionX, ResolutionY;
	GLFWwindow* Window;
	double LastFrameTime, ThisFrameTime;
	double MaxFPS;
	double DeltaTime, MinDeltaTime;
	int SleepTime, MinSleepTimeTH;
	float FPS;
	char FPSDisplay[32];

public:
	Application();
	Application(int WindowResolutionX, int WindowResolutionY, double TargetMaxFPS);
	~Application();

	GLFWwindow* GetWindow() { return Window; }
	Vector2 GetWindowResolution() { return Vector2(ResolutionX, ResolutionY); }
	double GetDeltaTime() { return DeltaTime; }
	void GetMousePosition(GLFWwindow* AppWindow, double MousePosX, double MousePosY);
	void GetMouseButton(int MouseButton, int ButtonAction);

	int MakeWindow();
	void Update();
};

