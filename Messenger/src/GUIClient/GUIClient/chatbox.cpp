#include "chatbox.hpp"
#include <QtWidgets>
//setlocale(LC_ALL, "pl_PL");
ChatBox::ChatBox(QWidget * parent, TcpClient *cl, SOCKET add) : QWidget(parent), clx(cl), con(add) {
	
	ui.setupUi(this);
	connect(ui.send, SIGNAL(clicked()), this, SLOT(sendwithline()));
	connect(ui.disc, SIGNAL(clicked()), this, SLOT(close()));
	list = std::thread([this]() {
		while (cls) {
			clx->msgrec(con);
				
		}
	});
	dis=std::thread([this]() {
		while (cls) {
			
			if (clx->sizerec() > 0)
			{
				//clx->mtx.lock();
				std::lock_guard<std::mutex> lck(clx->mtx);
				std::string tmp = clx->showmsgrec();

				if (tmp == "servfalse")
				{

					//QMessageBox::warning(this, "Błąd", "Brak połączenia z serwerem. Prosze nacisnąć 'disconnect' i zalogowac sie na inny serwer!");
					QString tmp = "Brak polaczenia z serwerem. Prosze nacisnac 'Closed' i wlaczyc ponownie program!";
					ui.display->append(tmp);
					cls = false;
					break;
			
				}
				else
					ui.display->append(QString::fromStdString(tmp));
			}
		}
	});

	
	
}
ChatBox::~ChatBox() {
	//flaga 
	cls = false; 
	//delete clx;
	list.join(); //tutaj sie zawiesza , ale tylko gdy wywolowujemy destruktor :/
	dis.join();
	
}

void ChatBox::sendwithline()
{

	if (!cls)
	{
		ui.message->clear();
		ui.message->text().clear();
	QMessageBox::warning(this, "Błąd", " Prosze nacisnac 'Closed' i zalogowac sie na inny serwer!");
	}
	else {
		clx->mtx.lock();
		ui.display->append(QString::fromStdString("Me") + ":" + ui.message->text());
		std::string msg = ui.message->text().toUtf8().constData();
		int len = msg.size() + 1;
		clx->SendAll(con, msg.data(), &len);
		clx->mtx.unlock();
		ui.message->clear();
		ui.message->text().clear();
	}
	}



