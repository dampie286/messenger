#include "TcpClient.h"
#include <sstream>



//inicjalizujemy winsocketa
bool TcpClient::Initialize()
{
	WSADATA data;
	WORD DllBVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllBVersion, &data) != 0)
	{
		Cleanup();

	}
	return WSAStartup(DllBVersion, &data) == 0;
}
//tworzymy socketa

SOCKET TcpClient::CreateSocket() {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		//QMessageBox::warning(it, "Blad", "Nie mozna utworzyc uzytkownika. Sprobuj wlaczyc na nowo");
		closesocket(sock);
		Cleanup();
		return sock;
		//exit(1);
		
		
	}
	else
	{
		int connResult = ConnectToSerwer(sock);
		if (connResult == SOCKET_ERROR)
		{
			
			closesocket(sock);
			Cleanup();
			return connResult;
		}
	}
	int length = ShowName().size();
	send(sock, (char*)&length, sizeof(int), 0); //wysylamy dlugosc tekstu
	send(sock, ShowName().data(),length, 0);
	return sock;
}//laczenie sie z serwerem
SOCKET TcpClient::ConnectToSerwer(const SOCKET &conn)
{
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);
	int connResult = ::connect(conn, (sockaddr*)&hint, sizeof(hint));
	return connResult;
}


//glowny program uruchomieniiowy

SOCKET TcpClient::conntoserv()
{
	//tworzymy klienta
	SOCKET client = CreateSocket();
	return client;
	
}

int TcpClient::SendAll(int client, const char *buf, int *len)
{

	int total = 0; // ile bajtów ju? wys?ali?my
	int bytesleft = *len; // ile jeszcze zosta?o do wys?ania
	int n;


	while (total < *len) {
		n = send(client, buf + total, bytesleft, 0);
		if (n == -1) { break; }
		total += n;
		bytesleft -= n;
	}

	*len = total; // zwró? ilosc faktycznie wyslanych bajtów

	return n == -1 ? -1 : 0; // zwró? -1 w przypadku b??du, 0, gdy si? powiedzie
}

void TcpClient::msgrec( const SOCKET &client) 
{
	char buf[4096];

	while (true)
	{
		fd_set x;
		FD_ZERO(&x);
		FD_SET(client, &x);
		timeval time;
		time.tv_sec = 2;
		int bytesReceived = 0;
		auto a = select(0, &x, nullptr, nullptr, &time);
		if (a)
			bytesReceived = recv(client, buf, 4096, 0);
		else
			break;
		mtx.lock();
		if (bytesReceived < 0) {
			
			std::string tmp = "servfalse";
			messages.emplace_back(tmp);
			mtx.unlock();
			break;
			
		}
		else
			messages.emplace_back(std::string(buf, 0, bytesReceived));
		mtx.unlock();
		
	}
}

int TcpClient::sizerec()
{
	int tmp = messages.size();
	return tmp;
}
std::string TcpClient::showmsgrec() {
	std::string tmp = messages.front();
	messages.pop_front();
	return tmp;
}
std::string TcpClient::ShowName()
{
	return name;
}

void TcpClient::Cleanup() {
	WSACleanup();
}