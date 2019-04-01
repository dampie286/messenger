#include "TcpListener.h"
#include <sstream>
#include<thread>
#include<mutex>
#include<queue>


bool TcpListener::Initialize(){

	WSADATA data; //Zmienna uruchamiaj�ca biblioteke WinSocket
	WORD DllBVersion = MAKEWORD(2, 1); //Wybranie wersji biblioteki
	if (WSAStartup(DllBVersion, &data) != 0) //sprawdzanie czy sie uruchamia
	{
		std::cerr << "Nie da sie utworzyc WinSocketa! Serwer sie zamknie dla bezpieczenstwa. Sprobuj ponownie wlaczyc" << std::endl;
		Cleanup(); //czyszczenie w sprawie nie powowdzenia
		Sleep(2000);
		exit(1);
	}
	return WSAStartup(DllBVersion, &data) == 0;
}
//The main processing loop
void TcpListener::Run()
{

	SOCKET listening = CreateSocket();//inicjalizacja gniazda nasluchuj�cego
	if (listening == INVALID_SOCKET)
	{
		closesocket(listening); //zamykanie gniazda
		std::cout << "Nie moze zostac utworzony serwer! Blad z serwerem. Sprobuj wlaczyc na nowo" << std::endl;
		Cleanup(); //czyszczenie
		Sleep(2000);
		exit(1);
	}
	std::cout << "Started..." << std::endl;
	fd_set master; //G��wny zestaw przechowuj�cy deskryptor plik�w
	FD_ZERO(&master); //zerowanie zestawu
	FD_SET(listening, &master); //dodanie do g��wngo zestawu gniazda nas�uchuj�cego

	
	
	//watek do wpisywania rzczy
	std::thread write=std::thread([this]() {
		while (true)
		{
			std::string s;//Zmienna tymczasowa wykorzystywana do przechowania tego co wpisuje serwer
			std::cout << ">";
			std::getline(std::cin, s);

			if (s == "Exit")
			{
				end = true;	
				break;
			}
			

		}
	});
	timeval time; //Struktura przechowuj�ca czas jak d�ugo ma czeka� synchronizator gniazd.
	time.tv_sec = 2;	//czas ustawiony na 2 sekundy 
	
	while (!end)
	{
		fd_set copy = master; //Zestaw pomocniczy
		int socketCount = select(0, &copy, nullptr, nullptr, &time); //synchronizacja gniazd 
			for (int i = 0; i < socketCount; i++)
			{
				SOCKET sock = copy.fd_array[i]; //Zmienna tymczasowa przechowuj�ca dane gniazdo po��czeniowe
				if (sock == listening) //gdy jest to prawda oznacza, �e do��cza do nas klient
				{
					
					SOCKET client = WaitForConnection(listening, klienci); //do��czenie klienta do serwera
					FD_SET(client, &master); // dodanie nowego u�ytkownika do zestawu

					std::string welcomeMSG = "Welcome to the Awesome Chat Serwer!"; //wys�anie wiadomo�ci powitalnej
					std::cout << "server sends from " << klienci[client] << ":" << welcomeMSG << "\n"; //pokazanie na serwerze, gdzie wys�a� i jak� wiadomo��
					send(client, welcomeMSG.c_str(), welcomeMSG.size() + 1, 0); //wys�anie wiadomo�ci powitalnej do nowego do��czonego u�ytkownika
					if (klienci.size() > 0) {
						for (int i = 0; i <= master.fd_count; i++)
						{
							
							SOCKET outSock = master.fd_array[i]; 
							if (outSock != listening &&outSock != client)
							{
								
								std::ostringstream ss; //Strumie� wyj�ciowy przechowuj�cy wiadomo��.
								ss  << klienci[client] <<" connected to room"<< std::endl;
								std::string strOut = ss.str(); //Zmienna przechowuj�ca wiadomo�� do wys�ania
								send(outSock, strOut.c_str(), strOut.size() + 1, 0);
							}
						}
					}

				}
				else
				{
					
					char buf[4096];				
					ZeroMemory(buf, 4096);
					int bytesIn = recv(sock, buf, 4096, 0);
					if (bytesIn <= 0) //je�li to zosta�o spe�nione, oznacza, �e klient si� roz��czy�
					{
						std::cout << "Disconnected " << klienci[sock] << std::endl;
						if (klienci.size() > 0) {
							for (int i = 0; i <= master.fd_count; i++)
							{
								
								SOCKET outSock = master.fd_array[i];
								if (outSock != listening &&outSock != sock)
								{
									
									std::ostringstream ss;
									ss << "Disconnected " << klienci[sock] << std::endl;
								
									std::string strOut = ss.str();
									send(outSock, strOut.c_str(), strOut.size() + 1, 0);
								}
							}
						}
						klienci[sock].erase(klienci[sock].begin() + 1); //usuwanie klienta z tablicy mieszj�cej
						closesocket(sock); //zamykanie gniazda
						FD_CLR(sock, &master); //usuni�cie clienta
					}
					else {
						std::cout << klienci[sock] << ":" << buf << "\r\n"; //wysy�anie wiadomo�ci do innnych
						for (int i = 0; i <= master.fd_count; i++)
						{
							
							SOCKET outSock = master.fd_array[i];
							if (outSock != listening &&outSock != sock)
							{

								
								std::ostringstream ss;
								ss << klienci[sock] << ":" << buf;
								
								std::string strOut = ss.str();
								send(outSock, strOut.c_str(), strOut.size() + 1, 0);

							}
						}

					}

				}

			}
		}
		

	klienci.clear(); //czyszczenie tablicy mieszj�cej
	FD_ZERO(&master); //czyszczenie tablicy
	closesocket(listening); //zamykanie gniazda nas�uchuj�cego
	write.join(); //zamykanie w�tku
	Cleanup(); //czysczenie klasy
}

