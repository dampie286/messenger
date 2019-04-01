#pragma once
#pragma comment (lib,"ws2_32.lib")	//Winsock library file
#include<WinSock2.h>
#include <ws2tcpip.h>
/**
Wirtualna klasa bazowa klasy TcpListener(serwer) oraz klasy TcpClient(u¿ytkownik clienta) 
*/

class Sck {
public:

	virtual ~Sck() {}						///destruktor wirtualnej klasy Sck
	virtual SOCKET CreateSocket() = 0;		///wirtualna metoda CreateSocket()
	virtual void Cleanup() = 0;				///wirtualna metoda Cleanup()
	virtual bool Initialize() = 0;			///wirtualna metoda Initialize()
};
