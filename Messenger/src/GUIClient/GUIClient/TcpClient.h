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
		Zmienna przechowuj�ca nazw� u�ytkownika.
	*/
	std::string name;
	/**
		Zmienna przechowuj�ca adres IP serwera.
	*/
	std::string m_ipAddress;
	/**
		Zmienna przechowuj�ca port serwera.
	*/
	int m_port;
	/**
	Metoda wirtualna inicjalizuj�ca powstanie gniazda nas�uchuj�cego.
	@return Gniazdo stworzone na podstawie parametr�w w klasie.
	*/
	SOCKET CreateSocket() override;
	/**
		Metoda umo�liwiaj�ca po��czenie z serwerem.
		@param conn Gniazdo utworzone przez u�ytkownika.
		@return Gniazdo, kt�re zosta�o przyj�te przez serwer.
	*/
	SOCKET ConnectToSerwer(const SOCKET &conn);
	/**
		Kolejka priorytetowa przechowuj�ca wiadomo�ci odebrane.
	*/
	std::deque<std::string> messages;
	
	
	
public:
	/**
	Konstruktor inicjalizuj�cy powstanie klasy TcpClient.
	@param ipAddress Adres IP serwera.
	@param port  Port serwera.
	@param nick Nazwa u�ytkownika.
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
		Metoda s�u��ca do wysy�ania wiadomo�ci.
		@param client Gniazdo u�ytkownika.
		@param buf Tre�� wiadomo�ci wysy�anej.
		@param len D�ugo�� wiadmo�ci.
		@return Warto��, kt�ra jest flag� poprawnego wys�ania(0) lub nie(-1).
	*/
	int SendAll(int client, const char *buf, int *len);
	/**
		Metoda utrzymuj�ca dzia�anie serwera i komunikacj� mi�dzy u�ytkownikami
		@return Zwraca true je�li si� powiedzie, w przeciwnym false
	*/
	bool Initialize() override;
	/**
		Metoda s�u��ca do uruchomienia klienta i ��czenie go z klientem.
		@return Gniazdo po��czone z serwerem.
	*/
	SOCKET conntoserv();
	/**
		Zatrzymuje prac� w�tku.
	*/
	std::mutex mtx;
	/**
		Metoda pozwalaj�ca przekazanie nazwy u�ytkownika
		@return Zwraca nazw� u�ytkownika.
	*/
	std::string ShowName();
	/**
		Metoda zwracaj�ca wielko�� kolejki.
		@return Wielko�� kolejki priorytetowej.
	*/
	int sizerec();
	/**
		Metoda zwracaj�c� wiadmo�� odebran�.
		@return Tre�� wiadomo�ci odebranej od serwera.
	*/
	std::string showmsgrec();
	/**
		Metoda s�u��ca do odbierania wiadomo�ci przez u�ytkownika.
		@param client Gniazdo u�ytkownika po��czone z serwerem.
	*/
	void msgrec(const SOCKET &client);
	/**
		Metoda wirtualna sprz�taj�ca, czyli usuwanie i czyszcznie zaalokowanych pami�ci.
	*/
	void Cleanup() override;

	
};