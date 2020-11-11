#include "Photon.h"
#include "Game.h"

#include <thread>
#include <mutex>

Game TTTGame;
std::mutex mu;

void OnMouseMove(GLFWwindow* Window, double MousePosX, double MousePosY)
{
	//TTTGame.GetApp().GetMousePosition(Window, MousePosX, MousePosY);

	//TTTGame.OnMouseMove(Window, MousePosX, MousePosY);
	if (TTTGame.GetCanGameStart())
	{
		if (TTTGame.IsGameOver())
		{
			TTTGame.GetReplayButtonUI()->IsMouseOverlapping(Window, MousePosX, MousePosY);
		}
		else if(TTTGame.GetPlayerNumber() == 1 && TTTGame.GetIsCrossTurn() || TTTGame.GetPlayerNumber() == 2 && !TTTGame.GetIsCrossTurn())
		{
			for (int y = 0; y < GRID_SIZE; y++)
			{
				for (int x = 0; x < GRID_SIZE; x++)
				{
					TTTGame.GetGrid(x, y)->IsMouseOverlapping(Window, MousePosX, MousePosY);
				}
			}
		}
	}
	
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	//TTTGame.GetApp().GetMouseButton(button, action);

	//TTTGame.OnMouseButton(button, action);

	if (button == 0 && action == 1)
	{
		if (TTTGame.GetCanGameStart())
		{
			if (!TTTGame.IsGameOver())
			{
				for (int y = 0; y < GRID_SIZE; y++)
				{
					for (int x = 0; x < GRID_SIZE; x++)
					{
						if (TTTGame.GetPlayerNumber() == 1 && TTTGame.GetIsCrossTurn() || TTTGame.GetPlayerNumber() == 2 && !TTTGame.GetIsCrossTurn())
						{
							if (TTTGame.GetGrid(x, y)->IsMouseClicked(TTTGame.GetIsCrossTurn()))
								Photon::GetInstance(TTTGame).SendMyVector2Data(TTTGame.GetGrid(x, y)->GetGridIndex());
						}
					}
				}
			}
			else if (TTTGame.GetReplayButtonUI()->IsMouseClicked(button, action))
			{
				TTTGame.SetReplayRequested(true);
				Photon::GetInstance(TTTGame).SendReplayRequest(TTTGame.GetReplayRequested());
			}
		}
		else
			std::cout << "Waiting for players..." << std::endl;
	}
	
}

void WaitForMessage()
{
	while (1)
	{
		std::string myString;

		//std::cout << "You: ";
		std::getline(std::cin, myString);
		//std::cout << "\033[A\033[2K\rYou:" << myString << std::endl;

		if (myString.size() > 0)
		{
			//std::cout << "Unencrypted string: " << myString << std::endl;
			int Key = 120;
			for (int i = 0; i < myString.length(); i++)
			{
				myString[i] = myString[i] ^ Key;
			}
			//std::cout << "Encrypted string: " << myString << std::endl;

			mu.lock();
			Photon::GetInstance(TTTGame).SendString(myString.c_str(), myString.length());
			mu.unlock();
		}


		Sleep(100);
	}
}

int main(void)
{
	TTTGame.Start();
	GLFWwindow* AppWindow = TTTGame.GetApp().GetWindow();

	// hook mouse move callback and lock/hide mouse cursor.
	glfwSetCursorPosCallback(AppWindow, OnMouseMove);
	glfwSetMouseButtonCallback(AppWindow, OnMouseButton);

	Photon::GetInstance(TTTGame).Connect();

	std::thread Thread1(&WaitForMessage);

	while (!glfwWindowShouldClose(AppWindow))
	{
		mu.lock();
		Photon::GetInstance(TTTGame).Run();
		mu.unlock();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		TTTGame.Update();
		TTTGame.Draw();

		glfwSwapBuffers(AppWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}