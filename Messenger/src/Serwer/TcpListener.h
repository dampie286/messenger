#pragma once
#pragma comment (lib,"ws2_32.lib")	//Winsock library file
#include<WinSock2.h>
#include <ws2tcpip.h>
#include<iostream>
#include<string>
#include<unordered_map>
#include "Sck.h"
#include<thread>
/**
Klasa odpowiedzialna za inicjalizacj� serwera, czyli postawienie serwera TCP/IP oraz komunikacj� mi�dzy u�ytkownikami.
*/

class TcpListener:public Sck {
private:
	/**
	Tablica mieszaj�ca przechowuj�ca nazwy u�ytkownik�w pod��czonych do serwera, kt�ry ka�dej nazwie jest przypisany klucz, czyli numer gniazda.
	*/
	std::unordered_map<SOCKET, std::string> klienci;
	/**
		Adres IP serwera 
	*/
	std::string	m_IpAdddress;
	/**
		Numer portu serwera 
	*/
	int	m_port;
	/**
		Metoda inicjalizuj�ca powstanie gniazda nas�uchuj�cego.
		@return Gniazdo stworzone na podstawie parametr�w w klasie.
	*/
	SOCKET CreateSocket() override;
	/**
		Metoda pozwalaj�ca do��czy� klientowi do serwera.
		@param listening Gniazdo nas�uchuj�ce, kt�re chce do��czy� do serwera
		@param klienci   Tablica mieszaj�ca przechowuj�ca nazwy u�ytkownik�w przypisanych do danego gniazda
		@return Gnizado, kt�re zosta�o przyj�te do serwera
	*/
	SOCKET WaitForConnection(const SOCKET &listening, std::unordered_map<SOCKET, std::string>& klienci);
public:
	/**
		Konstruktor inicjalizuj�cy powstanie klasy TcpListener.
		@param ipAddress Adres IP serwera.
		@param port  Port serwera.
	*/
	TcpListener(const std::string &ipAddress, const  int &port) :m_IpAdddress(ipAddress), m_port(port) {}; 
	/**
		Destruktor klasy TcpListener.
	*/
	~TcpListener();
	/**
		W�tek pozwalaj�cy wy��czy� serwer.
	*/
	std::thread write; 
	/**
		"Flaga" oznajmuj�ca zako�czenie pracy serwera, jak i w�tku.
	*/
	bool end = false;
	/**
		Metoda pozwalaj�ca na za�adowanie bibliotek WinSocket.
	*/
	bool Initialize() override;
	/**
		Metoda utrzymuj�ca dzia�anie serwera i komunikacj� mi�dzy u�ytkownikami
		@return Zwraca true je�li si� powiedzie, w przeciwnym false
	*/
	void Run();
	/**
		Metoda sprz�taj�ca, czyli usuwanie i czyszcznie zaalokowanych pami�ci.
	*/
	void Cleanup() override;
};