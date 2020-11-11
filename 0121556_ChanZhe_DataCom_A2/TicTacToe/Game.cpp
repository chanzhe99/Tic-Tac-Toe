#include "Game.h"

Game::Game()
{
}

void Game::SetGrid(int X, int Y)
{
	if(IsCrossTurn)
		Grid[X][Y]->SetGridState(EGridState::Crossed);
	else
		Grid[X][Y]->SetGridState(EGridState::Circled);
}

void Game::ResetGame()
{
	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			Grid[x][y]->SetGridState(EGridState::Empty);
		}
	}
	
	Winner = 0;
	IsCrossTurn = true;
}

bool Game::IsGameOver()
{
	int TilesEmpty = 0;
	int TilesCrossed = 0;
	int TilesCircled = 0;

	if (CheckHorizontalTiles(TilesCrossed, TilesCircled))
	{
		//std::cout << "Horizontal Win" << std::endl;
		return true;
	}
	else if (CheckVerticalTiles(TilesCrossed, TilesCircled))
	{
		//std::cout << "Vertical Win" << std::endl;
		return true;
	}
	else if (CheckDiagonalTiles(TilesCrossed, TilesCircled))
	{
		//std::cout << "Diagonal Win" << std::endl;
		return true;
	}
	else if (CheckEmptyTiles(TilesEmpty))
	{
		//std::cout << "Draw" << std::endl;
		return true;
	}

	return false;
}

bool Game::CheckHorizontalTiles(int TilesCrossed, int TilesCircled)
{
	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			switch (Grid[x][y]->GetGridState())
			{
			case EGridState::Crossed:
				TilesCrossed++;
				break;
			case EGridState::Circled:
				TilesCircled++;
				break;
			}
		}

		if (TilesCrossed == 3)
		{
			Winner = 1;
			return true;
		}
		else if (TilesCircled == 3)
		{
			Winner = 2;
			return true;
		}
		TilesCrossed = 0;
		TilesCircled = 0;
	}
	return false;
}

bool Game::CheckVerticalTiles(int TilesCrossed, int TilesCircled)
{
	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			switch (Grid[x][y]->GetGridState())
			{
			case EGridState::Crossed:
				TilesCrossed++;
				break;
			case EGridState::Circled:
				TilesCircled++;
				break;
			}
		}

		if (TilesCrossed == 3)
		{
			Winner = 1;
			return true;
		}
		else if (TilesCircled == 3)
		{
			Winner = 2;
			return true;
		}
		TilesCrossed = 0;
		TilesCircled = 0;
	}
	return false;
}

bool Game::CheckDiagonalTiles(int TilesCrossed, int TilesCircled)
{
	for (int xy = 0; xy < GRID_SIZE; xy++)
	{
		switch (Grid[xy][xy]->GetGridState())
		{
		case EGridState::Crossed:
			TilesCrossed++;
			break;
		case EGridState::Circled:
			TilesCircled++;
			break;
		}
	}

	if (TilesCrossed == 3)
	{
		Winner = 1;
		return true;
	}
	else if (TilesCircled == 3)
	{
		Winner = 2;
		return true;
	}
	TilesCrossed = 0;
	TilesCircled = 0;

	int x = 2;
	for (int y = 0; y < GRID_SIZE; y++)
	{
		switch (Grid[x][y]->GetGridState())
		{
		case EGridState::Crossed:
			TilesCrossed++;
			break;
		case EGridState::Circled:
			TilesCircled++;
			break;
		}
		x--;
	}

	if (TilesCrossed == 3)
	{
		Winner = 1;
		return true;
	}
	else if (TilesCircled == 3)
	{
		Winner = 2;
		return true;
	}
	TilesCrossed = 0;
	TilesCircled = 0;

	return false;
}

bool Game::CheckEmptyTiles(int TilesEmpty)
{
	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			switch (Grid[x][y]->GetGridState())
			{
			case EGridState::Empty:
			case EGridState::Highlighted:
				TilesEmpty++;
				break;
			}
		}
	}

	if (TilesEmpty == 0)
	{
		//Winner = 3;
		return true;
		/*if (Winner == 0)
		{
			Winner = 3;
			return true;
		}*/
	}

	return false;
}

void Game::OnMouseMove(GLFWwindow* AppWindow, double MousePosX, double MousePosY)
{
	/*for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			Grid[x][y]->CheckIsHovering(AppWindow, MousePosX, MousePosY);
		}
	}*/
}

