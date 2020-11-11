#include "Photon.h"

static const ExitGames::Common::JString appId = L"88eab4cf-e716-4fd5-a3cf-109ca086f23f"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";
static const ExitGames::Common::JString PLAYER_NAME = L"Windows";

void Photon::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
{
	std::wcout << "joinRoomEventAction" << std::endl;

	if (playernrs.getSize() >= 2)
		SendMyData();
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
			std::cout << "Received: " << data[0] << ", " << data[1] << std::endl;
			ClickedIndex = Vector2(data[0], data[1]);
		}
		else std::cout << "Invalid data" << std::endl;
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
	std::wcout << "JoinRandomRoomReturn" << std::endl;

	if (errorCode)
	{
		std::wcout << "Failed to join a random room : " << errorCode << ", " << errorString.cstr() << std::endl;

		if (errorCode == 32760) //no match found error code
		{
			std::wcout << "Creating a room..." << std::endl;
			//try to create a room and wait;
			ExitGames::Common::JString name;
			name += GETTIMEMS();
			LoadBalancingClient.opCreateRoom(name, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(20));
		}

		return;
	}
}

Photon::Photon() : LoadBalancingClient(*this, appId, appVersion, ExitGames::Photon::ConnectionProtocol::TCP, false, ExitGames::LoadBalancing::RegionSelectionMode::SELECT)
{
}

void Photon::Connect(void)
{
	std::wcout << "Connecting..." << std::endl;
	LoadBalancingClient.connect(ExitGames::LoadBalancing::AuthenticationValues(), PLAYER_NAME);
}

void Photon::SendMyData(void)
{
	float data[6];
	data[0] = 6.9f;
	data[1] = 6.9f;

	LoadBalancingClient.opRaiseEvent(true, data, 2, 1);
}

void Photon::SendVector2Data(Vector2 Vector2Data)
{
	float data[6];
	data[0] = Vector2Data.X;
	data[1] = Vector2Data.Y;

	LoadBalancingClient.opRaiseEvent(true, data, 2, 1);
}
