#pragma once
#include <QWidget>
#include "ui_chatbox.h"
#include "TcpClient.h"
#include<thread>
#include<mutex>

class ChatBox : public QWidget {
	Q_OBJECT

public:
	/**
	Konstruktor inicjalizujący powstanie okna dialogowego.
	@param parent Wskaźnik na przekazywany widget.
	@param cl Wskaźnik na klasę użytkownika.
	@param add Gniazdo połączone z serwerem.
	*/
	ChatBox(QWidget * parent = Q_NULLPTR, TcpClient *cl=nullptr, SOCKET add = 0);
	/**
	Destruktor okna czatowego.
	*/
	~ChatBox();
	/**
		Wskaźnik na klasę TcpClient.
	*/
	TcpClient *clx;
	/**
		Zmienna przechowująca gniazdo połączone z serwerem.
	*/
	SOCKET con;
private:
	/**
		Inicjalizacja obiektu ChatBox.
	*/
	Ui::ChatBox ui;
	/**
		Flaga zarządzająca działaniem wątku.
	*/
	bool cls = true;
	/**
		Wątek służący do odbierania wiadomości.
	*/
	std::thread list;
	/**
		Wątek służący do wyświetlania odebranych wiadomości.
	*/
	std::thread dis;
	private slots:
	/**
		Slot odpowiedzialny za wysyłanie wiadomości.
	*/
	void sendwithline();
};