void Game::OnMouseButton(int MouseButton, int ButtonAction)
{
	//for (int y = 0; y < GRID_SIZE; y++)
	//{
	//	for (int x = 0; x < GRID_SIZE; x++)
	//	{
	//		Grid[x][y]->CheckIsClicked(MouseButton, ButtonAction, IsCrossTurn);
	//		//if (Grid[x][y]->CheckIsClicked(MouseButton, ButtonAction, IsCrossTurn))
	//			//Photon::GetInstance().SendVector2Data(Grid[x][y]->GetGridIndex());
	//	}
	//}
}

void Game::SetPlayerNumber(int DesiredPlayerNumber)
{
	if (PlayerNumber == 0)
	{
		PlayerNumber = DesiredPlayerNumber;
		std::cout << "You are Player " << PlayerNumber;
		if (PlayerNumber == 1) std::cout << " (CROSS)\n";
		else std::cout << " (CIRCLE)\n";
	}
	else if (DesiredPlayerNumber == 3)
	{
		if (PlayerNumber == 1)
		{
			PlayerNumber = 2;
			std::cout << "You are now Player " << PlayerNumber << " (CIRCLE)\n";
		}
		else
		{
			PlayerNumber = 1;
			std::cout << "You are now Player " << PlayerNumber << " (CROSS)\n";
		}
	}
	if (!DesiredPlayerNumber)
	{
		PlayerNumber = 1;
		std::cout << "You are now Player " << PlayerNumber << " (CROSS)" << std::endl;
	}
}

void Game::Start()
{
	App.MakeWindow();

	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			Grid[x][y] = new GridObject(x, y);
			Grid[x][y]->SetPosition(Vector2(x * Grid[x][y]->GetWorldScale().X, -y * Grid[x][y]->GetWorldScale().Y));
			Grid[x][y]->SetPosition(Grid[x][y]->GetPosition() + Vector2(WINDOW_X / 2, WINDOW_Y / 2) + (Vector2(-Grid[x][y]->GetWorldScale().X, Grid[x][y]->GetWorldScale().Y)));
		}
	}

	WaitingUISprite = new Sprite("../Content/WaitingForPlayers.bmp");
	WinUISprite = new Sprite("../Content/Win.bmp");
	LoseUISprite = new Sprite("../Content/Lose.bmp");
	DrawUISprite = new Sprite("../Content/Draw.bmp");
	MyTurnUISprite = new Sprite("../Content/YourTurn.bmp");
	OpponentTurnUISprite = new Sprite("../Content/OpponentTurn.bmp");
	PendingUISprite = new Sprite("../Content/Pending.bmp");
	ReplayButtonUISprite = new Sprite("../Content/PlayAgain.bmp");

	WaitingUI = GameObject(WaitingUISprite);
	WinUI = GameObject(WinUISprite);
	LoseUI = GameObject(LoseUISprite);
	DrawUI = GameObject(DrawUISprite);
	MyTurnUI = GameObject(MyTurnUISprite);
	OpponentTurnUI = GameObject(OpponentTurnUISprite);
	PendingUI = GameObject(PendingUISprite);
	ReplayButtonUI = new ButtonObject(ReplayButtonUISprite);

	Vector2 Offset(0, 150);

	WaitingUI.SetPosition(Vector2(Grid[1][0]->GetPosition()) + Offset);

	WinUI.SetPosition(Vector2(Grid[1][0]->GetPosition()) + Offset);
	LoseUI.SetPosition(Vector2(Grid[1][0]->GetPosition()) + Offset);
	DrawUI.SetPosition(Vector2(Grid[1][0]->GetPosition()) + Offset);

	MyTurnUI.SetPosition(Vector2(Grid[1][0]->GetPosition()) + Offset);
	OpponentTurnUI.SetPosition(Vector2(Grid[1][0]->GetPosition()) + Offset);
	PendingUI.SetPosition(Vector2(Grid[1][2]->GetPosition()) - Offset);
	ReplayButtonUI->SetPosition(Vector2(Grid[1][2]->GetPosition()) - Offset);
}

void Game::Update()
{
	App.Update();
}

void Game::Draw()
{
	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			Grid[x][y]->Draw();
		}
	}

	if (!CanGameStart)
	{
		WaitingUI.Draw();
	}
	else if (IsGameOver())
	{
		if (Winner == 0)
			DrawUI.Draw();
		else if (PlayerNumber == Winner)
			WinUI.Draw();
		else if (PlayerNumber != Winner)
			LoseUI.Draw();

		if (ReplayRequested)
			PendingUI.Draw();
		else
			ReplayButtonUI->Draw();
	}
	else
	{
		if (PlayerNumber == 1 && IsCrossTurn || PlayerNumber == 2 && !IsCrossTurn)
			MyTurnUI.Draw();
		else
			OpponentTurnUI.Draw();
	}
}
