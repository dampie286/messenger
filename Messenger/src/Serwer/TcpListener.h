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
Klasa odpowiedzialna za inicjalizację serwera, czyli postawienie serwera TCP/IP oraz komunikację między użytkownikami.
*/

class TcpListener:public Sck {
private:
	/**
	Tablica mieszająca przechowująca nazwy użytkowników podłączonych do serwera, który każdej nazwie jest przypisany klucz, czyli numer gniazda.
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
		Metoda inicjalizująca powstanie gniazda nasłuchującego.
		@return Gniazdo stworzone na podstawie parametrów w klasie.
	*/
	SOCKET CreateSocket() override;
	/**
		Metoda pozwalająca dołączyć klientowi do serwera.
		@param listening Gniazdo nasłuchujące, które chce dołączyć do serwera
		@param klienci   Tablica mieszająca przechowująca nazwy użytkowników przypisanych do danego gniazda
		@return Gnizado, które zostało przyjęte do serwera
	*/
	SOCKET WaitForConnection(const SOCKET &listening, std::unordered_map<SOCKET, std::string>& klienci);
public:
	/**
		Konstruktor inicjalizujący powstanie klasy TcpListener.
		@param ipAddress Adres IP serwera.
		@param port  Port serwera.
	*/
	TcpListener(const std::string &ipAddress, const  int &port) :m_IpAdddress(ipAddress), m_port(port) {}; 
	/**
		Destruktor klasy TcpListener.
	*/
	~TcpListener();
	/**
		Wątek pozwalający wyłączyć serwer.
	*/
	std::thread write; 
	/**
		"Flaga" oznajmująca zakończenie pracy serwera, jak i wątku.
	*/
	bool end = false;
	/**
		Metoda pozwalająca na załadowanie bibliotek WinSocket.
	*/
	bool Initialize() override;
	/**
		Metoda utrzymująca działanie serwera i komunikację między użytkownikami
		@return Zwraca true jeśli się powiedzie, w przeciwnym false
	*/
	void Run();
	/**
		Metoda sprzątająca, czyli usuwanie i czyszcznie zaalokowanych pamięci.
	*/
	void Cleanup() override;
};