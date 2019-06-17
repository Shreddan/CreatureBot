#include <WS2tcpip.h>
#include <WinSock2.h>
#include <fstream>
#include <string>
#include <vector>

#include "Commands.h"


#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Ws2_32.lib")

namespace
{
	constexpr int BufferLength = 512;

	struct TwitchSocket
	{
	
		SOCKET Connection;
		std::vector<char> buffer;
	
		int send(const std::string& information)
		{
			return ::send(Connection, information.c_str(), information.length(), NULL);
		}
		std::string receive()
		{

			int bytesReceived = recv(Connection, buffer.data(), BufferLength, NULL);
			buffer[bytesReceived] = '\0';

			return std::string(buffer.begin(), buffer.begin() + bytesReceived);
		}

		TwitchSocket(const TwitchSocket&) = delete;
		TwitchSocket& operator=(const TwitchSocket&) = delete;

		TwitchSocket(SOCKET Connection)
		{
			this->Connection = Connection;
			this->buffer = std::vector<char>(BufferLength);
		}
	};

}

int main()
{
	WSADATA wsadata;
	SOCKET ConnectSocket = INVALID_SOCKET;
	addrinfo hints = {};
	addrinfo* result;
	std::ifstream fileIn("Twitch0AuthToken.txt", std::ios::in | std::ios::binary);
	std::string OAuthToken;
	std::string Username;
	std::string send;

	Commands command;

	int accumulator = 0;
	

	if (fileIn.is_open())
	{
		fileIn >> OAuthToken;
		fileIn >> Username;
		fileIn.close();
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		std::cout << "Socket Startup Failed" << std::endl;
		return 1;
	}
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	

	

	if (getaddrinfo("irc.chat.twitch.tv", "6667", &hints, &result) != 0)
	{
		std::cout << "Get Address Failed" << std::endl;
	}
	ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET)
	{
		std::cout << "Invalid Socket " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	if (connect(ConnectSocket, result->ai_addr, result->ai_addrlen) == SOCKET_ERROR)
	{
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		std::cout << "Cannot connect to server" << std::endl;
		WSACleanup();
		return 1;

	}

	TwitchSocket twitch(ConnectSocket);
	twitch.send("PASS " + OAuthToken + "\r\n");
	twitch.send("NICK " + Username + "\r\n");


	twitch.send("JOIN #danicron5\r\n");
	

	twitch.send("CAP REQ :twitch.tv/membership\r\n");

	twitch.receive();

	command.windowcheck(command.creaturewindow);

	twitch.send("PRIVMSG #danicron5 :CreatureBot Initialised\r\n");

	while (1)
	{
		std::string reply = twitch.receive();
		if (reply == "PING :tmi.twitch.tv\r\n")
		{
			std::cout << reply << std::endl;
			twitch.send("PONG :tmi.twitch.tv\r\n");
			std::cout << "Pong Returned!" << std::endl;
			accumulator++;
			std::cout << accumulator << std::endl;
			if (accumulator >= 1)
			{
				twitch.send("PRIVMSG #danicron5 :Check below for a list of Usable Commands!\r\n");
				accumulator = 0;
				continue;
			}

			continue;
		}

		

		command.processCommands(reply, command.creaturewindow, command.ip, command.wparam, command.lparam);
	}
	

	return 0;
}