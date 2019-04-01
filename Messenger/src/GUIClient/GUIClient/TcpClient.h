#pragma once
#pragma comment(lib, "ws2_32.lib") //dodanie bibliotek winsocket
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#include<iostream>
#include <queue>
#include<mutex>
#include "Sck.h"


class TcpClient :public Sck {
private:
	/**
		Zmienna przechowuj¹ca nazwê u¿ytkownika.
	*/
	std::string name;
	/**
		Zmienna przechowuj¹ca adres IP serwera.
	*/
	std::string m_ipAddress;
	/**
		Zmienna przechowuj¹ca port serwera.
	*/
	int m_port;
	/**
	Metoda wirtualna inicjalizuj¹ca powstanie gniazda nas³uchuj¹cego.
	@return Gniazdo stworzone na podstawie parametrów w klasie.
	*/
	SOCKET CreateSocket() override;
	/**
		Metoda umo¿liwiaj¹ca po³¹czenie z serwerem.
		@param conn Gniazdo utworzone przez u¿ytkownika.
		@return Gniazdo, które zosta³o przyjête przez serwer.
	*/
	SOCKET ConnectToSerwer(const SOCKET &conn);
	/**
		Kolejka priorytetowa przechowuj¹ca wiadomoœci odebrane.
	*/
	std::deque<std::string> messages;
	
	
	
public:
	/**
	Konstruktor inicjalizuj¹cy powstanie klasy TcpClient.
	@param ipAddress Adres IP serwera.
	@param port  Port serwera.
	@param nick Nazwa u¿ytkownika.
	*/
	TcpClient(const std::string &ipAD, const int &port, const std::string &nick) : m_ipAddress(ipAD), m_port(port), name(nick) {};
	/**
	Destruktor klasy TcpClient.
	*/
	~TcpClient()
	{
		Cleanup();
	}
	/**
		Metoda s³u¿¹ca do wysy³ania wiadomoœci.
		@param client Gniazdo u¿ytkownika.
		@param buf Treœæ wiadomoœci wysy³anej.
		@param len D³ugoœæ wiadmoœci.
		@return Wartoœæ, która jest flag¹ poprawnego wys³ania(0) lub nie(-1).
	*/
	int SendAll(int client, const char *buf, int *len);
	/**
		Metoda utrzymuj¹ca dzia³anie serwera i komunikacjê miêdzy u¿ytkownikami
		@return Zwraca true jeœli siê powiedzie, w przeciwnym false
	*/
	bool Initialize() override;
	/**
		Metoda s³u¿¹ca do uruchomienia klienta i ³¹czenie go z klientem.
		@return Gniazdo po³¹czone z serwerem.
	*/
	SOCKET conntoserv();
	/**
		Zatrzymuje pracê w¹tku.
	*/
	std::mutex mtx;
	/**
		Metoda pozwalaj¹ca przekazanie nazwy u¿ytkownika
		@return Zwraca nazwê u¿ytkownika.
	*/
	std::string ShowName();
	/**
		Metoda zwracaj¹ca wielkoœæ kolejki.
		@return Wielkoœæ kolejki priorytetowej.
	*/
	int sizerec();
	/**
		Metoda zwracaj¹c¹ wiadmoœæ odebran¹.
		@return Treœæ wiadomoœci odebranej od serwera.
	*/
	std::string showmsgrec();
	/**
		Metoda s³u¿¹ca do odbierania wiadomoœci przez u¿ytkownika.
		@param client Gniazdo u¿ytkownika po³¹czone z serwerem.
	*/
	void msgrec(const SOCKET &client);
	/**
		Metoda wirtualna sprz¹taj¹ca, czyli usuwanie i czyszcznie zaalokowanych pamiêci.
	*/
	void Cleanup() override;

	
};