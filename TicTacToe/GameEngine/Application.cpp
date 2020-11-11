#include "Application.h"

void OnWindowResized(GLFWwindow* Window, int Width, int Height)
{
	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Use ortho 2D view
	gluOrtho2D(0, Width, 0, Height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Application::Application()
{
	ResolutionX = 1280;
	ResolutionY = 720;
	MaxFPS = 60;
}

Application::Application(int WindowResolutionX, int WindowResolutionY, double TargetMaxFPS)
{
	ResolutionX = WindowResolutionX;
	ResolutionY = WindowResolutionY;
	MaxFPS = TargetMaxFPS;
}

Application::~Application()
{
	
}

void Application::GetMousePosition(GLFWwindow* AppWindow, double MousePosX, double MousePosY)
{
	std::cout << "Mouse position: " << MousePosX << ", " << MousePosY << std::endl;
}

void Application::GetMouseButton(int MouseButton, int ButtonAction)
{
	std::cout << "Mouse button: " << MouseButton << ", " << ButtonAction << std::endl;
}

int Application::MakeWindow()
{
	srand(time(NULL));

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	Window = glfwCreateWindow(ResolutionX, ResolutionY, "Game Window", NULL, NULL);
	if (!Window)
	{
		std::cout << "Window does not exist, glfw terminating..." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(Window, OnWindowResized);

	/* Make the window's context current */
	glfwMakeContextCurrent(Window);
	OnWindowResized(Window, ResolutionX, ResolutionY);
	Matrix matrix(Matrix::makeIdentityMatrix());
	glfwSwapInterval(0); // enable/disable vsync
	LastFrameTime = glfwGetTime();
	MinDeltaTime = 1 / MaxFPS;
	MinSleepTimeTH = 10;

	std::cout << "Game window started successfully" << std::endl;
	return 0;
}

void Application::Update()
{
	ThisFrameTime = glfwGetTime();
	DeltaTime = ThisFrameTime - LastFrameTime;

	//============================================================
	MinSleepTimeTH = 10;
	// Conservatively asking the system to sleep
	SleepTime = (MinDeltaTime - DeltaTime) * 1000 - MinSleepTimeTH;
	if (SleepTime >= MinSleepTimeTH)
		Sleep(SleepTime);

	// Sleep time is no precise, use loop to "waste" extra cpu cycles
	while (DeltaTime < MinDeltaTime)
		DeltaTime = glfwGetTime() - LastFrameTime;
	//============================================================

	LastFrameTime = glfwGetTime();

	FPS = 1.0 / DeltaTime;
	sprintf_s(FPSDisplay, "%f, %f", FPS, (float)DeltaTime);
	glfwSetWindowTitle(Window, FPSDisplay);
}
