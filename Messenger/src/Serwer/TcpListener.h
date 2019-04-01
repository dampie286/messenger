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
Klasa odpowiedzialna za inicjalizacjê serwera, czyli postawienie serwera TCP/IP oraz komunikacjê miêdzy u¿ytkownikami.
*/

class TcpListener:public Sck {
private:
	/**
	Tablica mieszaj¹ca przechowuj¹ca nazwy u¿ytkowników pod³¹czonych do serwera, który ka¿dej nazwie jest przypisany klucz, czyli numer gniazda.
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
		Metoda inicjalizuj¹ca powstanie gniazda nas³uchuj¹cego.
		@return Gniazdo stworzone na podstawie parametrów w klasie.
	*/
	SOCKET CreateSocket() override;
	/**
		Metoda pozwalaj¹ca do³¹czyæ klientowi do serwera.
		@param listening Gniazdo nas³uchuj¹ce, które chce do³¹czyæ do serwera
		@param klienci   Tablica mieszaj¹ca przechowuj¹ca nazwy u¿ytkowników przypisanych do danego gniazda
		@return Gnizado, które zosta³o przyjête do serwera
	*/
	SOCKET WaitForConnection(const SOCKET &listening, std::unordered_map<SOCKET, std::string>& klienci);
public:
	/**
		Konstruktor inicjalizuj¹cy powstanie klasy TcpListener.
		@param ipAddress Adres IP serwera.
		@param port  Port serwera.
	*/
	TcpListener(const std::string &ipAddress, const  int &port) :m_IpAdddress(ipAddress), m_port(port) {}; 
	/**
		Destruktor klasy TcpListener.
	*/
	~TcpListener();
	/**
		W¹tek pozwalaj¹cy wy³¹czyæ serwer.
	*/
	std::thread write; 
	/**
		"Flaga" oznajmuj¹ca zakoñczenie pracy serwera, jak i w¹tku.
	*/
	bool end = false;
	/**
		Metoda pozwalaj¹ca na za³adowanie bibliotek WinSocket.
	*/
	bool Initialize() override;
	/**
		Metoda utrzymuj¹ca dzia³anie serwera i komunikacjê miêdzy u¿ytkownikami
		@return Zwraca true jeœli siê powiedzie, w przeciwnym false
	*/
	void Run();
	/**
		Metoda sprz¹taj¹ca, czyli usuwanie i czyszcznie zaalokowanych pamiêci.
	*/
	void Cleanup() override;
};