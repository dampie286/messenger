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
	Konstruktor inicjalizuj�cy powstanie okna dialogowego.
	@param parent Wska�nik na przekazywany widget.
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
		Zmienna przechowuj�ca adres IP serwera.
	*/
	std::string ipad;
	/**
		Zmienna przechowuj�ca port serwera.
	*/
	int port;
	/**
		Zmienna przechowuj�ca nazw� u�ytkownika.
	*/
	std::string nick;
	private slots:
	/**
		Slot odpowiedzialny za wywo�anie funkcji, aby do��czy� do danego czatu.
	*/
	void ok();
protected:
	/**
		Gniazdo po��czone z serwerem.
	*/
	SOCKET clt;
	/**
		Wska�nik na obiekt TcpClient, czyli u�ytkownika.
	*/
	TcpClient *client = nullptr;
	/**
		Wska�nik na obiekt ChatBox.
	*/
	ChatBox *chat=nullptr;
};

#endif // GUICLIENT_H