void TcpListener::Cleanup() {
	WSACleanup(); //funkcja czyszcz�ca zainicjalizowan� bibliotek�
}
//Create a socket
SOCKET TcpListener::CreateSocket()
{
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0); //Zmienna przechowuj�ca stworzone gniazdo nas�uchuj�ce
	if (listening != INVALID_SOCKET)
	{
		SOCKADDR_IN addr; //Struktura przechowuj�ca informacj� o adresie gniazda
		addr.sin_port = htons(m_port); //dodanie portu
		addr.sin_family = AF_INET; //rodzina adres�w
		inet_pton(AF_INET, m_IpAdddress.c_str(), &addr.sin_addr);
		int bindok = bind(listening, (sockaddr*)&addr, sizeof(struct sockaddr)); //Zmienna, kt�ra zwraca czy gniazdo nas�uchuj�ce zosta�o przypisane do danych podanych przez u�ytkownika
		if (bindok != SOCKET_ERROR)
		{
			int listenok = listen(listening, SOMAXCONN); //Zmienna, kt�ra zwraca warto��, czy gniazdo jest ju� utworzonym gniazdem nas�uchuj�cym. Przypisuje si� gnia�dzie maksymaln� ilo�� przyjmowanych po��cze�.
			if (listenok == SOCKET_ERROR)
			{
				
				return -1;
			}

		}
	}
	else
	{
		std::cerr << "Nie moze zostac utworzone gniazdo!Koniec" << std::endl;
		closesocket(listening);
		WSACleanup();
		exit(1);
	}

	return listening;
}
//wait for a connection
SOCKET TcpListener::WaitForConnection(const SOCKET &listening, std::unordered_map<SOCKET, std::string>& klienci)
{

	sockaddr_in guest; //Zmienna przechowuj�ca informacje o kliencie przychodz�cym
	int sin_size = sizeof(struct sockaddr_in);

	SOCKET client = accept(listening, (struct sockaddr*)&guest, &sin_size); //Zmienna przechowuj�ca gniazdo u�ytkownika, kt�ry do��czy� do serwera
	if (client != INVALID_SOCKET) {
		
		int lengthnick;
		recv(client, (char*)&lengthnick,sizeof(int), 0); //dlugosc wiadomosci
		char *buffer = new char[lengthnick];
		recv(client, buffer, lengthnick, 0);
		if (lengthnick > 0)
		{
			std::string nick = std::string(buffer, 0, lengthnick);
			klienci.emplace(client, nick);
			lengthnick = 0;
			delete[]buffer;
		}
		else
			delete []buffer;

		char host[NI_MAXHOST];
		char service[NI_MAXHOST];
		ZeroMemory(host, NI_MAXHOST);
		ZeroMemory(service, NI_MAXHOST);


		if (getnameinfo((sockaddr*)&guest, sizeof(guest), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) //wy�wietlanie informacji o kliencie
		{
			std::cout << klienci[client] << " connected on port " << service << std::endl;
		}
		else
		{
			inet_ntop(AF_INET, &guest.sin_addr, host, NI_MAXHOST);
			std::cout << klienci[client] << " connected on port " << ntohs(guest.sin_port) << std::endl;
		}
	}
	else
	{
		std::cout << " connection failed" << std::endl;
	}
	
	return client;
}
//destruktor

TcpListener::~TcpListener() {
	if (!end) {
		klienci.clear();
		write.join();
	}
	Cleanup();
}


