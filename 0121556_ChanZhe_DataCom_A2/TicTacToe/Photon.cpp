#include "Photon.h"

static const ExitGames::Common::JString appId = L"88eab4cf-e716-4fd5-a3cf-109ca086f23f"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";
static const ExitGames::Common::JString PLAYER_NAME = L"Windows";

void Photon::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
{

	if (playernrs.getSize() >= 2)
	{
		//SendMyID(0);
		std::wcout << "An opponent has joined the room." << std::endl;
		MyGame.SetPlayerNumber(2);
		MyGame.SetCanGameStart(true);
		std::wcout << "Game started.\n\n" << "[PLAYER CHAT]\n";
	}
	else
	{
		std::wcout << "You have joined the room." << std::endl;
		MyGame.SetPlayerNumber(1);
		std::wcout << "Waiting for players..." << std::endl;
	}
}

void Photon::leaveRoomEventAction(int playerNr, bool isInactive)
{
	std::wcout << "The opponent has left the room." << std::endl;
	
	MyGame.SetPlayerNumber(NULL);
	MyGame.ResetGame();
	MyGame.SetCanGameStart(false);
}

void Photon::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
	if (eventCode == 1) // float data
	{
		float* data = ExitGames::Common::ValueObject<float*>(eventContent).getDataCopy();
		if (data) std::cout << "Received: " << data[0] << ", " << data[1] << std::endl;
		else std::cout << "Invalid data" << std::endl;
	}
	else if (eventCode == 2) // string data
	{
		ExitGames::Common::JString data = ExitGames::Common::ValueObject<ExitGames::Common::JString>(eventContent).getDataCopy();
		if (data) std::wcout << "Friend " << playerNr << ": " << data << std::endl;
		else std::cout << "Invalid data" << std::endl;
	}
	else if (eventCode == 3) // grid data
	{
		float* data = ExitGames::Common::ValueObject<float*>(eventContent).getDataCopy();
		if (data)
		{
			//std::cout << "Received: " << data[0] << ", " << data[1] << std::endl;
			MyGame.SetGrid(data[0], data[1]);
			MyGame.InvertCrossTurn();
		}
		else std::cout << "Invalid data" << std::endl;
	}
	else if (eventCode == 4) // replay button data
	{
		bool data = ExitGames::Common::ValueObject<bool>(eventContent).getDataCopy();
		if (data)
		{
			/*std::cout << "My replay request: " << MyGame.GetReplayRequested() << std::endl;
			std::cout << "Opponent replay request: " << data << std::endl;*/
			if (MyGame.GetReplayRequested())
			{
				SendReplayRequest(MyGame.GetReplayRequested());
				MyGame.SetReplayRequested(false);
				MyGame.SetPlayerNumber(3);
				MyGame.ResetGame();
			}
		}
	}
	else if (eventCode == 5) // chat data
	{
		unsigned char* StringDataInBytes = ExitGames::Common::ValueObject<unsigned char*>(eventContent).getDataCopy();
		const int* StringSize = ExitGames::Common::ValueObject<unsigned char*>(eventContent).getSizes();

		if (StringDataInBytes)
		{
			int Key = 120;
			for (int i = 0; i < StringSize[0]; i++)
			{
				StringDataInBytes[i] = StringDataInBytes[i] ^ Key;
			}
			StringDataInBytes[StringSize[0]] = '\0';
			std::cout << "Opponent: " << StringDataInBytes << std::endl;
			//std::cout << "\033[A\33[2K\rOpponent: " << StringDataInBytes << std::endl;
		}
		else std::wcout << "invalid data" << std::endl;
	}
}

void Photon::connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& cluster)
{
	if (errorCode)
		std::wcout << "Failed to connect : " << errorString.cstr() << std::endl;
	else
	{
		std::wcout << "Connected to Photon Server." << std::endl;

		std::wcout << "Trying to join a random room..." << std::endl;
		LoadBalancingClient.opJoinRandomRoom();
	}
}

void Photon::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout << "Joining a random room..." << std::endl;

	if (errorCode)
	{
		std::wcout << "Failed to join a random room : " << errorCode << ", " << errorString.cstr() << std::endl;

		if (errorCode == 32760) //no match found error code
		{
			std::wcout << "Creating a room..." << std::endl;
			//try to create a room and wait;
			ExitGames::Common::JString name;
			name += GETTIMEMS();
			LoadBalancingClient.opCreateRoom(name, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(2));
		}

		return;
	}
}

Photon::Photon(Game& CurrentGame) : LoadBalancingClient(*this, appId, appVersion, ExitGames::Photon::ConnectionProtocol::TCP, false, ExitGames::LoadBalancing::RegionSelectionMode::SELECT), MyGame(CurrentGame)
{
}

void Photon::Connect(void)
{
	std::wcout << "Connecting..." << std::endl;
	LoadBalancingClient.connect(ExitGames::LoadBalancing::AuthenticationValues(), PLAYER_NAME);
}

void Photon::SendMyID(int IDNum)
{
	float data[6];
	data[0] = 6.9f;
	data[1] = 6.9f;

	LoadBalancingClient.opRaiseEvent(true, data, 2, 1);
}

void Photon::SendMyVector2Data(Vector2 Vector2Data)
{
	float data[2];
	data[0] = Vector2Data.X;
	data[1] = Vector2Data.Y;
	MyGame.InvertCrossTurn();
	LoadBalancingClient.opRaiseEvent(true, data, 2, 3);
}

void Photon::SendReplayRequest(bool ReplayData)
{
	LoadBalancingClient.opRaiseEvent(true, ReplayData, 4);
}

void Photon::SendString(const char* StringData, int StringSize)
{
	const unsigned char* StringDataInBytes = (const unsigned char*)StringData;
	LoadBalancingClient.opRaiseEvent(true, StringDataInBytes, StringSize, 5);
}
