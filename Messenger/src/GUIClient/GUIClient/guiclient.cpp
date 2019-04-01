#include "guiclient.h"
#include <QtWidgets>
GUIClient::GUIClient(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.ok, SIGNAL(clicked()), this, SLOT(ok()));
	connect(ui.noOK, SIGNAL(clicked()), this, SLOT(close()));
}

GUIClient::~GUIClient()
{
	delete chat;
	delete client;
	
	
}


void GUIClient::ok()
{
	ipad = ui.ipAD->text().toUtf8().constData();
	nick = ui.nick->text().toUtf8().constData();
	bool goodint;
	port = ui.port->text().toInt(&goodint, 10);
	if (!goodint)
	{
		QMessageBox::warning(this, "Blad", "Port musi byc podany cyframi");
		ui.port->clear();
		ui.port->text().clear();
		goodint = true;
	}
	else {
		client=new TcpClient(ipad, port, nick);
		if (client->Initialize())
		{
			clt = client->conntoserv();
			if (clt == 0)
			{
				QMessageBox::warning(this, "Blad", "Nie mozna utworzyc uzytkownika. Sprobuj wlaczyc na nowo");
				ui.ipAD->clear();
				ui.ipAD->text().clear();
				ui.port->clear();
				ui.port->text().clear();
			}
			else if (clt == -1) {
				QMessageBox::warning(this, "Blad", "Nie mozna polaczyc sie z serwerem. Sprawdz, czy dobrze wpisales IP lub port");
				ui.ipAD->clear();
				ui.ipAD->text().clear();
				ui.port->clear();
				ui.port->text().clear();
			}
			else {
				ui.ipAD->deleteLater();
				ui.nick->deleteLater();
				ui.port->deleteLater();
				ui.noOK->deleteLater();
				ui.ok->deleteLater();
				this->hide();
				chat = new ChatBox(nullptr, client, clt);
				chat->show();
			}
		}
	}
}