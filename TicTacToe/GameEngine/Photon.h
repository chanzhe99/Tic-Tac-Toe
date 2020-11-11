#pragma once

#include <LoadBalancing-cpp/inc/Client.h>
#include <iostream>
#include "Vector2.h"

class Photon : private ExitGames::LoadBalancing::Listener
{
private:
	Vector2 ClickedIndex = Vector2(-1, -1);
	ExitGames::LoadBalancing::Client LoadBalancingClient;

	// receive and print out debug out here
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string) {}

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode) { std::wcout << "ConnectionErrorReturn : " << errorCode << std::endl; }
	virtual void clientErrorReturn(int errorCode) { std::wcout << "ClientErrorReturn : " << errorCode << std::endl; }
	virtual void warningReturn(int warningCode) { std::wcout << "WarningReturn : " << warningCode << std::endl; }
	virtual void serverErrorReturn(int errorCode) { std::wcout << "ServerErrorReturn : " << errorCode << std::endl; }

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr, bool isInactive) { std::wcout << "LeaveRoomEventAction" << std::endl; }
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

	virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats) { std::wcout << "OnLobbyStatsResponse" << std::endl; }
	virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats) { std::wcout << "OnLobbyStatsUpdate" << std::endl; }
	virtual void onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers) { LoadBalancingClient.selectRegion("Asia"); }

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& cluster);
	virtual void disconnectReturn(void) { std::wcout << "Disconnected" << std::endl; }
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString) { std::wcout << "CreateRoomReturn" << std::endl; }
	virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString) { std::wcout << "JoinOrCreateRoomReturn" << std::endl; }
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString) { std::wcout << "JoinRoomReturn" << std::endl; }
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString) { std::wcout << "LeaveRoomReturn" << std::endl; }
	virtual void joinLobbyReturn(void) { std::wcout << "JoinLobbyReturn" << std::endl; }
	virtual void leaveLobbyReturn(void) { std::wcout << "LeaveLobbyReturn" << std::endl; }

public:
	Photon();
	~Photon() {}

	void Run(void) { LoadBalancingClient.service(); }
	void Connect(void);
	void Disconnect(void) { LoadBalancingClient.disconnect(); }

	static Photon& GetInstance()
	{
		static Photon Instance;
		return Instance;
	}

	Vector2 GetClickedIndex() { return ClickedIndex; }

	void SendMyData(void);
	void SendVector2Data(Vector2 Vector2Data);
};

