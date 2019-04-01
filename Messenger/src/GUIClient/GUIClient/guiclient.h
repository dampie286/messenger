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
	Konstruktor inicjalizujπcy powstanie okna dialogowego.
	@param parent Wskaünik na przekazywany widget.
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
		Zmienna przechowujπca adres IP serwera.
	*/
	std::string ipad;
	/**
		Zmienna przechowujπca port serwera.
	*/
	int port;
	/**
		Zmienna przechowujπca nazwÍ uøytkownika.
	*/
	std::string nick;
	private slots:
	/**
		Slot odpowiedzialny za wywo≥anie funkcji, aby do≥πczyÊ do danego czatu.
	*/
	void ok();
protected:
	/**
		Gniazdo po≥πczone z serwerem.
	*/
	SOCKET clt;
	/**
		Wskaünik na obiekt TcpClient, czyli uøytkownika.
	*/
	TcpClient *client = nullptr;
	/**
		Wskaünik na obiekt ChatBox.
	*/
	ChatBox *chat=nullptr;
};

#endif // GUICLIENT_H