#ifndef GUICLIENT_H
#define GUICLIENT_H

#include <QtWidgets/QDialog>
#include "ui_guiclient.h"
#include "TcpClient.h"
#include "chatbox.hpp"
#include<thread>
class GUIClient : public QDialog
{
	Q_OBJECT

public:
	/**
	Konstruktor inicjalizujący powstanie okna dialogowego.
	@param parent Wskaźnik na przekazywany widget.
	*/
	GUIClient(QWidget *parent = 0);
	/**
	Destruktor okna dialogowego.
	*/
	~GUIClient();
	
	
	private:
	/**
		
		Inicjalizacja obiektu GuiClient.
	*/
	Ui::GUIClientClass ui;
	/**
		Zmienna przechowująca adres IP serwera.
	*/
	std::string ipad;
	/**
		Zmienna przechowująca port serwera.
	*/
	int port;
	/**
		Zmienna przechowująca nazwę użytkownika.
	*/
	std::string nick;
	private slots:
	/**
		Slot odpowiedzialny za wywołanie funkcji, aby dołączyć do danego czatu.
	*/
	void ok();
protected:
	/**
		Gniazdo połączone z serwerem.
	*/
	SOCKET clt;
	/**
		Wskaźnik na obiekt TcpClient, czyli użytkownika.
	*/
	TcpClient *client = nullptr;
	/**
		Wskaźnik na obiekt ChatBox.
	*/
	ChatBox *chat=nullptr;
};

#endif // GUICLIENT_H